#include "mincut.hpp"
#include <utility>
#include <iostream>
#include <locale>
#include <sstream>
#include <algorithm>
#include <functional>
#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <limits>
#include <time.h>

//class edge
edge::edge(std::shared_ptr<node> v, std::shared_ptr<node> w):m_v(v),m_w(w){

};

std::shared_ptr<node> edge::other(std::shared_ptr<node> c){
	if(c==m_v)
		return m_w;
	else
		return m_v;
};

void edge::changeto(std::shared_ptr<node> old,std::shared_ptr<node> fresh){
	if(old==m_w)
		m_w=fresh;
	else
		m_v=fresh;
};
std::string edge::edge_as_string(){
	std::ostringstream out;
	out<<m_v->vertices_as_string()<<" ---- "<<m_w->vertices_as_string();	
	return out.str();
};
//class node
node::node(int v){
	m_vertices.insert(v);
};
node::node(std::set<int> vertices){
	add_vertex(vertices);
};
void node::add_vertex(std::set<int> vertices){
	m_vertices.insert(vertices.begin(),vertices.end());
};
std::string node::vertices_as_string(){
	std::ostringstream out;
	for(std::set<int>::iterator it(m_vertices.begin()),end(m_vertices.end());it!=end;++it){
		out<<*it<<" ";
	}
	return out.str();
};

std::string node::adjacency_node_as_string(){
	std::ostringstream out;
	for(std::set<std::shared_ptr<edge> >::iterator it(m_edges.begin()),end(m_edges.end());it!=end;++it){
		std::shared_ptr<node> o=(*it)->other(shared_from_this());
		out<<o->vertices_as_string()<<"|";
	}
	return out.str();

};
void node::add_adjacency_edge(std::shared_ptr<edge> edge){
	m_edges.insert(edge);
};

void node::add_adjacency_edge(std::set<std::shared_ptr<edge> > edges){
	m_edges.insert(edges.begin(),edges.end());
};


//class graph
graph::graph(std::string filename){
  		std::ifstream in(filename);
        std::string line;
        //construct the two tables;     
        while(std::getline(in,line)){
 		boost::trim(line);
		//std::cout<<"line:"<<line<<"\n";
                std::vector<std::string> vStr;
                boost::split(vStr,line,boost::is_any_of(" \t"),boost::token_compress_on);
		int v=atoi((*vStr.begin()).c_str());
                for( std::vector<std::string>::iterator it = vStr.begin()+1; it != vStr.end(); ++it ){
			int w=atoi((*it).c_str());
		//	std::cout<<"adding "<<v<<","<<w<<"\n";
			add_edge(v,w);
                }
        }
		
		//backup_graph();
};

void graph::add_edge(int v,int w){
	bool v_in=vertex_contained(v);
	bool w_in=vertex_contained(w);
	if(!v_in && !w_in){  //this two vertices are not in graph
		//std::cout<<"cond1:"<<v<<","<<w<<"\n";
		std::shared_ptr<node> v_node(new node(v));
		std::shared_ptr<node> w_node(new node(w));	
		std::shared_ptr<edge> vw_edge(new edge(v_node,w_node));
		v_node->add_adjacency_edge(vw_edge);
		w_node->add_adjacency_edge(vw_edge);
		//store these new objects
		m_nodes.insert(v_node);
		m_nodes.insert(w_node);
		m_edges.insert(vw_edge);
		m_vtonode.insert(std::make_pair(v,v_node));
		m_vtonode.insert(std::make_pair(w,w_node));
	}
	else if(!v_in && w_in){	
		//std::cout<<"cond2:"<<v<<","<<w<<"\n";
		std::shared_ptr<node> v_node(new node(v));
		std::shared_ptr<node> w_node=vtonode(w);
		std::shared_ptr<edge> vw_edge(new edge(v_node,w_node));
		v_node->add_adjacency_edge(vw_edge);
		w_node->add_adjacency_edge(vw_edge);
		m_nodes.insert(v_node);
		m_edges.insert(vw_edge);
		m_vtonode.insert(std::make_pair(v,v_node));
	}
	else if(v_in && !w_in){
		//std::cout<<"cond3:"<<v<<","<<w<<"\n";
		std::shared_ptr<node> w_node(new node(w));	
		std::shared_ptr<node> v_node=vtonode(v);
		std::shared_ptr<edge> vw_edge(new edge(v_node,w_node));
		v_node->add_adjacency_edge(vw_edge);
		w_node->add_adjacency_edge(vw_edge);
		m_nodes.insert(w_node);
		m_edges.insert(vw_edge);
		m_vtonode.insert(std::make_pair(w,w_node));
	}
	else{

		//std::cout<<"cond4:"<<v<<","<<w<<"\n";
		std::shared_ptr<node> w_node=vtonode(w);
		std::shared_ptr<node> v_node=vtonode(v);
		std::shared_ptr<edge> ed=exist_edge(v_node,w_node);
		if(ed.get()!=NULL)
			return;
		else{
			std::shared_ptr<edge> vw_edge(new edge(v_node,w_node));
			v_node->add_adjacency_edge(vw_edge);
			w_node->add_adjacency_edge(vw_edge);
			m_edges.insert(vw_edge);
		}
		
	}

};
void graph::show_graph(){
	std::cout<<"has "<<num_v()<<" vertices,and "<<num_edge()<<" edges\n";
	for(std::set<std::shared_ptr<node> >::iterator it(m_nodes.begin()),end(m_nodes.end());it!=end;++it){
		std::cout<<(*it)->vertices_as_string()<< " : "<<(*it)->adjacency_node_as_string()<<"\n";
	}	
};

