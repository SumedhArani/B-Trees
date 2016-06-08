#include "node.h"
#define n 4

node::node()
{
	data = new int[n-1];
	child_ptr = new node* [n];
	leaf = true;
	k=0;
}

node::~node()
{
	cout<<"Destructor called"<<endl;
}
