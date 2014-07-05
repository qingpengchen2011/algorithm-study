#include "select.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>

int main(int argc,char* argv[]){
//	int a[]={5,43,1,6,2,0,70,80};
//	int len=sizeof(a)/(sizeof(int));
/*
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
*/
	for(int c=0;c<10;c++){
	int len=rand()%1000+1000;
	std::cout<<"about to genereate:"<<len<<" data\n";
	int* a=new int[len];
	for(int i=0;i<len;++i)
		a[i]=i;
	std::random_shuffle(a,a+len);
//	Rselect rs;
//	std::cout<<"Rselect:"<<argv[1]<<"th:"<<rs.select(a,len,atoi(argv[1]))<<std::endl;
	
	Dselect ds;
	std::cout<<"Dselect:"<<argv[1]<<"th:"<<ds.select(a,len,atoi(argv[1]))<<std::endl;
	delete[] a;
	}
	return 0;
};
