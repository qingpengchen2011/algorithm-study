#include "keyindexcounting.hpp"
#include <iostream>
int main(int argc,char* argv[]){
	using namespace std;
	typename keyindexcounting::array_elements_type data;
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(2,"Anderson")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(3,"Brown")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(3,"Davis")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(4,"Garcia")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(1,"Harris")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(3,"Jackson")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(4,"Johnson")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(3,"Jones")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(1,"Martin")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(2,"Martinez")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(2,"Miller")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(1,"Moore")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(2,"Robinson")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(4,"Mith")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(3,"Taylor")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(4,"Thomas")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(2,"White")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(3,"Williams")));	
	data.push_back(shared_ptr<typename keyindexcounting::element_type>(new typename keyindexcounting::element_type(4,"Wilson")));	


	keyindexcounting(data,4);
	//result			
	for(typename keyindexcounting::array_elements_type::const_iterator it=data.begin(),end=data.end();it!=end;++it){
		cout<<(*it)->first<<" "<<(*it)->second<<endl;
	}
}
