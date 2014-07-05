#include "ewdigraph.hpp"
#include <stdio.h>
#include <fstream>
#include <deque>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

diedge::diedge(int v,int w,double weight):m_v(v),m_w(w),m_weight(weight){};

std::string diedge::toString()const{
	char buf[1024];
	snprintf(buf,sizeof(buf),"%d->%d (%.6f)",m_v,m_w,m_weight);
	return std::string(buf);
};

//class ewdigraph

ewdigraph::ewdigraph(int v):m_v(v),m_e(0){
	m_adjTable.assign(v,std::vector<diedge>());

};

ewdigraph::ewdigraph(std::string filename){
	std::ifstream in(filename);
        in>>m_v>>m_e;
        m_adjTable.assign(m_v,std::vector<diedge>());
        int v,w;
        double  weight;
        while(in>>v>>w>>weight){
                m_adjTable[v].push_back(diedge(v,w,weight));
        }
        in.close();

};

void ewdigraph::addEdge(diedge e){
	int v=e.from();
	m_adjTable[v].push_back(e);		
	++m_e;

};

std::vector<diedge> ewdigraph::edges(){
	std::vector<diedge> l_edges;
        for(int v=0;v<m_v;++v){
                const ADJLIST& v_adj=adj(v);
                for(int j=0;j<v_adj.size();++j){
                        const diedge& e=v_adj[j];
			l_edges.push_back(e);
                }

        }
        return l_edges;
};

ewdigraph ewdigraph::reverse_weight(){
	ewdigraph tmp(m_v);
	for(int v=0;v<m_v;++v){
		const ADJLIST& v_adj=adj(v);
                for(int j=0;j<v_adj.size();++j){
                        const diedge& e=v_adj[j];
                        tmp.addEdge(diedge(e.from(),e.to(),-e.weight()));
                }

        }	
	return tmp;
};

std::string ewdigraph::toString(){
	char buffer[1024];
        snprintf(buffer,sizeof(buffer),"EDGE_WEIGHT_DIGRAPH:number of v:%d,number of e:%d\n",m_v,m_e);
        std::string s(buffer);
        for(int i=0;i<m_adjTable.size();++i){
                std::vector<diedge>& adj=m_adjTable[i];
                snprintf(buffer,sizeof(buffer),"%d->: ",i);
                s+=buffer;
                for(int j=0;j<adj.size();++j){
                        snprintf(buffer,sizeof(buffer),"%d(%.5f) ",adj[j].to(),adj[j].weight());
                        s+=buffer;
                }
                s+='\n';
        }
        return s;

};


//class dijkstra shortest path

dijkstra_sp::dijkstra_sp(ewdigraph g,int s):m_g(g),m_s(s){
	m_edgeto.assign(g.V(),diedge(-1,-1,0.0));
	m_edgeto[s]=diedge(s,s,0.0);
	m_distto.assign(g.V(),(std::numeric_limits<double>::max)());
	m_distto[s]=0.0;

	m_pq.insert(s,0.0);
	while(!m_pq.empty()){
		visit(m_pq.del_min());
	}
};

bool dijkstra_sp::haspathto(int v){
	return m_distto[v]!=(std::numeric_limits<double>::max)();
};

std::vector<diedge> dijkstra_sp::pathto(int v){	
	std::deque<diedge> path;	
	for(diedge e=m_edgeto[v];e.to()!=e.from();e=m_edgeto[e.from()]){
		path.push_front(e);		
	}
	return std::vector<diedge>(path.begin(),path.end());
};

double dijkstra_sp::dist(int v){
	return m_distto[v];
};

void dijkstra_sp::visit(int v){
	const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		const diedge& e=v_adj[i];
		int w=e.to();
		if(m_distto[w]>m_distto[v]+e.weight()){
			m_distto[w]=m_distto[v]+e.weight();
			m_edgeto[w]=e;
			if(m_pq.contains(w)){
				m_pq.change(w,m_distto[w]);
			}
			else{
				m_pq.insert(w,m_distto[w]);
			}	
		}		
	}	
};


