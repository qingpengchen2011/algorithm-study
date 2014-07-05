#include "graph.hpp"
#include <stdio.h>
#include <deque>
#include <boost/algorithm/string.hpp>

//class graph
graph::graph(int v):m_v(v),m_e(0){
	init();
};

graph::graph(std::ifstream& in){
	int a,b;
	in>>m_v>>m_e;
	init();
	int r=0;
	while(r<m_e){
		in>>a>>b;
		adjTable[a].push_back(b);	
		adjTable[b].push_back(a);
		++r;
	}
};

void graph::init(){
	adjTable.reserve(m_v);
	adjTable.assign(m_v,std::vector<int>());
};

void graph::addEdge(int v,int w){
	adjTable[v].push_back(w);
	adjTable[w].push_back(v);
	++m_e;

};


std::string graph::toString(){
	char buffer[1024];
	snprintf(buffer,sizeof(buffer),"number of v:%d,number of e:%d\n",m_v,m_e);
	std::string s(buffer);
	for(int i=0;i<adjTable.size();++i){
		std::vector<int>& adj=adjTable[i];		
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

//class depthfirstsearch
	
depthfirstsearch::depthfirstsearch(graph g,int s):m_g(g),m_s(s),m_count(0){
	mark.assign(g.num_v(),false);
	dfs(s);
};

bool depthfirstsearch::connect(int v){
	return mark[v];
};

int depthfirstsearch::count(){return m_count;};
	//private
void depthfirstsearch::dfs(int v){
	mark[v]=true;
	m_count++;
	typename graph::ADJLIST v_adj=m_g.adjlist(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(!mark[w]) dfs(w);
	}
	
};

//class depthfirstpath

depthfirstpath::depthfirstpath(graph g,int s):m_g(g),m_s(s){
	mark.assign(g.num_v(),false);
	edgeto.reserve(g.num_v());
	dfs_p(s);
};


bool depthfirstpath::haspathto(int v){ return mark[v];};

std::vector<int> depthfirstpath::pathto(int v){	
	std::deque<int> path;
	for(int s=v;s!=m_s;s=edgeto[s]){
		path.push_front(s);	
	}
	path.push_front(m_s);
	return std::vector<int>(path.begin(),path.end());
};

	//private
void depthfirstpath::dfs_p(int v){
	mark[v]=true;
	typename graph::ADJLIST v_adj=m_g.adjlist(v);
	for(int i=0;i<v_adj.size();++i){
		int w=v_adj[i];
		if(!mark[w]){
			edgeto[w]=v;
			dfs_p(w);
		}		
	}		
};

//class breadfirstsearch 

breadfirstsearch::breadfirstsearch(graph g,int s):m_g(g),m_s(s),m_count(0){
	mark.assign(g.num_v(),false);
	bfs(s);
};
	//private
void breadfirstsearch::bfs(int s){
	std::deque<int>  queue;
	mark[s]=true;
	queue.push_back(s);
	++m_count;
	while(!queue.empty()){
		int v=queue.front();
		queue.pop_front();
		typename graph::ADJLIST v_adj=m_g.adjlist(v);
		for(int i=0;i<v_adj.size();++i){
			int w=v_adj[i];
			if(!mark[w]){
				mark[w]=true;
				queue.push_back(w);
				++m_count;
			}	

		}
	}
};

//class breadfirstpath

breadfirstpath::breadfirstpath(graph g,int s):m_g(g),m_s(s){
	mark.assign(g.num_v(),false);
	edgeto.reserve(g.num_v());
	bfs_p(s);
};

std::vector<int> breadfirstpath::pathto(int v){
	std::deque<int> path;
	for(int s=v;s!=m_s;s=edgeto[s]){
		path.push_front(s);	
	}
	path.push_front(m_s);
	return std::vector<int>(path.begin(),path.end());
};

	//private
void breadfirstpath::bfs_p(int s){
	std::deque<int> queue;
	mark[s]=true;
	queue.push_back(s);
	while(!queue.empty()){
		int v=queue.front();
		queue.pop_front();
		typename graph::ADJLIST v_adj=m_g.adjlist(v);
		for(int i=0;i<v_adj.size();++i){
			int w=v_adj[i];
			if(!mark[w]){
				mark[w]=true;
				queue.push_back(w);
				edgeto[w]=v;		
			}
		}		
	}	
};


//class connection_component
	
connection_component::connection_component(graph g):m_g(g),m_count(0){
	mark.assign(g.num_v(),false);
	ids.reserve(g.num_v());
	for(int i=0;i<m_g.num_v();++i){
		if(!mark[i]){
			dfs_cc(i);
			++m_count;
		}	
	}
};

bool connection_component::connected(int s,int v){
	return ids[s]==ids[v];
};

int connection_component::id(int v){
	return ids[v];
};

int connection_component::countofcc(){return m_count;};

	//private
void connection_component::dfs_cc(int s){
	mark[s]=true;
	ids[s]=m_count;
	typename graph::ADJLIST s_adj=m_g.adjlist(s);
	for(int i=0;i<s_adj.size();++i){
		int w=s_adj[i];
		if(!mark[w]){
			dfs_cc(w);
		}
	}						
};


//class cycle_graph




//class twocolor_graph

twocolor_graph::twocolor_graph(graph g):m_g(g){
	mark.assign(m_g.num_v(),false);	
	color.assign(m_g.num_v(),false);
	istwocolorable=true;
	for(int s=0;s<m_g.num_v();++s){
		if(!mark[s])
			dfs_twocolor(s);
	}

};

	//private
void twocolor_graph::dfs_twocolor(int s){
	mark[s]=true;
	typename graph::ADJLIST s_adj=m_g.adjlist(s);
	for(int i=0;i<s_adj.size();++i){
		int w=s_adj[i];
		if(!mark[w]){
			color[w]=!color[s];//put color on
			dfs_twocolor(w);
		}
		else if (color[s]==color[w]){
			istwocolorable=false;
		}
	}	
}; 


//class symbol_graph

symbol_graph::symbol_graph(std::string filename,std::string delim){
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
	m_pg.reset(new graph(m_symtable.size()));	
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


int symbol_graph::index(std::string vertex){
	return (*m_symtable.find(vertex)).second;	
};

bool symbol_graph::contains(std::string vertex){
	return m_symtable.find(vertex)!=m_symtable.end()?true:false;
};
