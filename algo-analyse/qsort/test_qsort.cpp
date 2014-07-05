#include "qsort.hpp"
#include <iostream>
#include <vector>
#include <fstream>

int main(int argc,char* argv[]){
//	int a[]={5,43,1,6,2,0,90};
//	int len=sizeof(a)/(sizeof(int));

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

	quicksort qs;
	qs.sort(a,len);
	int line=0;
	for(int i=0;i<len;i++){
        	std::cout<<a[i]<<" ";
		if(++line%10 ==0){
			line=0;
			std::cout<<std::endl;
		}
	}
        std::cout<<std::endl;
	
	std::cout<<"number of comparsion:"<<qs.compare_count<<std::endl;

	return 0;
};
