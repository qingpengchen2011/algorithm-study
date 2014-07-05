#include "invert-count.hpp"
//merge sort top-down approach
long long invert_count::sort_count(int* a,int len){
	aux=new int[len];
 	return msort_count(a,0,len-1);
};

long long invert_count::msort_count(int* a,int low,int high){
	if(high<=low)
		return 0;
	int mid=(low+high)/2;
	long long left=msort_count(a,low,mid);
	long long right=msort_count(a,mid+1,high);
	return (left+right+merge_count(a,low,mid,high));

};

long long invert_count::merge_count(int* a,int low,int mid,int high){
	int i=low,j=mid+1;
	long long count=0;
	for(int k=low;k<=high;k++)
		aux[k]=a[k];
	for(int k=low;k<=high;k++){
		if(i>mid)
			a[k]=aux[j++];
		else if(j>high)		
			a[k]=aux[i++];
		else if(aux[i]<=aux[j])
			a[k]=aux[i++];
		else{
			a[k]=aux[j++];	
			count+=(mid-i+1);
		}
	}	
	return count;
};


