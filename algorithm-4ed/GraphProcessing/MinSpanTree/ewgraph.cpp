#include "ewgraph.hpp"

#include <fstream>
#include <algorithm>
#include <limits>
#include <functional>
#include <algorithm>

//class ewgraph
ewgraph::ewgraph(int v):m_v(v),m_e(0){
	m_adjTable.assign(v,std::vector<edge>());
};
ewgraph::ewgraph(std::string filename){
	std::ifstream in(filename);
        in>>m_v>>m_e;
        m_adjTable.assign(m_v,std::vector<edge>());
        int v,w;
	double  weight;
        while(in>>v>>w>>weight){
                m_adjTable[v].push_back(edge(v,w,weight));
		m_adjTable[w].push_back(edge(v,w,weight));
        }
        in.close();
};

void ewgraph::addEdge(edge e){
	int v=e.either();
	m_adjTable[v].push_back(e);
	m_adjTable[e.other(v)].push_back(e);
	++m_e;
};

std::vector<edge> ewgraph::edges(){
	std::vector<edge> l_edges;
	for(int v=0;v<m_v;++v){
		const ADJLIST& v_adj=adj(v);
		for(int j=0;j<v_adj.size();++j){
			const edge& e=v_adj[j];
			if(std::find(l_edges.begin(),l_edges.end(),e)==l_edges.end()){
				l_edges.push_back(e);
			}
		}	

	}
	return l_edges;
};

std::string ewgraph::toString(){
	char buffer[1024];
        snprintf(buffer,sizeof(buffer),"EDGE_WEIGHT_GRAPH:number of v:%d,number of e:%d\n",m_v,m_e);
        std::string s(buffer);
        for(int i=0;i<m_adjTable.size();++i){
                std::vector<edge>& adj=m_adjTable[i];
                snprintf(buffer,sizeof(buffer),"%d: ",i);
                s+=buffer;
                for(int j=0;j<adj.size();++j){
                        snprintf(buffer,sizeof(buffer),"%d(%.5f) ",adj[j].other(i),adj[j].weight());
                        s+=buffer;
                }
                s+='\n';
        }
        return s;
};

//class lazy_prim_mst

lazy_prim_mst::lazy_prim_mst(ewgraph g):m_g(g),m_weight(0.0){
	m_marked.assign(g.V(),false);
	visit(0); //begin with vertex 0, but any vertex is ok	
	while(!m_pq.empty()){
		edge e=m_pq.top();
		m_pq.pop();
		int v=e.either();
		int w=e.other(v);
		if(m_marked[v]&&m_marked[w]) //check for fail cross-edge
			continue;	
		m_edgeofmst.push_back(e);
		m_weight+=e.weight();
		if(!m_marked[v])
			visit(v);
		else
			visit(w);
	}
};

void lazy_prim_mst::visit(int v){
	m_marked[v]=true; //add this vertex to MST
	const typename ewgraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		edge e=v_adj[i];
		if(!m_marked[e.other(v)])
			m_pq.push(e);	 //add cross-edges to priority_queue
	}
		
};


// class eager_prim_mst

eager_prim_mst::eager_prim_mst(ewgraph g):m_g(g),m_weight(0.0){
	m_edgeofmst.assign(g.V(),edge(0,0,0.0));
	m_marked.assign(g.V(),false);
	m_weightto.assign(g.V(),(std::numeric_limits<double>::max)());
	visit(0);
	while(!m_queue.empty()){
		m_weight+=m_queue.min();
		visit(m_queue.del_min());		
	}		
};

void eager_prim_mst::visit(int v){
	m_marked[v]=true;
	const typename ewgraph::ADJLIST& v_adj=m_g.adj(v);
	for(int i=0;i<v_adj.size();++i){
		edge e=v_adj[i];
		int w=e.other(v);
		if(!m_marked[w]){ //vertex w not on the tree now
			if(e.weight()<m_weightto[w]){
				m_weightto[w]=e.weight();
				m_edgeofmst[w]=e;//do record or update
				if(!m_queue.contains(w))
					m_queue.insert(w,m_weightto[w]);
				else
					m_queue.change(w,m_weightto[w]);
			}
		}
	}
};

//class kruskal_mst
kruskal_mst::kruskal_mst(ewgraph g):m_g(g),m_weight(0.0),m_uf(g.V()){
	m_edgeofmst.reserve(g.V());
	std::vector<edge> edgs=m_g.edges();		
	for(std::vector<edge>::iterator it=edgs.begin(),end=edgs.end();it!=end;++it){
		m_pqueue.push(*it); 
	}
	while(!m_pqueue.empty()&&m_edgeofmst.size()<m_g.V()-1){
		edge e=m_pqueue.top();
		m_pqueue.pop();
		int v=e.either();
		int w=e.other(v);
		if(!m_uf.connected(v,w)){
			m_edgeofmst.push_back(e);
			m_uf.do_union(v,w);
			m_weight+=e.weight();
		}		

	}
};
