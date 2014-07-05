#include <boost/unordered_set.hpp>
#include <fstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <iostream>

using namespace std;
using namespace boost;

int satisfy(long target,boost::unordered_multiset<long long>& sets){
	for(auto it=sets.begin(),end=sets.end();it!=end;++it){
		long long t=*it;
		long long t_minus=target - t;
		if (t==t_minus) 
			continue;	
		if(sets.find(t_minus)!=sets.end())
			return true;	
	}
	return false;
}

int main(int argc,char* argv[]){
	boost::unordered_multiset<long long> sets;
	std::ifstream infile(argv[1]);
        std::string line;
        while(std::getline(infile,line)){
                trim(line);
//		std::cout<<atoll(line.c_str())<<"\n";
                sets.insert(atoll(line.c_str()));
        }
	std::cout<<sets.size()<<"\n";
	long start=-10000,end=10000+1;
	long number=0;
	while(start<end){
		std::cout<<"start:"<<start<<"\n";
		if(satisfy(start,sets))
			++number;
		++start;

	}	
	std::cout<<number<<"\n";
	return 0;
}

