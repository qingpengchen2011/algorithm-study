#include "invert-count.hpp"
#include <iostream>
#include <fstream>
#include <vector>
int main(int argc,char* argv[]){
	std::vector<int> data;
	int t;
	std::ifstream fin(argv[1]);
	while(fin>>t){
		data.push_back(t);
	}
	std::cout<<"size of data:"<<data.size()<<std::endl;		
	int len=data.size();
	int* a=new int[len];		
  	std::copy(data.begin(),data.end(),a);	
	//int a[]={1,3,5,2,4,6};
	//int len=sizeof(a)/(sizeof(int));
	invert_count ic;
	//long r=ic.sort_count(a,len);
	std::cout<<"number of inversions:"<<ic.sort_count(a,len)<<std::endl;
//	for(int i=0;i<len;i++)
//		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
	return 0;
}
