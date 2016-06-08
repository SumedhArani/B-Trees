#include <iostream>
#include <cstdlib>
#include "btree.h"

#define n 4

int i=0;
int j=0;
node* groot; //used as a global variable to reset the root and avoid several parameter

void insert(int key, node** root)
{

	cout<<"insert called" <<endl;
	node* temp =*root;
	node* parent = new node[10];
	i=0;
	j=0;

	//if tree is empty, create a new node and mark it as the root
	if (*root==NULL)
	{
		node* n1 = new node();
		*root = n1;
		temp = n1;
	}
	//find the leaf node in which the new key has to be inserted
	else
	{	
		while(temp->leaf==false)
		{
			if(key < temp->data[0])
			{
				i=0;
			}
			else
			{
				while(temp->leaf==false && i<temp->k &&!((key>temp->data[i])&&(key<temp->data[i+1])))
					i++;
			}
			parent[j++] = *temp;
			temp = temp->child_ptr[i];
		}
	}

	//cout << "Parent height: " << j <<endl;

	//temp is node L
	//atmost three keys can be filled
	//here, n-1=3

	if(((temp->k)<n-1))
	{
		insert_leaf(key, temp);
	}

	//overflow has occured
	else
	{
		overflow(key, temp, parent);
		//if the root has been split, make it the new root
		if(j<0)
			*root=groot;
	}

	cout << "Completed \n" << endl;

}

void overflow(int key, node* temp, node* parent)
{
	cout<<"insert overflow" <<endl;
	node* right = new node();

	int middle;

	//shift the elements and then reduce the number of keys inserted in it
	//k begins with 1, whereas n is an index from zero
	//temp is the left node, and we have created a new node
	// the insert_leaf procedure takes care as to where to insert the key in the right position
	//compare ((n-1)/2) & ((n-1)/2)+1 with key element
	//if less than put in the left node
	//if greater, right node
	//else middle element
	//middle element goes as a key to the parent and is a part of the right node always,
	// so only one single node needs to be created and the rest can be moved out
	//the existing node can be considered as the left node.
	//saving memory instead of creating a new node
	if((temp->data[(n-1)/2] < key)&&(key< temp->data[(n-1)/2+1]))
	{
		//Case 1: the element to be pushed is the key itself
		cout<<"1: "<<key<<endl;
		middle =key;
		for(int i=(n-1)/2+1; i<n; i++)
		{
			right->data[i-((n-1)/2+1)]=temp->data[i];
			right->k++;
		}
		temp->k = ((n-1)/2)+1;
		insert_leaf(key, right);
	}
	else if(key<temp->data[(n-1)/2])
	{
		//Case 2:
		cout<<"2: "<<(n-1)/2<<" "<<temp->data[(n-1)/2]<<endl;
		middle = temp->data[(n-1)/2];
		for(int i=(n-1)/2; i<n; i++)
		{
			right->data[i-((n-1)/2)]=temp->data[i];
			right->k++;
		}
		temp->k = (n-1)/2;
		insert_leaf(middle, temp);
	}
	else
	{
		cout << "3: "<<(n-1)/2+1 << " " <<temp->data[(n-1)/2+1] <<endl;
		middle = temp->data[((n-1)/2)+1];
		for(int i=(n-1)/2+1; i<n; i++)
		{
			right->data[i-((n-1)/2+1)]=temp->data[i];
			right->k++;
		}
		temp->k = ((n-1)/2)+1;
		insert_leaf(key, right);
	}

	temp->child_ptr[n-1]=right; //sibling ptr
	insert_parent(middle, parent, temp, right);

	//if root being split create a new node
	//insert parent ->shift the child pointers too

	//when child splits, mark the sibling of left as right
	//NB: Shift the child pointers
}

void insert_leaf(int key, node* temp)
{
	cout<<"insert leaf" <<endl;
	//insert first
	if((temp->k)==0)
	{
		temp->data[0]=key;
	}

	//insert at the beginning
	else if(key<temp->data[0])
	{
		//shift all to the right
		for(int i= temp->k-1; i>=0; i--)
		{
			temp->data[i+1] = temp->data[i];
		}
		temp->data[0]=key;
	}

	//insert at last
	else if(key>temp->data[(temp->k)-1])
	{
		temp->data[(temp->k)]=key;
	}

	//insert in the middle
	else
	{ \
	
		int i= (temp->k)-1;
		while(i>0 && !((key < temp->data[i])&&(key > temp->data[i - 1])))
		{
			i--;
			temp->data[i+1] = temp->data[i];
		}
		temp->data[i+1] = temp->data[i];
		temp->data[i] = key;
	}

	(temp->k) = (temp->k) +1; //increase the number of keys filled in the node
}

void insert_nonleaf(int key, node* temp, node* right)
{
	//similar to insert leaf
	//here we need to take care of child ptrs as well
	//and also insert the newly split node
	//hence the new node is passed as a parameter

	//k can never be n at the beginning
	//in the end, it can equal to n
	//k= n-1

	cout<<"insert nonleaf" <<endl;

	//insert at the beginning
	if(key<temp->data[0])
	{
		//shift all to the right
		for(int i= temp->k-1; i>=0; i--)
		{
			temp->data[i+1] = temp->data[i];
		}
		for(int i= temp->k; i>0; i--)
		{
			temp->child_ptr[i+1] = temp->child_ptr[i];
		}
		temp->data[0]=key;
		temp->child_ptr[1]=right;
	}

	//insert at last
	else if(key>temp->data[(temp->k)-1])
	{
		temp->data[(temp->k)]=key;
		temp->child_ptr[(temp->k)+1]=right;
	}

	//insert in the middle
	else
	{
		int i= (temp->k)-1;
		while(i>0 && !((key < temp->data[i])&&(key > temp->data[i - 1])))
		{
			i--;
			temp->data[i+1] = temp->data[i];
			temp->child_ptr[i+2] = temp->child_ptr[i+1];
		}
		temp->data[i+1] = temp->data[i];
		temp->data[i] = key;
		temp->child_ptr[i+1] = right;
	}

	(temp->k) = (temp->k) +1; //increase the number of keys filled in the node
}

void insert_parent(int middle, node* parent, node* left, node* right)
{

	cout<<"insert parent called" <<endl;

	//similar to insert function
	//flow: insert -> overflow -> insert_parent -> overflow -> insert_parent i.e if parent also splits

	//Every time this function is called, we move up a level(parent)
	int t = --j;

	//insert first or when the root has been split
	if(parent==NULL || t<0)
	{
		//create new node
		//with only one key value
		node* nnode = new node();

		nnode->data[0] = middle;
		nnode->child_ptr[0] = left;
		nnode->child_ptr[1] = right;

		nnode->k = 1;

		groot = nnode;
	}

	//insert in other situations
	else
	{
		node* temp = parent+t;

		if(((temp->k)<n-1))
			insert_nonleaf(middle, temp, right);
		else
			overflow(middle, temp, parent);
	}
}
