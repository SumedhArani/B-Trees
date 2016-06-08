#include <iostream>
#include <cstdlib>
#include "btree.h"
using namespace std;

int main()
{
	/* code */
	node* root1 = NULL;

	insert(5, &root1);
	insert(9, &root1);
	insert(1, &root1);
	insert(3, &root1);
	insert(4, &root1);
	insert(59, &root1);	
	insert(65, &root1);
	insert(45, &root1);
	insert(89, &root1);	
	insert(29, &root1);
	insert(68, &root1);
	insert(108, &root1);	
	insert(165, &root1);
	insert(298, &root1);
	insert(219, &root1);	

	return 0;
}