#include "ewdigraph.hpp"
#include <iostream>


int main(int argc,char* argv[]){
	std::string filename(argc>=2?argv[1]:"tinyEWD");
//	cpm p(filename);

        ewdigraph ewdg(filename);
        //presentation of wegraph
        std::cout<<ewdg.toString()<<std::endl;
        std::vector<diedge> edges=ewdg.edges();
        for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
                std::cout<<it->toString()<<std::endl;
        }
        std::cout<<std::endl;
	/*	
	//shortest-path
	std::cout<<"Dijkstra shortest path\n";
	dijkstra_sp dsp(ewdg,0);
	for(int v=0;v<ewdg.V();++v){
		std::cout<<" 0 to "<<v<<",distance:"<<dsp.dist(v)<<"|";
		if(dsp.haspathto(v)){
			edges=dsp.pathto(v);
			for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
				std::cout<<it->toString()<<" ";
        		}
		
		}
		std::cout<<std::endl;
	}			
	std::cout<<std::endl;
	*/	
	//test for cycle detection
	std::cout<<"cycle detection\n";
	ewdirected_cycle ewdi_cycle(ewdg);
	if(ewdi_cycle.hascycle()){
		edges=ewdi_cycle.cycle();
		 for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
                std::cout<<it->toString()<<std::endl;
        }
        std::cout<<std::endl;
	}
	

	//acyclic shortest-path
	std::cout<<"acyclic sp\n";
	acyclic_sp asp(ewdg,0);				
	for(int v=0;v<ewdg.V();++v){
		std::cout<<" 0 to "<<v<<",distance:"<<asp.dist(v)<<"|";
		if(asp.haspathto(v)){
			edges=asp.pathto(v);
			for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
				std::cout<<it->toString()<<" ";
        		}
		
		}
		std::cout<<std::endl;
	}			
	std::cout<<std::endl;

	//acyclic longest-path
	std::cout<<"acyclic longest path:\n";
	acyclic_lp alp(ewdg,0);
	for(int v=0;v<ewdg.V();++v){
		std::cout<<" 0 to "<<v<<",distance:"<<alp.dist(v)<<"|";
		if(alp.haspathto(v)){
			edges=alp.pathto(v);
			for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
				std::cout<<it->toString()<<" ";
        		}
		
		}
		std::cout<<std::endl;
	}			
	std::cout<<std::endl;
		

	std::cout<<"run cpm for jobsPC file\n";
	cpm p("jobsPC");

	//bellman_ford_sp 
	std::cout<<"bellman_ford shortest path\n";
	bellman_ford_sp bellsp(ewdg,0);
	if(bellsp.hasnegativecycle()){
		std::cout<<"detect a negative cycle:\n";
		edges=bellsp.negativecycle();
		for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
				std::cout<<it->toString()<<" ";
        	}
	}
	else{
		std::cout<<"no negative-cycle,shortest path is:\n";	
		for(int v=0;v<ewdg.V();++v){
			std::cout<<" 0 to "<<v<<",distance:"<<bellsp.dist(v)<<"|";
			if(bellsp.haspathto(v)){
				edges=bellsp.pathto(v);
				for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
					std::cout<<it->toString()<<" ";
        			}
		
			}
			std::cout<<std::endl;
		}			
	}		
	std::cout<<std::endl;

		
	return 0;
};
