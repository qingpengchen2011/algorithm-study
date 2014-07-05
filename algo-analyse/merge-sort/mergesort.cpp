#include "mergesort.hpp"
//merge sort top-down approach
void merge_sort_TD::sort(int* a,int len){
	aux=new int[len];
 	msort(a,0,len-1);
};

void merge_sort_TD::msort(int* a,int low,int high){
	if(high<=low)
		return;
	int mid=(low+high)/2;
	msort(a,low,mid);
	msort(a,mid+1,high);
	merge(a,low,mid,high);

};

void merge_sort_TD::merge(int* a,int low,int mid,int high){
	int i=low,j=mid+1;
	for(int k=low;k<=high;k++)
		aux[k]=a[k];
	for(int k=low;k<=high;k++){
		if(i>mid)
			a[k]=aux[j++];
		else if(j>high)		
			a[k]=aux[i++];
		else if(aux[i]<=aux[j])
			a[k]=aux[i++];
		else
			a[k]=aux[j++];	
	}	


};

//merge sort bottom-up approach
void merge_sort_BU::sort(int* a,int len){
	aux=new int[len];
	for(int sz=1;sz<len;sz=2*sz){
		for(int low=0;low<len-sz;low+=2*sz)
			merge(a,low,low+sz-1,std::min<int>(low+sz+sz,len-1));

	};


};

void merge_sort_BU::merge(int* a,int low,int mid,int high){
        int i=low,j=mid+1;
        for(int k=low;k<=high;k++)
                aux[k]=a[k];
        for(int k=low;k<=high;k++){
                if(i>mid)
                        a[k]=aux[j++];
                else if(j>high)
                        a[k]=aux[i++];
                else if(aux[i]<=aux[j])
                        a[k]=aux[i++];
                else
                        a[k]=aux[j++];
        }


};

