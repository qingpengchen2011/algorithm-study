#ifndef __INDEX_MIN_PQ_HPP
#define __INDEX_MIN_PQ_HPP
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

using namespace boost;
using namespace boost::bimaps;
class index_min_pq{

	private:
		struct vertex{};
		struct weight{};
		typedef bimap<
				tagged<int,vertex>,
				multiset_of<tagged<double,weight> >
			> vw_container;		
		typedef vw_container::value_type vw_value;
		typedef vw_container::map_by<vertex>::const_iterator v_const_iterator;
		typedef vw_container::map_by<vertex>::iterator v_iterator;
		typedef vw_container::map_by<weight>::const_iterator w_const_iterator;
		typedef vw_container::map_by<weight>::iterator w_iterator;	


	
	public:
		void insert(int v,double w); //insert vertex v with weight w 
		void change(int v,double w); //change the vertex v's weight to w
		bool contains(int v); //we contain vertex v in container right now?
		void del(int v);   //remove vertex v and its associated weight from container
		double min();         //return the min weight
		int min_index();     //return the index v of the min weight
		int del_min();	     // return index v of the min weight and remove it and its associated weight value out of container
		bool empty();        //our container is empty?	
		int size();          // current elements in our container	

		void clear();

    		//LOG:
		void show_left();
		void show_right();
		void show();
	private:
		vw_container m_container;
		

};

#endif
