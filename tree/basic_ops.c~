#include<stdio.h>
#include<stdlib.h>

/* data type for node data */
typedef struct {int id; float value;}Ndtype;

/* STATUS codes */
typedef enum {SUCCESS, FAILURE, NOACT}_status_code;

/* ERROR codes */
typedef enum {NPTR}_error_code;

/* tree node */
typedef struct node{
	
	// data to be stored in the node
	Ndtype data;
	
	// pointer to left child
	struct node* left;
	
	// pointer to right child
	struct node* right;
}TNode;

// provide error information
void indicate_error(_error_code e, char type[]){
	printf("\n");
	if(e = NPTR){
		if(type == "pTNode")
		printf("ERROR: Expected Tree Node Pointer, Received NULL pointer");		
	}
	printf("\n");
}


// create new tree node, and return pointer to it.
TNode* create_TNode(NDtype data){

	// allocate memeory 
	TNode* tnode= malloc(sizeof(TNode));

	// insert data
	(tnode->data).id = data.id;
	(tnode->data).value = data.value;
	
	tnode->left = NULL;
	tnode->right = NULL;
	
	return tnode;
}


// insert a node in the tree, (binary tree).
_status_code insert(TNode* root, Ndtype data){
	_status_code ret_code = SUCCESS;
	
	// validate root
	if(root == NULL) {indicate_error(NPTR, "pTNode");}
	
	//if root is valid	
	else {
		// create new node
		TNode* new_TNode = create_TNode(data);
	} 	 
	return ret_code;
}

int main(){
	return 0;
}