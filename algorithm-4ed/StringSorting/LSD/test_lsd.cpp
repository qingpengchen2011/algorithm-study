#include "lsd.hpp"
#include <fstream>
#include <iostream>
int main(int argc,char* argv[]){
	std::vector<std::string> data;
	std::string word;

	std::ifstream in("words3");
	while(!in.eof()){
		in>>word;
		data.push_back(word);	
	}
	
	lsd ins_lsd(data,3,3);
	for(int i=0;i<data.size();++i){
		std::cout<<data[i]<<std::endl;
	}
}
