#ifndef __LSD_HPP
#define __LSD_HPP
#include "keyindexcounting.hpp"

class lsd{
	private:
		typedef typename keyindexcounting::element_type element_type;
                typedef typename keyindexcounting::array_elements_type array_elements_type;

	public:
		/*  array_string:strings to sort
  		 *  w:the number of bit used to sort
                 *  len:length of string
		 */
		lsd(std::vector<std::string>& array_string,int w,int len);
	private:
		std::vector<std::string>& m_array_string;
		array_elements_type m_part_array;			
		int m_w;
		int m_len;
	
	private:
		void init_part_array();
		void construct_part_array(int);



};

#endif
