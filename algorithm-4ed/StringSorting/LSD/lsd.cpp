#include "lsd.hpp"

lsd::lsd(std::vector<std::string>& array_string,int w,int len):m_array_string(array_string),m_w(w),m_len(len){
	init_part_array();
	for(int i=0;i<m_w;++i){
		construct_part_array(m_len-i-1);	
		keyindexcounting kic(m_part_array,256);
	}	

	for(int i=0;i<m_part_array.size();++i){
		m_array_string[i]=m_part_array[i]->second;
	}	
};

void lsd::init_part_array(){
	for(int i=0;i<m_array_string.size();++i){
		m_part_array.push_back(std::shared_ptr<element_type>(new element_type(0,m_array_string[i])));
	}
};

void lsd::construct_part_array(int key_index){
	for(int i=0;i<m_part_array.size();++i){
		int key=m_part_array[i]->second[key_index];
		m_part_array[i]->first=key;	

	}	

};
