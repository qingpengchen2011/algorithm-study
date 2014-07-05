#include "uf.hpp"


// class weighted_quick_union_uf

weighted_quick_union_uf::weighted_quick_union_uf(int n):m_components(n){
	int i=0;
	while(i<n){
		m_ids.push_back(i);
		++i;
	}
	m_weigth.assign(n,1);	
};


void weighted_quick_union_uf::do_union(int p,int q){
	int rp=find(p);
	int rq=find(q);
	if(rp==rq) return;
	if(rp>rq){
		m_ids[rq]=rp;	
		m_weigth[rp]+=m_weigth[rq];
	}
	else{
		m_ids[rp]=rq;
		m_weigth[rq]+=m_weigth[rp];
	}
	--m_components;
};

int weighted_quick_union_uf::find(int p){
	while(p!=m_ids[p]){
		p=m_ids[p];	
	}	
	return p;
};