//----------------UTIL-------------------
// class ewdirected_cycle
ewdirected_cycle::ewdirected_cycle(ewdigraph g):m_g(g){
        marked.assign(m_g.V(),false);
        onstack.assign(m_g.V(),false);
        edge.assign(m_g.V(),diedge(0,0,0.0));
        for(int v=0;v<m_g.V();++v){
                if(!marked[v])
                        cyclic_dfs(v);
        }
};

void ewdirected_cycle::cyclic_dfs(int v){ //we are done,when we've already detect a cycle
                        //call hascycle() here can be better?
        marked[v]=true;
        onstack[v]=true;
        const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
        for(int i=0;i<v_adj.size();++i){
                diedge e=v_adj[i];
                int w=e.to();
                if(hascycle()) //the point to call hascycle() is considerable
                        return;
                else if(!marked[w]){
                        edge[w]=e;
                        cyclic_dfs(w);
                }
                else if(onstack[w]){ //w has been checked,then check weather it's alreadly on stack now
                        diedge x(e);
                        for( ;x.from()!=w;x=edge[x.from()]){
                                m_cycle.push_front(x);
                        }
                        m_cycle.push_front(x);
                }
        }
        onstack[v]=false;
};

//class ewdigraph_depthfirstorder

ewdigraph_depthfirstorder::ewdigraph_depthfirstorder(ewdigraph g):m_g(g){
        marked.assign(m_g.V(),false);
        for(int v=0;v<m_g.V();++v){
                if(!marked[v])
                        dfs(v);
        }
};

void ewdigraph_depthfirstorder::dfs(int v){
        marked[v]=true;
        m_pre.push_back(v);
        const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
        for(int i=0;i<v_adj.size();++i){
                int w=v_adj[i].to();
                if(!marked[w])
                        dfs(w);
        }
        m_post.push_back(v);
        m_reversepost.push_front(v);

};


//class ewdigraph_topological
ewdigraph_topological::ewdigraph_topological(ewdigraph g):m_g(g){
        ewdirected_cycle dc(m_g);
        if(!dc.hascycle()){
                ewdigraph_depthfirstorder dfo(m_g);
                m_order=dfo.reversepost();
        }
};


//----------------END UTIL-------------------

//class acyclic_sp 
acyclic_sp::acyclic_sp(ewdigraph g,int s):m_g(g),m_s(s){
	m_edgeto.assign(g.V(),diedge(-1,-1,0.0));
        m_edgeto[s]=diedge(s,s,0.0);
        m_distto.assign(g.V(),(std::numeric_limits<double>::max)());
        m_distto[s]=0.0;

	ewdigraph_topological topo(g);
	std::vector<int> topo_order=topo.order();
	for(int i=0;i<topo_order.size();++i){
		int v=topo_order[i];
		relax(v);
	}

};

bool acyclic_sp::haspathto(int v){
	return m_distto[v]!=(std::numeric_limits<double>::max)();
};

std::vector<diedge> acyclic_sp::pathto(int v){
	std::deque<diedge> path;	
	for(diedge e=m_edgeto[v];e.to()!=e.from();e=m_edgeto[e.from()]){
		path.push_front(e);		
	}
	return std::vector<diedge>(path.begin(),path.end());
};

double acyclic_sp::dist(int v){
	return m_distto[v];
};

void acyclic_sp::relax(int v){
	const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		const diedge& e=v_adj[i];
		int w=e.to();
		if(m_distto[w]>m_distto[v]+e.weight()){
			m_distto[w]=m_distto[v]+e.weight();
			m_edgeto[w]=e;
		}		
	}	
};

//class acyclic_lp
acyclic_lp::acyclic_lp(ewdigraph g,int s):m_g(g),m_s(s){
	m_edgeto.assign(g.V(),diedge(-1,-1,0.0));
	m_edgeto[s]=diedge(s,s,0.0);
        m_distto.assign(g.V(),-(std::numeric_limits<double>::max)()); //miminum of double
	m_distto[s]=0.0;

	ewdigraph_topological topo(g);
	std::vector<int> topo_order=topo.order();
	for(int i=0;i<topo_order.size();++i){
		int v=topo_order[i];
		relax(v);
	}

};

