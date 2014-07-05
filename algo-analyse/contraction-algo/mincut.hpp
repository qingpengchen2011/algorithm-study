#ifndef __MIN_CUT__HPP
#define __MIN_CUT__HPP

#include <memory>
#include <string>
#include <map>
#include <set>
#include <vector>
class node;
class edge{
	private:
		std::shared_ptr<node> m_v;
		std::shared_ptr<node> m_w;
	public:
		edge(std::shared_ptr<node> v,std::shared_ptr<node> w);
		void changeto(std::shared_ptr<node> old,std::shared_ptr<node> fresh);
		std::shared_ptr<node> other(std::shared_ptr<node> c);
		std::shared_ptr<node> either(){return m_v;};
		std::string edge_as_string();

};
class node:public std::enable_shared_from_this<node> {
	private:
		std::set<std::shared_ptr<edge> > m_edges;
		std::set<int> m_vertices;
	public:
		node(int v);
		node(std::set<int> vertices);
		std::set<int> get_vertices(){return m_vertices;};
		std::set<std::shared_ptr<edge> > adjacency_edges(){return m_edges;};	
		void add_vertex(int v);
		void add_vertex(std::set<int> vertices);
		void add_adjacency_edge(std::shared_ptr<edge> edge);
		void add_adjacency_edge(std::set<std::shared_ptr<edge> > edges);
		
		std::string vertices_as_string();
		std::string adjacency_node_as_string();	
};
class graph{
	private:
		std::set<std::shared_ptr<node> > m_nodes;
		std::set<std::shared_ptr<edge> > m_edges;
		std::map<int, std::shared_ptr<node> > m_vtonode;

		//for backup
		std::set<std::shared_ptr<node> > m_nodes_bk;
		std::set<std::shared_ptr<edge> > m_edges_bk;
		std::map<int, std::shared_ptr<node> > m_vtonode_bk;

	public:
		graph(){};
		graph(std::string filename);
		void add_edge(int v,int w);	

		void show_graph();
		void show_bk_graph();
		int num_v(){return m_nodes.size();};
		int num_edge(){return m_edges.size();};

		int karger_constraction();
		int mincut();
		void select_edge_to_constrac();
	
	private:
		void backup_graph(){
			m_nodes_bk=m_nodes;
			m_edges_bk=m_edges;
			m_vtonode_bk=m_vtonode;
		};
		void reset_graph(){
			m_nodes=m_nodes_bk;
			m_edges=m_edges_bk;
			m_vtonode=m_vtonode_bk;	
		};
		void constract(std::shared_ptr<edge> sel_edge);
		bool parallel_edge(std::shared_ptr<edge> one,std::shared_ptr<edge> two);
		void update_vtonode(std::shared_ptr<node> old,std::shared_ptr<node> n);
		bool vertex_contained(int v);
		std::shared_ptr<node> vtonode(int v); 
		std::shared_ptr<edge> exist_edge(std::shared_ptr<node> v,std::shared_ptr<node> w);
};

#endif

