#ifndef _INVERT_COUNT__HPP
#define _INVERT_COUNT__HPP
#include <algorithm>
//top-down merge sort
class invert_count{
	private:
		int* aux;
	public:
		long long sort_count(int* a,int len);
	private:
		long long msort_count(int* a,int low,int high);
		long long merge_count(int* a,int low,int mid,int high);	
};

#endif
