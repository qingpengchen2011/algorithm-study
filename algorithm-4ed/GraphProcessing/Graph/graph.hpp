#ifndef __GRAPH_HPP

#define __GRAPH_HPP

#include<vector>
#include<fstream>
#include<iostream>
#include<string>
#include<map>
#include<memory>

//presentation of undirected graph
class graph{
	public:
		typedef std::vector<int> ADJLIST;
	private:
		int m_v;
		int m_e;
		std::vector<ADJLIST> adjTable;
	
	public:
		graph(int v);
		graph(std::ifstream& in);
		int num_v(){return m_v;};
		int num_e(){return m_e;};
		void addEdge(int v,int w);
		ADJLIST adjlist(int v){return adjTable[v];};
		std::string toString();		
	
	private:
		void init();
};


class depthfirstsearch{
	public:
		depthfirstsearch(graph g,int s);
		bool connect(int v); //v connect to s ?
		int count();//number of vertexs connect to s

	private:
		graph m_g;
		int m_s;//source vertex
		int m_count;
		std::vector<bool> mark;
	private:
		void dfs(int v);
		
};


class depthfirstpath{
	public:
		depthfirstpath(graph g,int s);
		bool haspathto(int v);
		std::vector<int> pathto(int v);
	private:
		int m_s;
		graph m_g;
		std::vector<bool> mark;
		std::vector<int> edgeto;//this is a tree,the value of edgeto[n] points to node n's father node
	private:
		void dfs_p(int v);		

};

class breadfirstsearch{
	
	private:
		graph m_g;
		int m_s;
		int m_count;
		std::vector<bool> mark;
		
	public:
		breadfirstsearch(graph g,int s);
		bool connect(int v){return mark[v];};
		int count(){return m_count;};
	private:
		void bfs(int s);

};

class breadfirstpath{
	private:
		graph m_g;
		int m_s;
		std::vector<bool> mark;
		std::vector<int> edgeto;
	public:
		breadfirstpath(graph g,int s);
		bool haspathto(int v){return mark[v];};
		std::vector<int> pathto(int v);
	private:
		void bfs_p(int s);
		

};



class connection_component{	
	private:
		graph m_g;
		int m_count;
		std::vector<bool> mark;
		std::vector<int> ids;  
	public:
		connection_component(graph g);
		bool connected(int s,int v);//vertex v and s are connected?
		int id(int v); //which connection_component, vertex v belongs to
		int countofcc(); //number of connection_component
	private:
		void dfs_cc(int s);

};

class cycle_graph{

};

class twocolor_graph{

	private:
		bool istwocolorable;
		graph m_g;
		std::vector<bool> mark;
		std::vector<bool> color;
	
	public:
		twocolor_graph(graph g);
		bool bipartitegraph(){return istwocolorable;};
	
	private:
		void dfs_twocolor(int s);
	

};


class symbol_graph{

	private:
		std::shared_ptr<graph> m_pg;
		std::map<std::string,int> m_symtable; //trans string to integer
		std::vector<std::string> m_idxtable;		// integer to string
		
	public:
		symbol_graph(std::string filename,std::string delim=" ");
		bool contains(std::string vertex);
		int index(std::string vertex);
		std::string name(int v){return m_idxtable[v];};
		graph g(){return *m_pg;};
};
#endif
