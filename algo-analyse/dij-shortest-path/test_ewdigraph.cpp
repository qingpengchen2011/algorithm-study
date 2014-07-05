#include "ewdigraph.hpp"
#include <iostream>


int main(int argc,char* argv[]){
	std::string filename(argc>=2?argv[1]:"tinyEWD");

        ewdigraph ewdg(filename);
	
	//shortest-path
	std::cout<<"Dijkstra shortest path\n";
	dijkstra_sp dsp(ewdg,0);
	for(int v=0;v<ewdg.V();++v){
                if(! (v==6 || v==36|| v==58 || v==81 || v==98 || v==114 || v==132 || v==164 || v==187 || v==196) )
			continue;
		std::cout<<" 0 to "<<v<<",distance:"<<dsp.dist(v)<<"|";
/*		if(dsp.haspathto(v)){
			edges=dsp.pathto(v);
			for(std::vector<diedge>::const_iterator it=edges.begin(),end=edges.end();it!=end;++it){
				std::cout<<it->toString()<<" ";
        		}
		
		}
*/
		std::cout<<std::endl;
	}			
	std::cout<<std::endl;
	
	return 0;
};
