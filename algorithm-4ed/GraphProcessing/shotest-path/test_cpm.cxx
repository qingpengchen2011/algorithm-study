#include "ewdigraph.hpp"
#include <string>
#include <boost/algorithm/string.hpp>
int main(int argc, char* argv[]){
	std::ifstream in(std::string(argv[1]));
        int v=0;
        in>>v;
        int s=2*v,t=2*v+1;
        std::string line;
        //construct the graph
        ewdigraph g(2*v+2);
        for(int i=0;i<v;++i){
                std::getline(in,line);
                std::vector<std::string> vStr;
                boost::split(vStr,line,boost::is_any_of(std::string(" ")));
                g.addEdge(diedge(i,i+v,atof(vStr[0].c_str())));
                g.addEdge(diedge(s,i,0.0));
                g.addEdge(diedge(i+v,t,0.0));
                for( std::vector<std::string>::iterator it = vStr.begin()+1; it != vStr.end(); ++ it ){
                        g.addEdge(diedge(i+v,atoi(it->c_str()),0.0));
                }


        }

        //finish construct the graph
        acyclic_lp lp(g,s);
        std::cout<<"start times:\n";
        for(int i=0;i<v;++i){
                std::cout<<i<<" : "<<lp.dist(i)<<std::endl;
        }
        std::cout<<"finish time:"<<lp.dist(t)<<std::endl;

	return 0;
}
