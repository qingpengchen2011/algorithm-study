#include "ewgraph.hpp"
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/bind.hpp>
int main(int argc,char* argv[]){
	std::string filename(argc>=2?argv[1]:"tinyEWG");
	ewgraph ewg(filename);
	//presentation of wegraph
	std::cout<<ewg.toString()<<std::endl;
	std::vector<edge> edges=ewg.edges();
	//for_each(edges.begin(),edges.end(),std::cout<<boost::bind(&edge::toString,boost::lambda::_1)()<<",");
	//for_each(edges.begin(),edges.end(),boost::bind(&edge::toString,_1));
	//for_each(edges.begin(),edges.end(),boost::bind(&std::operator<<,std::cout,boost::bind(&edge::toString,_1)));
	for(std::vector<edge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
		std::cout<<it->toString()<<std::endl;
	}
	std::cout<<std::endl;

	//test MST:
	std::cout<<"MST:lazy prim\n";
	lazy_prim_mst lpmst(ewg);	
	edges=lpmst.mst();
	for(std::vector<edge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
		std::cout<<it->toString()<<std::endl;
	}
	std::cout<<lpmst.weight()<<std::endl;
	std::cout<<std::endl;
	
	std::cout<<"MST:eager prim\n";
	eager_prim_mst epmst(ewg);		
	edges=epmst.mst();
	for(std::vector<edge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
		std::cout<<it->toString()<<std::endl;
	}
	std::cout<<epmst.weight()<<std::endl;
	std::cout<<std::endl;

	std::cout<<"MST:kruskal\n";
	kruskal_mst kmst(ewg);
	edges=kmst.mst();
	
	for(std::vector<edge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
		std::cout<<it->toString()<<std::endl;
	}
	std::cout<<kmst.weight()<<std::endl;
	std::cout<<std::endl;

	return 0;
}
