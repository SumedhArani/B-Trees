#include <iostream>
#include <cstdlib>
using namespace std;

class node
{
	public:
		int k; //keys filled in the given node in an n-ary tree
		int* data; //ptr to an array of size n-1
		bool leaf; //leaf or non leaf
		node** child_ptr; //ptr to an array of ptr to child nodes of size n
		node();
		~node();
};
