#ifndef __SELECT__HPP
#define __SELECT__HPP
class Rselect{
	public:
		int select(int*a,int len,int i);
	private:
		int mselect(int*a,int lo,int hi,int i);
		void choosepivot(int*a,int lo,int hi);
		int partition(int*a,int lo,int hi);
};

class Dselect{
	public:
		int select(int*a,int len,int i);
	private:
		int mselect(int* a,int lo,int hi,int i);
		int partition(int *a,int lo,int hi);
		void choosepivot(int*a ,int lo,int hi);	
};

#endif
