#include<stdio.h>
#include<stdlib.h>

/* data type for node data */
typedef struct {int id; float value;}Ndtype;

/* STATUS codes */
typedef enum {SUCCESS, FAILURE, NOACT}_status_code;

/* ERROR codes */
typedef enum {NPPTR, NPTR, DUPL, MMAL, UNID}_error_code;

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
void indicate_error(_error_code e){
	printf("\n");
	switch(e) {
	case NPTR:
		printf("ERROR: Expected TNode Pointer, Received NULL Pointer");
		break;		
	case NPPTR:
		printf("ERROR: Expected Pointer to TNode Pointer, Received NULL Pointer");
		break;
	case MMAL:
		printf("ERROR: Memory Allocation Failed");	
		break;
	case DUPL:
		printf("ERROR: ID Duplication Not Allowed");
		break;
	default:
		printf("ERROR: Unidentified Error");
	}
	printf("\n");
}


// create new tree node, and return pointer to it.
TNode* create_TNode(Ndtype data){

	// allocate memory 
	TNode* tnode= malloc(sizeof(TNode));

	// if memory allocation fails, indicate the failure and return.
	if(tnode == NULL){indicate_error(MMAL);}

	// if memory allocation succeeds, carry on with further opertations.	
	else{
		// insert data
		(tnode->data).id = data.id;
		(tnode->data).value = data.value;
	
		tnode->left = NULL;
		tnode->right = NULL;
	}
	
	// return either a pointer to the successfully created TNode, or a NULL pointer.
	return tnode;
}


// find parent of node to be inserted in the tree
TNode* find_parent(TNode* root, int id){
	TNode *temp = root, *paren=NULL;
	
	while(temp!=NULL) {
		
		/* if new node id is less than current node id, 
		the new node will be in left subtree of the current node */
		if((temp->data).id > id){
			printf("\ngoing left\n");
			paren = temp;		
			temp = temp->left;
		}
		
		/* if new node id is greater than current node id,
		the new node will be in the right subtree of the current node */
		else if((temp->data).id < id){
			printf("\ngoing right\n");
			paren = temp;
			temp = temp->right;
			}
		
		/* if both are equal, the node cannot be inserted, as we are not allowing id duplication */
		else if((temp->data).id == id){
			printf("\nduplicate \n");
			temp = NULL;
			paren = temp;
			}
	}
	
	/* we have made sure, that root is never NULL, during function call, so if parent is NULL 
	 while returning, this means, there is duplication*/
	return paren;
}


// insert a node in the tree, (binary tree).
_status_code insert(TNode** rootref, Ndtype data){
	_status_code ret_code = SUCCESS;
	
	// validate pointer to pointer to root
	if(rootref == NULL) {indicate_error(NPPTR);}
	
	//if double pointer is valid
	else {
		// create new node
		TNode* new_TNode = create_TNode(data);

		// if tnode creation fails, return with FAILURE code
		if(new_TNode == NULL) ret_code = FAILURE;
		
		// if tnode creation succeeds
		else {
			// if the root pointer is NULL, i.e. the tree is empty, the new node becomes the root
			if((*rootref) == NULL) (*rootref) = new_TNode;
			
			/* else find the proper parent for the new node, 
			decide weather it should be left or right child and insert*/
			else {
				TNode* parent = find_parent(*rootref, data.id);
	
				// if parent is null, therefore there is no place for the new node,i.e. duplication case occured, so destroy it.
				if(parent == NULL){
					indicate_error(DUPL);
					free(new_TNode);
					ret_code = FAILURE; 
					}	
				
				// insert to the left or right depending on id
				else if(parent != NULL){
					if((parent->data).id > (new_TNode->data).id) parent->left = new_TNode;
					else if((parent->data).id < (new_TNode->data).id) parent->right = new_TNode;
				}	
			}		
		}		
	} 	 
	return ret_code;
}

int main(){
	
	// test data
	Ndtype d,d1,d2;
	d.id = 3;
	d.value = 200.0;

	d1.id = 1;
	d1.value = 400.0;

	d2.id = 1;
	d2.value = 420.0;

	// testing create new node	
	TNode* testNode = create_TNode(d);
	printf("\nTEST1: create new node:\n");
	printf("\ntest node data id: %d\n", (testNode->data).id);
	printf("\ntest node data value: %f\n", (testNode->data).value);
	
	// testing new tree creation, i.e. inserting first element in the tree, as its root
	printf("\nTEST2: new tree creation, i.e. inserting first element in the tree, as its root:\n");
	TNode* testRoot = NULL;
	_status_code status = insert(&testRoot, d);
	if(status == SUCCESS) printf("\nroot data: id:%d value:%f\n",(testRoot->data).id, (testRoot->data).value);

	// testing general insertion
	printf("\nTEST2: general insertion:\n");
	status = insert(&testRoot, d1);
	printf("status(this should be 0): %d\n", status);
	status = insert(&testRoot, d2);
	printf("status(this should be 1): %d\n", status);
	
	return 0;
}