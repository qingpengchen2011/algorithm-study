#ifndef __EWDIGRAPH__
#define __EWDIGRAPH__

#include<string>
#include<vector>
#include<queue>
#include<limits>
#include"indexminpq.hpp"

//directed edge
class diedge{
	public:
		diedge(int v,int w,double weight);
		int from()const{return m_v;};
		int to()const{return m_w;}; 
		double weight()const{return m_weight;};
		std::string toString()const;
	private:
		int m_v;
		int m_w;
		double m_weight;

};


class ewdigraph{
	public:
		typedef  std::vector<diedge> ADJLIST;
	public:
		ewdigraph(int v);
		ewdigraph(std::string filename);
		int V(){return m_v;};
		int E(){return m_e;};
		void addEdge(diedge e);
		ADJLIST adj(int v){return m_adjTable[v];};
		std::vector<diedge> edges();
		ewdigraph reverse_weight();
		std::string toString();
	private:
		int m_v;
		int m_e;
		std::vector<ADJLIST> m_adjTable;	


};

class dijkstra_sp{
	public:
		dijkstra_sp(ewdigraph g,int s);
		bool haspathto(int v);
		std::vector<diedge> pathto(int v);
		double dist(int v);
	private:
		ewdigraph m_g;
		int m_s;
		std::vector<diedge> m_edgeto;
		std::vector<double> m_distto;
		index_min_pq m_pq;	
	
	private:
		void visit(int v);

};


//---------------------------UTIL------------------------------------------
/* edge weighted digraph cycle detection*/
class ewdirected_cycle{

        public:
                ewdirected_cycle(ewdigraph g);
                bool hascycle(){return !m_cycle.empty();};
                std::vector<diedge> cycle(){return std::vector<diedge>(m_cycle.begin(),m_cycle.end());};
        private:
                ewdigraph m_g;
                std::deque<diedge> m_cycle;
                std::vector<bool> marked; //vertex has been checked?
                std::vector<bool> onstack;//vertex now is on stack?
                std::vector<diedge> edge;   //the dfs-access tree

        private:
                void cyclic_dfs(int v);
};

/* do depth first in edge weighted digraph*/
class ewdigraph_depthfirstorder{

        private:
                ewdigraph m_g;
                std::vector<bool> marked;
                std::deque<int> m_pre;
                std::deque<int> m_post;
                std::deque<int> m_reversepost;
        public:
                ewdigraph_depthfirstorder(ewdigraph g);
                std::vector<int> pre(){return std::vector<int>(m_pre.begin(),m_pre.end());};
                std::vector<int> post(){return std::vector<int>(m_post.begin(),m_post.end());};
                std::vector<int> reversepost(){return std::vector<int>(m_reversepost.begin(),m_reversepost.end());};
        private:
                void dfs(int v);

};

/* topological order for edge weighted digraph*/
class ewdigraph_topological{

        public:
                ewdigraph_topological(ewdigraph g);
                bool isDAG(){return m_order.empty();};//DAG:Directed acyclic graph 
                std::vector<int> order(){return m_order;};
        private:
                ewdigraph m_g;
                std::vector<int> m_order;

};

//---------------------------END UTIL------------------------------------------

//acyclic edge weighted digraph shortest path
//relax every vertex in graph's topological order
class acyclic_sp{
	public:
		acyclic_sp(ewdigraph g,int s);
		bool haspathto(int v);
		std::vector<diedge> pathto(int v);
		double dist(int v);
	private:
		int m_s;
		ewdigraph m_g;
		std::vector<double> m_distto;
		std::vector<diedge> m_edgeto;
	private:
		void relax(int v);
	
};

//longest path 
class acyclic_lp{
	public:
		acyclic_lp(ewdigraph g,int s);
		std::vector<diedge> pathto(int v);
		bool haspathto(int v);
		double dist(int v);
	private:
		std::vector<diedge> m_edgeto;
		std::vector<double> m_distto;
		int m_s;
		ewdigraph m_g;
	private:
		void relax(int v);	

};

//parallel task scheduling;; critical path
class cpm{
	public:
		cpm(std::string filename);

};

class bellman_ford_sp{
	public:
		bellman_ford_sp(ewdigraph g,int s);
		bool haspathto(int v){return m_distto[v]!=(std::numeric_limits<double>::max)();};
		std::vector<diedge> pathto(int v);
		double dist(int v){return m_distto[v];};
		
		bool hasnegativecycle(){return !m_cycle.empty();};
		std::vector<diedge> negativecycle(){return m_cycle;};
	
	private:
		std::vector<double> m_distto;
		std::vector<diedge> m_edgeto;
		std::queue<int> m_queue;
		std::vector<bool> m_onqueue;
		std::vector<diedge> m_cycle;
		ewdigraph m_g;
		int m_s;
		int m_cost;
	
	private:
		void relax(int v);			
		void findnegativecycle();

};

#endif
