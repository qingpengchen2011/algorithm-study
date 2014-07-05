#ifndef _UF_HPP
#define _UF_HPP
#include<vector>

/*
 * class  for dynamic connectivity check
 *
*/


class weighted_quick_union_uf{


	public:
		weighted_quick_union_uf(int n);
		void do_union(int p,int q);
		int find(int p);
		bool connected(int p,int q){return find(p)==find(q);};
		int count(){return m_components;};
	private:
		int m_components;
		std::vector<int> m_ids;
		std::vector<int> m_weigth;

};


#endif
