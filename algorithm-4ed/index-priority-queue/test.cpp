#include <iostream>
#include <string>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include "indexminpq.hpp"

using namespace boost::bimaps;


int main()
{
   //---------------------------------------------------------------------------
   std::cout<<"-------------------------------------------------------------\ntest for index_min_pq:\n";
   index_min_pq    queue;
   std::cout<<"is empty():"<<queue.empty()<<std::endl;
   std::cout<<"insert\n";
   queue.insert(0,1.1);
   queue.insert(1,2.1);
   queue.insert(4,99.1);
   queue.insert(3,8.1);
   queue.insert(6,0.91);
   std::cout<<"current size:"<<queue.size()<<std::endl;
   queue.show();
   std::cout<<std::endl;   

   
   std::cout<<"change\n";
   queue.change(0,1000.1);
   queue.change(3,0.00001);
   queue.show();

   std::cout<<"min_index\n";
   std::cout<<"the mix weight of index:"<<queue.min_index()<<std::endl;
   std::cout<<"del_min\n";
   std::cout<<"the index of min weight is:"<<queue.del_min()<<std::endl;
   queue.show();

   std::cout<<"min weight:"<<queue.min()<<std::endl;  
   std::cout<<"is empty():"<<queue.empty()<<std::endl;
   std::cout<<"current size:"<<queue.size()<<std::endl;

   queue.clear();
   
   std::cout<<"is empty():"<<queue.empty()<<std::endl;
   std::cout<<"current size:"<<queue.size()<<std::endl;
   
   return 0;
}
