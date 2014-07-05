#ifndef __TRIES_HPP

#define __TRIES_HPP
#include <memory>
#include <vector>
#include <string>
class TriesST{
	public:
		struct Node{
			int value;
			std::vector<std::shared_ptr<Node> > next;
			Node(){ next.assign(256,std::shared_ptr<Node>());};
		};

		TriesST();
		int get(std::string);
	private:	
		Node root;
		
			
		

};


#endif
