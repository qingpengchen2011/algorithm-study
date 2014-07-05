#include "indexminpq.hpp"

#include <boost/typeof/typeof.hpp>
//class index_min_pq

void index_min_pq::insert(int v,double w){
	m_container.insert(vw_value(v,w));
};


void index_min_pq::change(int v,double w){
	v_iterator it=m_container.left.find(v);
	m_container.left.replace_data(it,w);
};

bool index_min_pq::contains(int v){
	v_iterator it=m_container.left.find(v);
	return (it!=m_container.left.end()?true:false);
};

void index_min_pq::del(int v){
	m_container.left.erase(v);	
};

double index_min_pq::min(){
	return m_container.right.begin()->get<weight>();
};

int index_min_pq::min_index(){
	return m_container.right.begin()->get<vertex>();	

};

int index_min_pq::del_min(){
	w_iterator it=m_container.right.begin();
	int v=it->get<vertex>();
	m_container.right.erase(it);
	return v;	
};

void index_min_pq::clear(){
	m_container.clear();
};

bool index_min_pq::empty(){return m_container.empty();};
int index_min_pq::size(){return m_container.size();};

//LOG
void index_min_pq::show_left(){
	for(BOOST_AUTO(pos,m_container.begin());pos!=m_container.end();++pos)
		std::cout<<pos->get<vertex>()<<"->"<<pos->get<weight>()<<std::endl;
   	std::cout<<std::endl;

};

void index_min_pq::show_right(){
	for(BOOST_AUTO(pos,m_container.right.begin());pos!=m_container.right.end();++pos)
		std::cout<<pos->get<vertex>()<<"->"<<pos->get<weight>()<<std::endl;
   	std::cout<<std::endl;

};

void index_min_pq::show(){
	show_left();
	show_right();
};
