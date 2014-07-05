#include "digraph.hpp"
#include <iostream>

int main(int argc,char* argv[]){
	
	std::string filename(argc>=2?argv[1]:"tinyDG");
	//digraph
	digraph dg(0);	
	symbol_digraph sdg;
	if(argc>=2){
	static symbol_digraph lsdg(filename,"/");
		dg=lsdg.g();
		sdg=lsdg;
	}
	else{
		dg=digraph(filename);	
	}
	std::cout<<dg.toString()<<std::endl;
	std::cout<<"reverse of G:"<<std::endl;
	std::cout<<dg.reverse().toString()<<std::endl;
	
	//directed dfs
{
	std::cout<<"DFS:single poit accessbility\n";
	directed_dfs didfs(dg,0);	
	for(int i=0;i<dg.V();++i){
		if(didfs.mark(i)){
			std::cout<<i<<" ";	
		}
	}	
	std::cout<<std::endl;
}
{
	std::cout<<"DFS:multi-point accessibility\n";
	std::vector<int> srcs;
	srcs.push_back(0);
	srcs.push_back(1);
	srcs.push_back(6);
	directed_dfs didfs(dg,srcs);	
	for(int i=0;i<dg.V();++i){
		if(didfs.mark(i)){
			std::cout<<i<<" ";	
		}
	}	
	std::cout<<std::endl;
	std::cout<<std::endl;
}
	//dfs-dp; directed path
	std::cout<<"DFS:directed path\n";
	depthfirstdirectedpath dfsdp(dg,0);
        for(int i=0;i<dg.V();++i){
                if(dfsdp.haspathto(i)){
                        std::vector<int> path=dfsdp.pathto(i);
                        std::cout<<"0 to "<<i<<" :";
                        for(int j=0;j<path.size();++j){
                                int w=path[j];
                                if(w==i)
                                        std::cout<<i<<std::endl;
                                else
                                        std::cout<<w<<'-';
                        }
                }
        }
        std::cout<<std::endl;
	//bfs
		
{
	std::cout<<"BFS:single poit accessbility\n";
	directed_bfs dibfs(dg,0);	
	for(int i=0;i<dg.V();++i){
		if(dibfs.mark(i)){
			std::cout<<i<<" ";	
		}
	}	
	std::cout<<std::endl;
}
{
	std::cout<<"BFS:multi-point accessibility\n";
	std::vector<int> srcs;
	srcs.push_back(0);
	srcs.push_back(1);
	srcs.push_back(6);
	directed_bfs dibfs(dg,srcs);	
	for(int i=0;i<dg.V();++i){
		if(dibfs.mark(i)){
			std::cout<<i<<" ";	
		}
	}	
	std::cout<<std::endl;
	std::cout<<std::endl;
}

	
	//bfs-dp; directed path
	std::cout<<"BFS:directed path\n";
	breadthfirstdirectedpath bfsdp(dg,0);
        for(int i=0;i<dg.V();++i){
                if(bfsdp.haspathto(i)){
                        std::vector<int> path=bfsdp.pathto(i);
                        std::cout<<"0 to "<<i<<" :";
                        for(int j=0;j<path.size();++j){
                                int w=path[j];
                                if(w==i)
                                        std::cout<<i<<std::endl;
                                else
                                        std::cout<<w<<'-';
                        }
                }
        }
        std::cout<<std::endl;

	//dfs:detect directed cyclic graph 
	directed_cycle dicyc(dg);
	std::cout<<"DFS:cyclic graph detection\n";
	if(dicyc.hascycle()){
		std::cout<<"has CYCLE:";
		const std::vector<int>& cyc=dicyc.cycle();
		for( std::vector<int>::const_iterator it=cyc.begin(),end=cyc.end();it!=end;++it){
			std::cout<<*it<<" ";
		}
		std::cout<<std::endl;
	}
	else{
		std::cout<<"This directed graph is not cyclic\n";
	}
        std::cout<<std::endl;

	//dfs:depth-first-order
	depthfirstorder dfo(dg);
	std::cout<<"DFS:depth first order\n";	
	std::cout<<"pre-order\n";
	const std::vector<int>& preorder=dfo.pre();
	for(std::vector<int>::const_iterator it=preorder.begin(),end=preorder.end();it!=end;++it){
		std::cout<<*it<<" ";
	}		
        std::cout<<std::endl;
	std::cout<<"post-order\n";
	const std::vector<int>& postorder=dfo.post();
	for(std::vector<int>::const_iterator it=postorder.begin(),end=postorder.end();it!=end;++it){
		std::cout<<*it<<" ";
	}		
        std::cout<<std::endl;
	std::cout<<"reserve-pre-order\n";
	const std::vector<int>& reservepreorder=dfo.reversepost();
	for(std::vector<int>::const_iterator it=reservepreorder.begin(),end=reservepreorder.end();it!=end;++it){
		std::cout<<*it<<" ";
	}		
        std::cout<<std::endl;
        std::cout<<std::endl;

	//dfs:topological
	std::cout<<"DFS:topological\n";
	topological topo(dg);
	const std::vector<int>& order=topo.order();
	for(std::vector<int>::const_iterator it=order.begin(),end=order.end();it!=end;++it){
		if(argc>=2){
			std::cout<<sdg.name(*it)<<std::endl;
		}
		else{
			std::cout<<*it<<std::endl;	
		}		
		
	}						
        std::cout<<std::endl;


	//strong_connection_component 
	std::cout<<"kosaraje:strong_connection_component\n";	
	kosaraju_scc scc(dg);
	int n=scc.countofscc();
        std::cout<<n<<" components"<<std::endl;
        std::vector<std::vector<int> > components(n,std::vector<int>());
        for(int i=0;i<dg.V();++i){
                components[scc.id(i)].push_back(i);
        }
        for(int i=0;i<components.size();++i){
                std::vector<int>& component=components[i];
                std::cout<<"component "<<i<<" :";
                for(int j=0;j<component.size();++j){
                        std::cout<<component[j]<<" ";
                }
                std::cout<<std::endl;
        }

        std::cout<<std::endl;

	//accessibility of paired vertex
	std::cout<<"DFS:accessibility of paired vertex\n";
	transitive_closure tc(dg);
	for(int v=0;v<dg.V();++v){
		std::cout<<"vertex "<<v<<" can reach to :";
		for(int w=0;w<dg.V();++w){
			if(tc.reachable(v,w))
				std::cout<<w<<" ";	
		}
		std::cout<<std::endl;
	}		
	std::cout<<std::endl;

	return 0;
}
