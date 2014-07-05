#include "uf.hpp"
#include <iostream>
	
int main(int argc,char *argv[]){
	using namespace std;
	int N;
	cin>>N;
	weighted_quick_union_uf uf(N);
	int p,q;
	while(!cin.eof()){
		cin>>p>>q;
		if(!uf.connected(p,q)){
			uf.do_union(p,q);
			cout<<p<<"--"<<q<<endl;
		}
	}
	cout<<"number of components:"<<uf.count()<<endl;
	return 0;
}
