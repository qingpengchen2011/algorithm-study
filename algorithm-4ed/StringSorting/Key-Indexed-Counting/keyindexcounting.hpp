#ifndef __KEYINDEXCOUNTING_

#define __KEYINDEXCOUNTING_

#include <string>
#include <utility>
#include <vector>
#include <memory>
class keyindexcounting{
	public:
		typedef std::pair<int,std::string> element_type;
		typedef std::vector<std::shared_ptr<element_type> > array_elements_type;
  	public:
		/*  elements:a vector of elements to sort
                 *  R:number of alphabet 
                 */
		keyindexcounting(array_elements_type& elements,int R);
	private:
		array_elements_type& m_elements;
		int m_R;
		
		std::vector<int> m_count;
	private:
		void dostatistic();
		void calculateindex();	
	   	void dosort();	

};
#endif
