#include "mergesort.hpp"
#include <iostream>

int main(int argc,char* argv[]){
	int a[]={1,9,0,12,4,11,5,76,10};
	int len=sizeof(a)/(sizeof(int));
	merge_sort_BU td;
	td.sort(a,len);
	for(int i=0;i<len;i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
	return 0;
}
