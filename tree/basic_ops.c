#include<stdio.h>
#include<stdlib.h>

// data type for node data
typedef struct {int id; float value;}Ndtype;

// tree node
typedef struct node{
	
	// data to be stored in the node
	Ndtype data;
	
	// pointer to left child
	node* left = NULL;
	
	// pointer to right child
	node* right = NULL;
}TNode;


int main(){
	
	
	return 0;
}