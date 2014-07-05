#include "digraph.hpp"
#include <fstream>
#include <deque>
#include <boost/algorithm/string.hpp>

//class digraph

digraph::digraph(int v):m_v(v),m_e(0){
	m_adjTable.assign(v,std::vector<int>());
};

digraph::digraph(std::string filename){
	std::ifstream in(filename);
	in>>m_v>>m_e;
//	std::cout<<"number of vertices: "<<m_v<<" ,number of edges:"<<m_e<<std::endl;
	m_adjTable.assign(m_v,std::vector<int>());
	int v,w;
	while(in>>v>>w){
//		std::cout<<"edge:"<<v<<" -> "<<w<<std::endl;
		m_adjTable[v-1].push_back(w-1);
	}
	in.close();
};

void digraph::addEdge(int v,int w){
	m_adjTable[v].push_back(w);
	++m_e;
};

digraph digraph::reverse(){
	digraph rev_graph(m_v);
	for(int v=0;v<m_adjTable.size();++v){
		const ADJLIST& v_adj=adj(v);
		for(int j=0;j<v_adj.size();++j){
			int w=v_adj[j];
			rev_graph.addEdge(w,v);
		}	
	}
	return rev_graph;
};

std::string digraph::toString(){
        char buffer[1024];
        snprintf(buffer,sizeof(buffer),"number of v:%d,number of e:%d\n",m_v,m_e);
        std::string s(buffer);
        for(int i=0;i<m_adjTable.size();++i){
                std::vector<int>& adj=m_adjTable[i];
                snprintf(buffer,sizeof(buffer),"%d: ",i);
                s+=buffer;
                for(int j=0;j<adj.size();++j){
                        snprintf(buffer,sizeof(buffer),"%d ",adj[j]);
                        s+=buffer;
                }
                s+='\n';
        }
        return s;
};


//class directed_dfs
directed_dfs::directed_dfs(digraph g,int s):m_g(g){
	marked.assign(m_g.V(),false);
	di_dfs(s);
};


directed_dfs::directed_dfs(digraph g,std::vector<int> sources):m_g(g){
	marked.assign(m_g.V(),false);
	for(std::vector<int>::iterator it=sources.begin(),end=sources.end();it!=end;++it){
		if(!marked[*it])
			di_dfs(*it);
	}	

};

void directed_dfs::di_dfs(int v){
	marked[v]=true;
	const digraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(!marked[w])
			di_dfs(w);
	}			
};

//class depthfirstdirectedpath

depthfirstdirectedpath::depthfirstdirectedpath(digraph g,int s):m_g(g),m_s(s){
	marked.assign(g.V(),false);
	edge.reserve(g.V());	
	dfs(s);	
};

std::vector<int> depthfirstdirectedpath::pathto(int v){
	std::deque<int> path;
	for(int s=v;s!=m_s;s=edge[s]){
		path.push_front(s);	
	}
	path.push_front(m_s);
	return std::vector<int>(path.begin(),path.end());
};

void depthfirstdirectedpath::dfs(int v){
	marked[v]=true;	
	const digraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(!marked[w]){
			edge[w]=v;
			dfs(w);
		}
	}			

};


//class directed_bfs

directed_bfs::directed_bfs(digraph g,int s):m_g(g){
	marked.assign(g.V(),false);
	bi_bfs(s);
};

directed_bfs::directed_bfs(digraph g,std::vector<int> sources):m_g(g){
	marked.assign(g.V(),false);
	for(std::vector<int>::iterator it=sources.begin(),end=sources.end();it!=end;++it){
		if(!marked[*it])
			bi_bfs(*it);
	}	

};

void directed_bfs::bi_bfs(int v){
	std::deque<int> queue;
	marked[v]=true;
	queue.push_back(v);	
	while(!queue.empty()){
		int v=queue.front();
		queue.pop_front();	
		const digraph::ADJLIST& v_adj=m_g.adj(v);
		for(int i=0;i<v_adj.size();++i){
			int w=v_adj[i];
			if(!marked[w]){
				marked[w]=true;
				queue.push_back(w);
			}
		}			
	}

};

//class breadthfirstdirectedpath
breadthfirstdirectedpath::breadthfirstdirectedpath(digraph g,int s):m_g(g),m_s(s){
	marked.assign(m_g.V(),false);
	edge.reserve(m_g.V());
	bfs(s);	
};

std::vector<int> breadthfirstdirectedpath::pathto(int v){
	std::deque<int> path;
	for(int s=v;s!=m_s;s=edge[s]){
		path.push_front(s);	
	}
	path.push_front(m_s);
	return std::vector<int>(path.begin(),path.end());
};

