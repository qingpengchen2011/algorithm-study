#ifndef __QSORT_HPP
#define __QSORT_HPP
class quicksort{
	public:
		void sort(int* a,int len);
		long compare_count;
	private:
		void msort(int* a, int lo,int hi);
		void choosepivot_random(int*a,int lo,int hi);
		void choosepivot_first_ele(int* a,int lo,int hi);
		void choosepivot_last_ele(int* a,int lo,int hi);
		void choosepivot_median_of_three(int* a,int lo,int hi);
		int partition(int* a,int lo,int hi);
};

#endif
