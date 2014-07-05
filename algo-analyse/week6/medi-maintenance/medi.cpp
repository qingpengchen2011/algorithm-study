#include <iostream>
#include <queue>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <stdlib.h>
#include <numeric>
#include <limits>
using namespace std;
using namespace boost;

int main(int argc, char* argv[]){
	priority_queue<int,vector<int>,greater<int> > minHeap;
	priority_queue<int,vector<int>,less<int> > maxHeap;	
	vector<int> medians;

	ifstream infile(argv[1]);
	string line;
	int l_max=numeric_limits<int>::min();
	int h_min=numeric_limits<int>::min();
	while(getline(infile,line)){
		trim(line);
		int now=atoi(line.c_str());
		if(!maxHeap.empty()){
			l_max=maxHeap.top();
		}
		if(!minHeap.empty()){
			h_min=minHeap.top();
		}
		cout<<"now:"<<now<<" l_max:"<<l_max<<" h_min:"<<h_min<<"\n";	
		if(l_max!=numeric_limits<int>::min() && now<=l_max){
			maxHeap.push(now);
			if(maxHeap.size()-minHeap.size()>=2){
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			}
		}
		
		else if (h_min!=numeric_limits<int>::min() && now>= h_min){
			minHeap.push(now);
			if(minHeap.size()-maxHeap.size()>=2){
				maxHeap.push(minHeap.top());
				minHeap.pop();
			}
		}
		else if (l_max!=numeric_limits<int>::min() && h_min!=numeric_limits<int>::min() && l_max<now && now < h_min){
			if (maxHeap.size()>minHeap.size())
				minHeap.push(now);
			else
				maxHeap.push(now);
		}
		else{
			maxHeap.push(now);
			if(maxHeap.size()-minHeap.size()>=2){
				minHeap.push(maxHeap.top());
				maxHeap.pop();
			}
		}

		cout<<"maxHeap.size():"<<maxHeap.size()<<" minHeap.size():"<<minHeap.size()<<"\n";
		//collect medians
		if(maxHeap.size()>=minHeap.size())
			medians.push_back(maxHeap.top());
		else
			medians.push_back(minHeap.top());
		
	}
	cout<<"result:"<<accumulate(medians.begin(),medians.end(),0)%10000<<"\n";		

/*
		
    minHeap.push(10);
    minHeap.push(5);
    minHeap.push(12);
    minHeap.push(3);
    minHeap.push(3);
    minHeap.push(4);
 
    while ( !minHeap.empty()){
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
*/
	return 0;
}
