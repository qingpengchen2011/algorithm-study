#include "graph.hpp"

int main(int argc,char* argv[]){
	
	std::string filename(argc>=2?argv[1]:"tinyG");
	symbol_graph sg(filename,"/");	
	
//	std::ifstream in(filename);
//	graph g(in);
	graph g(sg.g());
	std::string str_graph=g.toString();
	std::cout<<str_graph<<std::endl;
	//dfs
	depthfirstsearch dfs(g,0);
	for(int i=0;i<g.num_v();++i){
		if(dfs.connect(i))
			std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	if(g.num_v()!=dfs.count())
		std::cout<<"NOT CONNECTED!!"<<std::endl;
	std::cout<<std::endl;

	//dfs-p
	depthfirstpath dfsp(g,0);
	for(int i=0;i<g.num_v();++i){
		if(dfsp.haspathto(i)){
			std::vector<int> path=dfsp.pathto(i);
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
	breadfirstsearch bfs(g,0);
	for(int i=0;i<g.num_v();++i){
		if(dfs.connect(i))
			std::cout<<i<<" ";
	}
	std::cout<<std::endl;
	if(g.num_v()!=bfs.count())
		std::cout<<"NOT CONNECTED!!"<<std::endl;
	std::cout<<std::endl;

	//bfs_p
	breadfirstpath bfsp(g,0);	
	for(int i=0;i<g.num_v();++i){
		if(bfsp.haspathto(i)){
			std::vector<int> path=bfsp.pathto(i);
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

	//connection_component
	connection_component cc(g);
	int n=cc.countofcc();
	std::cout<<n<<" components"<<std::endl;	
	std::vector<std::vector<int> > components(n,std::vector<int>());
	for(int i=0;i<g.num_v();++i){
		components[cc.id(i)].push_back(i);	
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
	
	//color_graph
	twocolor_graph cg(g);
	if(cg.bipartitegraph()){
		std::cout<<"this is a bipartite graph"<<std::endl;
	}
	else{
		std::cout<<"unable to be bipartite graph"<<std::endl;
	}	
	std::cout<<std::endl;
	
	return 0;
}
