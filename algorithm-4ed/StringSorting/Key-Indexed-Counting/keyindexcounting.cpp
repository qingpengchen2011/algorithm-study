#include "keyindexcounting.hpp"

keyindexcounting::keyindexcounting(array_elements_type& elements,int R):m_elements(elements),m_R(R){
	m_count.assign(m_R+1,0);
	dostatistic();
	calculateindex();
	dosort();
};

void keyindexcounting::dostatistic(){
	for(array_elements_type::const_iterator it=m_elements.begin(),end=m_elements.end();it!=end;++it){
		m_count[(*it)->first+1]++;
	}
};


void keyindexcounting::calculateindex(){
	for(int i=0;i<m_R;++i){
		m_count[i+1]+=m_count[i];
  	}
};

void keyindexcounting::dosort(){
	array_elements_type aux(m_elements.size());
	for(array_elements_type::const_iterator it=m_elements.begin(),end=m_elements.end();it!=end;++it){
		//int index=m_count[(*it)->first]++;
		//aux[index]=*it;
		aux[m_count[(*it)->first]++]=*it;
	}	
	m_elements.swap(aux);	
};
