#include "select.hpp"
#include <utility>
#include <cstdlib>
#include <algorithm>
int Rselect::select(int*a,int len,int i){
	return mselect(a,0,len-1,i);
};

int Rselect::mselect(int*a ,int lo,int hi, int i){
	if(lo==hi)
		return a[lo];
	choosepivot(a,lo,hi);
	int p=partition(a,lo,hi);
	int ith_p=p-lo+1;	//order statistic of arrary[lo..hi]
	if(ith_p==i)
		return a[p];
	else if (ith_p>i)
		return  mselect(a,lo,p-1,i);
	else
		return mselect(a,p+1,hi,i-ith_p);
	
};

void Rselect::choosepivot(int *a,int lo,int hi){
	int c=rand()%(hi-lo+1)+lo;
	std::swap(a[lo],a[c]);	
	return ;
};

int Rselect::partition(int*a ,int lo,int hi){	
	int i=lo+1;
	for(int j=lo+1;j<=hi;++j){
		if(a[j]<a[lo]){
			std::swap(a[i],a[j]);
			++i;
		}
	}
	std::swap(a[i-1],a[lo]);
	return i-1;
			
};


//-----D SELECT
int Dselect::select(int* a,int len,int i){
	return mselect(a,0,len-1,i);
};

int Dselect::mselect(int *a,int lo,int hi,int i){
	if(lo==hi)
		return a[lo];
	choosepivot(a,lo,hi);
	int p=partition(a,lo,hi);
	int ith_p=p-lo+1;	
	if(i==ith_p)
		return a[p];
	else if (ith_p>i)
		return mselect(a,lo,p-1,i);
	else
		return mselect(a,p+1,hi,i-ith_p);	

};


int Dselect::partition(int* a,int lo,int hi){
	int i=lo+1;
	for(int j=lo+1;j<=hi;++j){
		if(a[j]<a[lo]){
			std::swap(a[j],a[i]);
			++i;		
		}
	}
	std::swap(a[i-1],a[lo]);
	return i-1;
};

void Dselect::choosepivot(int* a,int lo,int hi){
	int c=0;
	for(int i=lo;i<hi;i+=5){
		std::sort(a+i,a+(std::min(hi,i+5)));
		++c;
	}
	int* C=new int[c];
	for(int i=0;i<c;++i){
		int m=(i*5+std::min(hi,i*5+5))/2;
		C[i]=a[m];
	}
	int p=mselect(C,0,c-1,(c+1)/2);
	delete[] C;
	//swap pivot and first element
	for(int i=lo;i<=hi;++i)
		if(p==a[i]){
			std::swap(a[i],a[lo]);
			break;	
		}
};
