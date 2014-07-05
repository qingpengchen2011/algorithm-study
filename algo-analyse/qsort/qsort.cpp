#include "qsort.hpp"
#include <utility>
#include <cstdlib>
void quicksort::sort(int* a,int len){
	compare_count=0;
	msort(a,0,len-1);
};

void quicksort::msort(int* a,int lo,int hi){
	if(lo>=hi)
		return;
	compare_count+=(hi-lo);
	choosepivot_first_ele(a,lo,hi);
	int mid=partition(a,lo,hi);
	msort(a,lo,mid-1);
	msort(a,mid+1,hi);

};

void quicksort::choosepivot_random(int* a, int lo, int hi){
	int len=hi-lo+1;
	int i=rand()%len+lo;
	std::swap(a[lo],a[i]);	
};

void quicksort::choosepivot_first_ele(int* a,int lo,int hi){
	return;
};

void quicksort::choosepivot_last_ele(int*a, int lo,int hi){
	std::swap(a[lo],a[hi]);
};

void quicksort::choosepivot_median_of_three(int* a,int lo,int hi){
	int mid=lo+((hi-lo+1)/2-1)+((hi-lo+1)%2);
	int median_index=0;
	if(a[lo]>=a[hi]){
		if(a[lo]>=a[mid]){
			if(a[mid]<=a[hi])
				median_index=hi;
			else
				median_index=mid;
		}
		else{
			median_index=lo;	
		}	
	}
	else{
		if(a[hi]>=a[mid]){
			if(a[lo]<=a[mid]){
				median_index=mid;
			}
			else{
				median_index=lo;	
			}
		}
		else{
			median_index=hi;
		}	
	}	
	
	std::swap(a[lo],a[median_index]);

};

int quicksort::partition(int* a ,int lo,int hi){
	int i=lo+1;
	for(int j=lo+1;j<=hi;++j){
		if(a[lo]>a[j]){
			std::swap(a[i],a[j]);
			++i;
		}	
	}
	std::swap(a[lo],a[i-1]);
	return i-1;
};