bool acyclic_lp::haspathto(int v){
	return m_distto[v]!=(-(std::numeric_limits<double>::max)());
};

std::vector<diedge> acyclic_lp::pathto(int v){
	std::deque<diedge> path;	
	for(diedge e=m_edgeto[v];e.to()!=e.from();e=m_edgeto[e.from()]){
		path.push_front(e);		
	}
	return std::vector<diedge>(path.begin(),path.end());
};

double acyclic_lp::dist(int v){
	return m_distto[v];
};

void acyclic_lp::relax(int v){
	const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		const diedge& e=v_adj[i];
		int w=e.to();
		if(m_distto[w]<m_distto[v]+e.weight()){  //different with SP
			m_distto[w]=m_distto[v]+e.weight();
			m_edgeto[w]=e;
		}		
	}	
};

//class cpm

cpm::cpm(std::string filename){
	std::ifstream in(filename);
	int v=0;
	std::string line;
	in>>v;
	std::getline(in,line);
	int s=2*v,t=2*v+1;
	//construct the graph
	ewdigraph g(2*v+2);
	for(int i=0;i<v;++i){
		std::getline(in,line);
		std::vector<std::string> vStr;
                boost::split(vStr,line,boost::is_any_of("/"));
		g.addEdge(diedge(i,i+v,atof(vStr[0].c_str())));
		g.addEdge(diedge(s,i,0.0));
		g.addEdge(diedge(i+v,t,0.0));
                for( std::vector<std::string>::iterator it = vStr.begin()+1; it != vStr.end(); ++ it ){
			g.addEdge(diedge(i+v,atoi(it->c_str()),0.0));		
                }


	}							

	//finish construct the graph
	acyclic_lp lp(g,s);
	std::cout<<"start times:\n";
	for(int i=0;i<v;++i){
		std::cout<<i<<" : "<<lp.dist(i)<<std::endl;
	}		
	std::cout<<"finish time:"<<lp.dist(t)<<std::endl;
	
};

//class bellman_ford_sp
bellman_ford_sp::bellman_ford_sp(ewdigraph g,int s):m_g(g),m_s(s),m_cost(0){
	m_distto.assign(g.V(),(std::numeric_limits<double>::max)());
	m_distto[s]=0.0;
	
	m_edgeto.assign(g.V(),diedge(-1,-1,0.0));
	m_edgeto[s]=diedge(s,s,0.0);

	m_onqueue.assign(g.V(),false);
	m_queue.push(s);
	m_onqueue[s]=true;
	while(!m_queue.empty() && !hasnegativecycle()){
		int v=m_queue.front();
		m_queue.pop();	
		m_onqueue[v]=false;
		relax(v);
	}

};

std::vector<diedge> bellman_ford_sp::pathto(int v){
	std::deque<diedge> path;	
	for(diedge e=m_edgeto[v];e.to()!=e.from();e=m_edgeto[e.from()]){
		path.push_front(e);		
	}
	return std::vector<diedge>(path.begin(),path.end());
};

	//private
void bellman_ford_sp::relax(int v){
	const ewdigraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		const diedge& e=v_adj[i];
		int w=e.to();
		if(m_distto[w]>m_distto[v]+e.weight()){
			m_distto[w]=m_distto[v]+e.weight();
			m_edgeto[w]=e;
			if(!m_onqueue[w]){
				m_onqueue[w]=true;			
				m_queue.push(w);
			}
		}		
		//when to call findnegativecycle is considerable!	
		if(((++m_cost)%m_g.V())	== 0){
			findnegativecycle();		
		}
	}	

};

void bellman_ford_sp::findnegativecycle(){
	ewdigraph g(m_edgeto.size());
	for(int i=0;i<m_edgeto.size();++i){
		diedge e=m_edgeto[i];
		if(e.from()!=e.to()){
			g.addEdge(e);
		}
	}
	ewdirected_cycle cyc(g);
	m_cycle=cyc.cycle();		
};