void breadthfirstdirectedpath::bfs(int v){
	std::deque<int> queue;
	marked[v]=true;
	queue.push_back(v);	
	while(!queue.empty()){
		int v=queue.front();
		queue.pop_front();	
		const digraph::ADJLIST& v_adj=m_g.adj(v);
		for(int i=0;i<v_adj.size();++i){
			int w=v_adj[i];
			if(!marked[w]){
				marked[w]=true;
				edge[w]=v;
				queue.push_back(w);
			}
		}			
	}


};


//-------------------------------------------------------------------
//class directed_cycle

directed_cycle::directed_cycle(digraph g):m_g(g){
	marked.assign(m_g.V(),false);
	onstack.assign(m_g.V(),false);
	edge.reserve(m_g.V());
	for(int v=0;v<m_g.V();++v){
		if(!marked[v])
			cyclic_dfs(v);	
	}			
};

void directed_cycle::cyclic_dfs(int v){ //we are done,when we've already detect a cycle
			//call hascycle() here can be better?
	marked[v]=true;
	onstack[v]=true;	
	const digraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(hascycle()) //the point to call hascycle() is considerable
			return;
		else if(!marked[w]){
			edge[w]=v;
			cyclic_dfs(w);
		}
		else if(onstack[w]){ //w has been checked,then check weather it's alreadly on stack now
			for(int x=v;x!=w;x=edge[x]){
				m_cycle.push_front(x);
			}	
			m_cycle.push_front(w);
			m_cycle.push_back(w);
		}
	}			
	onstack[v]=false;
};

//class symbol_digraph

symbol_digraph::symbol_digraph(std::string filename,std::string delim){
	std::ifstream in(filename);
	std::string line;
	//construct the two tables;	
	while(std::getline(in,line)){
		std::vector<std::string> vStr;
		boost::split(vStr,line,boost::is_any_of(delim));
		for( std::vector<std::string>::iterator it = vStr.begin(); it != vStr.end(); ++ it ){
			if(m_symtable.find(*it)==m_symtable.end()){
				m_symtable.insert(std::make_pair(*it,m_symtable.size()));
			}
		}

	}

	m_idxtable.assign(m_symtable.size(),std::string(""));


	for(std::map<std::string,int>::iterator it=m_symtable.begin(),end=m_symtable.end();it!=end;++it){
		m_idxtable[it->second]=it->first;
	}
	in.close();
	//construct the graph

	in.open(filename);
	m_pg.reset(new digraph(m_symtable.size()));	
	while(std::getline(in,line)){
		std::vector<std::string> vStr;
		boost::split(vStr,line,boost::is_any_of(delim));
		int s=index(vStr[0]);
		for( std::vector<std::string>::iterator it = vStr.begin()+1; it != vStr.end(); ++ it ){
			m_pg->addEdge(s,index(*it));
		}

	}
	in.close();
	std::cout<<"Symbol Table:"<<m_symtable.size()<<" id index:"<<m_idxtable.size()<<std::endl;
	std::cout<<"std::vector:capacity():"<<m_idxtable.capacity()<<std::endl; 
};


int symbol_digraph::index(std::string vertex){
	return (*m_symtable.find(vertex)).second;	
};

bool symbol_digraph::contains(std::string vertex){
	return m_symtable.find(vertex)!=m_symtable.end()?true:false;
};

//-------------------------------------------------------------------

//class depthfirstorder
depthfirstorder::depthfirstorder(digraph g):m_g(g){
	marked.assign(m_g.V(),false);
	for(int v=0;v<m_g.V();++v){
		if(!marked[v])
			dfs(v);
	}
};

void depthfirstorder::dfs(int v){
	marked[v]=true;
	m_pre.push_back(v);		
	const digraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(!marked[w])
			dfs(w);
	}			
	m_post.push_back(v);
	m_reversepost.push_front(v);

};

//class topological

topological::topological(digraph g):m_g(g){
	directed_cycle dc(m_g);
	if(!dc.hascycle()){
		depthfirstorder dfo(m_g);
		m_order=dfo.reversepost();
	}	
};

//class koaraju_scc

kosaraju_scc::kosaraju_scc(digraph g):m_count(0),m_g(g){
	marked.assign(g.V(),false);
	ids.reserve(g.V());
	depthfirstorder dfs(g.reverse());	
	const std::vector<int>& order=dfs.reversepost();
	for(std::vector<int>::const_iterator it=order.begin(),end=order.end();it!=end;++it){
		if(!marked[*it]){
			dfs_scc(*it);
			++m_count;
		}
	}
};


void kosaraju_scc::dfs_scc(int v){
	marked[v]=true;	
	ids[v]=m_count;
	const digraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(!marked[w]){
			dfs_scc(w);
		}
	}			

};

//class transitive_closure 

transitive_closure::transitive_closure(digraph g){
	directed_dfses.reserve(g.V());
	for(int v=0;v<g.V();++v){
		directed_dfses[v].reset(new directed_dfs(g,v));
	};
};

