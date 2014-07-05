#include "mincut.hpp"
#include <iostream>
#include <math.h>
int main(int argc,char* argv[]){
	std::cout<<argv[1]<<std::endl;
	graph g(argv[1]);
	int n=g.num_v();
	std::cout<<"number of vertices: "<<n<<std::endl;
	std::cout<<"see graph\n";
//	g.show_graph();
	long long times=(long long)(n*n*log((double)n));
	std::cout<<"about to do "<<times<<std::endl;
	int min=g.mincut();
	std::cout<<"!!round "<<0<<" value:"<<min<<"\n";
	long long  i=1;
	graph* gp;
	while(i<times){
 	    {
		//graph g(argv[1]);
		gp=new graph(argv[1]);
		int c=gp->mincut();
		std::cout<<"!!round "<<i<<" value:"<<c<<"\n";
		if (c<min)
			min=c;
	    }
		i++;
		delete gp;
	}
	std::cout<<"@@get min value "<<min<<std::endl;
	//g.select_edge_to_constrac();
	//std::cout<<"get min cut:"<<g.karger_constraction()<<std::endl;
	return 0;
}
