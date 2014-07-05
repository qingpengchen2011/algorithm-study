#ifndef _MERGE_SORT_HPP
#define _MERGE_SORT_HPP
#include <algorithm>
//top-down merge sort
class merge_sort_TD{
	private:
		int* aux;
	public:
		void sort(int* a,int len);
	private:
		void msort(int* a,int low,int high);
		void merge(int* a,int low,int mid,int high);	

};

//bottom-up merge sort
class merge_sort_BU{
	private:
		int* aux;
	public:
		void sort(int* a,int len);
	private:
		void merge(int*a ,int low,int mid,int high);	

};

#endif