void graph::show_bk_graph(){
	std::cout<<"bk_graph has "<<num_v()<<" vertices,and "<<num_edge()<<" edges\n";
	for(std::set<std::shared_ptr<node> >::iterator it(m_nodes_bk.begin()),end(m_nodes_bk.end());it!=end;++it){
		std::cout<<(*it)->vertices_as_string()<< " : "<<(*it)->adjacency_node_as_string()<<"\n";
	}	
};
	//private
bool graph::vertex_contained(int v){
	return m_vtonode.find(v)!=m_vtonode.end();
};

std::shared_ptr<node> graph::vtonode(int v){
	return (*(m_vtonode.find(v))).second;
};

std::shared_ptr<edge> graph::exist_edge(std::shared_ptr<node> v,std::shared_ptr<node> w){
	for(std::set<std::shared_ptr<edge> >::iterator it(m_edges.begin()),end(m_edges.end());it!=end;++it){
		std::shared_ptr<node> one=(*it)->either();
		std::shared_ptr<node> second=(*it)->other(one);
		if( (one==v && second==w) || (one==w && second==v))
			return *it;	
	}
	return std::shared_ptr<edge>(NULL);
};

//contraction algorithm
void graph::constract(std::shared_ptr<edge> e){
	std::shared_ptr<node> v_node(e->either());
	std::shared_ptr<node> w_node(e->other(v_node));
	std::shared_ptr<node> new_node(new node(v_node->get_vertices()));
	new_node->add_vertex(w_node->get_vertices());
	//std::cout<<"new node:"<<new_node->vertices_as_string()<<"\n";
	std::set<std::shared_ptr<edge> > edges_to_erase;	
	edges_to_erase.insert(e);
	//update edges's node	
	std::set<std::shared_ptr<edge> > adj_edges=v_node->adjacency_edges();
	for(std::set<std::shared_ptr<edge> >::iterator it(adj_edges.begin()),end(adj_edges.end());it!=end;++it){
		if(parallel_edge(e,*it)){
			edges_to_erase.insert(*it);		
		}	
		else{
			//std::cout<<"before changeto:"<<(*it)->edge_as_string()<<"\n";
			(*it)->changeto(v_node,new_node);
		//	std::cout<<"after changeto:"<<(*it)->edge_as_string()<<"\n";
			new_node->add_adjacency_edge(*it);
		}
	}
	adj_edges=w_node->adjacency_edges();
	for(std::set<std::shared_ptr<edge> >::iterator it(adj_edges.begin()),end(adj_edges.end());it!=end;++it){
		if(parallel_edge(e,*it)){
			edges_to_erase.insert(*it);		
		}	
		else{
			//std::cout<<"before changeto:"<<(*it)->edge_as_string()<<"\n";
			(*it)->changeto(w_node,new_node);
			//std::cout<<"after changeto:"<<(*it)->edge_as_string()<<"\n";
			new_node->add_adjacency_edge(*it);
		}
	}
	//erase parall edges
	for(std::set<std::shared_ptr<edge> >::iterator it(edges_to_erase.begin()),end(edges_to_erase.end());it!=end;++it){
		m_edges.erase(*it);
	}
	//m_edges.erase(edges_to_erase.begin(),edges_to_erase.end());
	//update vertex - node map
	update_vtonode(v_node,new_node);
	update_vtonode(w_node,new_node);	
	//update graph nodes
	m_nodes.erase(v_node);
	m_nodes.erase(w_node);
	m_nodes.insert(new_node);
	return;
};

bool graph::parallel_edge(std::shared_ptr<edge> one,std::shared_ptr<edge> two){
	std::shared_ptr<node> one_v=one->either();	
	std::shared_ptr<node> two_v=two->either();
	std::shared_ptr<node> one_w=one->other(one_v);
	std::shared_ptr<node> two_w=two->other(two_v);
	if( (one_v==two_v && one_w==two_w) || (one_w==two_v && one_v == two_w))
		return true;
	return false;
};

void graph::update_vtonode(std::shared_ptr<node> old,std::shared_ptr<node> n){
	std::set<int> vertices=old->get_vertices();
	for(std::set<int>::iterator it(vertices.begin()),end(vertices.end());it!=end;++it){
		m_vtonode[*it]=n;
	}
};

void graph::select_edge_to_constrac(){
	int n=num_edge();	
	srand (time(NULL));
	std::set<std::shared_ptr<edge> >::iterator it=m_edges.begin();
	std::advance(it,rand()%n);
//	std::cout<<"selected edge:"<<(*it)->edge_as_string()<<"\n";
	constract(*it);
	//std::cout<<"new graph:\n";
	//show_graph();
};

int graph::mincut(){
	int min=std::numeric_limits<int>::max();
	while(num_v()>2){
		select_edge_to_constrac();	
		int c=num_edge();
		if(c < min)
			min=c;
	}
	return min;
};

int graph::karger_constraction(){
	int n=num_v();
	long times=(long)(n*(n-1)/2*log((double)n));
	long i=0;
	int min=std::numeric_limits<int>::max();
	graph tmp(*this);
	while(i<times){
		std::cout<<"!!before run mincut\n";
		show_graph();
		int c=mincut();
		std::cout<<"!!round "<<i<<" --> "<<c<<std::endl;
		if(c<min)
			min=c;
		i++;
		//std::cout<<"!!after run mincut\n";
		//show_graph();
		//std::cout<<"!!after run mincut,see bk_graph\n";
		//tmp.show_graph();
		reset_graph();
	}

	return min;
}
