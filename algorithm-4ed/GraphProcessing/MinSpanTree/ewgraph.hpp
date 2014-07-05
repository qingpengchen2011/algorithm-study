#ifndef __EWGRAPH_H

#define __EWGRAPH_H
#include <stdio.h>
#include <string>
#include <vector>
#include <ostream>
#include <queue>
#include <boost/bimap.hpp>
#include "uf.hpp"
#include "indexminpq.hpp"

//presentation of edge
class edge{
	private:
		int m_v;
		int m_w;
		double m_weight;
	public:
		edge(int v,int w,double weight):m_v(v),m_w(w),m_weight(weight){};
		double weight(){return m_weight;};
		int other(int v){ return (v==m_v?m_w:m_v);};
		int either(){return m_v;};
		bool operator<(edge const& o)const{return m_weight<o.m_weight;};
		bool operator>(edge const& o)const{return !(*this<o);};
		//for template function find
		bool operator==(edge const& o)const {return m_weight==o.m_weight && (
										(m_v==o.m_v && m_w==o.m_w)||
										(m_w==o.m_v && m_v==o.m_w));};
		std::string toString() const{
			char buf[1024];
			snprintf(buf,sizeof(buf),"%d-%d: %.6f",m_v,m_w,m_weight); return std::string(buf); };
		
};
/*
std::ostream& operator<< (std::ostream& os,  edge const& e){
	os<<e.toString()<<std::endl;
	return os;
};
*/

//presentation of  edge_weight_graph
class ewgraph{
	public:
		typedef std::vector<edge> ADJLIST;
	public:
		ewgraph(int v);
		ewgraph(std::string filename);
		int V(){return m_v;};
		int E(){return m_e;};
		void addEdge(edge e);
		ADJLIST adj(int v){return m_adjTable[v];};
		std::vector<edge> edges();
		std::string toString();
	private:
		int m_v;
		int m_e;
		std::vector<ADJLIST> m_adjTable;

};


class lazy_prim_mst{
	private:
		std::vector<bool> m_marked; //weather vertex v is in the MST?
		std::priority_queue<edge,std::vector<edge>,std::greater<std::vector<edge>::value_type> >m_pq; //cross-edges including fail ones
		std::vector<edge> m_edgeofmst; //edges of MST
		ewgraph m_g;
		double m_weight; //weight of whole MST

	public:
		lazy_prim_mst(ewgraph g);
		double weight(){return m_weight;};
		std::vector<edge> mst(){return m_edgeofmst;};


	private:
		void visit(int v);//mark vertex v of MST,and add the cross-edges of vertex g



};

class eager_prim_mst{
	private:
		ewgraph m_g;
		double m_weight;
		std::vector<edge> m_edgeofmst;
		std::vector<bool> m_marked;
		std::vector<double> m_weightto;
		index_min_pq m_queue;//indexed priority queue
	public:
		eager_prim_mst(ewgraph g);
		double weight(){return m_weight;};
		std::vector<edge> mst(){return m_edgeofmst;};
	private:
		void visit(int v);

};

class kruskal_mst{	
	private:
		ewgraph m_g;
		double m_weight;
		weighted_quick_union_uf m_uf;
		std::vector<edge> m_edgeofmst;
		std::priority_queue<edge,std::vector<edge>,std::greater<std::vector<edge>::value_type> >m_pqueue; //cross-edges including fail ones
	public:
		kruskal_mst(ewgraph g);	
		double weight(){return m_weight;};					
		std::vector<edge> mst(){return m_edgeofmst;};
	
};

#endif
