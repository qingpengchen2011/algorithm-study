#ifndef __DIGRAPH_HPP
#define __DIGRAPH_HPP

#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <map>
#include <stack>
class digraph{
	public:
		typedef std::vector<int> ADJLIST; 
	private:
		int m_v;
		int m_e;
		std::vector< ADJLIST > m_adjTable;
		
	public:
		digraph(int v);
		digraph(std::string filename);
		ADJLIST adj(int v){return m_adjTable[v];};
		void addEdge(int v,int w);	
		digraph reverse();
		std::string toString();
		int V(){return m_v;};
		int E(){return m_e;};


};

class directed_dfs{

	public:
		//accessibility for directed graph,just as connectivity for undirected graph
		directed_dfs(digraph g,int s);  //single point of accessibility
		directed_dfs(digraph g,std::vector<int> sources);//multi-points of accessibility
		bool mark(int v){return marked[v];};
	private:
		digraph m_g;
		std::vector<bool> marked;	
	private:
		void di_dfs(int v);


};


class depthfirstdirectedpath{
	private:
		int m_s;
		digraph m_g;
		std::vector<bool> marked;
		std::vector<int> edge;	
	public:
		depthfirstdirectedpath(digraph g,int s);
		bool haspathto(int v){return marked[v];};
		std::vector<int> pathto(int v);
	
	private:
		void dfs(int v);
			

};

class directed_bfs{
	
	public:
		directed_bfs(digraph g,int s);
		directed_bfs(digraph g,std::vector<int> sources);
		bool mark(int v){return marked[v];};
	private:
		digraph m_g;
		std::vector<bool> marked;
	private:
		void bi_bfs(int v);

};


class breadthfirstdirectedpath{
	public:
		breadthfirstdirectedpath(digraph g,int s);
		bool haspathto(int v){return marked[v];};
		std::vector<int> pathto(int v);
	private:
		digraph m_g;
		int m_s;
		std::vector<bool> marked;
		std::vector<int> edge;
	private:
		void bfs(int v);	
};

class symbol_digraph{

        private:
                std::shared_ptr<digraph> m_pg;
                std::map<std::string,int> m_symtable; //trans string to integer
                std::vector<std::string> m_idxtable;            // integer to string

        public:
		symbol_digraph(){};
                symbol_digraph(std::string filename,std::string delim=" ");
                bool contains(std::string vertex);
                int index(std::string vertex);
                std::string name(int v){return m_idxtable[v];};
                digraph g(){return *m_pg;};
};


//-------------------------------------------------------------------
//to finger out that if this directed graph has a cycle
//directed cyclic graph detection

/*  this method can be used to detect the undirected cyclic graph as well
 *  point is:mark the vertexs that are currently on stack
 */
class directed_cycle{

	public:
		directed_cycle(digraph g);
		bool hascycle(){return !m_cycle.empty();};
		std::vector<int> cycle(){return std::vector<int>(m_cycle.begin(),m_cycle.end());};
	private:
		digraph m_g;
		std::deque<int> m_cycle;
		std::vector<bool> marked; //vertex has been checked?
		std::vector<bool> onstack;//vertex now is on stack?
		std::vector<int> edge;   //the bfs-access tree
	
	private:
		void cyclic_dfs(int v);
};

class depthfirstorder{
	
	private:
		digraph m_g;
		std::vector<bool> marked;
		std::deque<int> m_pre;
		std::deque<int> m_post;
		std::deque<int> m_reversepost;
	public:
		depthfirstorder(digraph g);
		std::vector<int> pre(){return std::vector<int>(m_pre.begin(),m_pre.end());};
		std::vector<int> post(){return std::vector<int>(m_post.begin(),m_post.end());};
		std::vector<int> reversepost(){return std::vector<int>(m_reversepost.begin(),m_reversepost.end());};
	private:
		void dfs(int v);

};


class topological{
	
	public:
		topological(digraph g);
		bool isDAG(){return m_order.empty();};//DAG:Directed acyclic graph 
		std::vector<int> order(){return m_order;};
	private:
		digraph m_g;
		std::vector<int> m_order;

};

// strong_connection_component for short scc
class kosaraju_scc{
	public:
		kosaraju_scc(digraph g);
		bool strong_connected(int v,int w){return ids[v]==ids[w];};
		int id(int v){return ids[v];};
		int countofscc(){return m_count;};

	private:
		int m_count;
		digraph m_g;
		std::vector<int> marked;
		std::vector<int> ids;
	
	private: 
		void dfs_scc(int v);

};

//can be used to determine accessibility of one pair of vertexes(points);
class transitive_closure{
	private: 
		std::vector<std::shared_ptr<directed_dfs> >  directed_dfses;
	
	public:
		transitive_closure(digraph g);	
		bool reachable(int v,int w){return directed_dfses[v]->mark(w);};

};

#endif
