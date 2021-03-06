#include<stdio.h>
#include<stdlib.h>

// number of available operations
#define NUM_AVAIL_OPS 12

// list of available operations
const char *AVAIL_OPS[]={"list available operations","insert at position","insert after","insert before",
	"delete node at position","delete node after","delete node before","replace node","search for data",
	"print entire list", "reverse list","exit"
};


//node of the doubly linked list
typedef struct node{
	int data;
	struct node* prev;
	struct node* next;
}Node;

// length of the list 
int length(Node*);

// create new node
Node* create(int, Node*, Node*);

// to list available operations
void list_avail_ops();

// check if pointer is null
int valid(Node*);

// check if pointer to pointer is null
int validref(Node**);

// go to the required position 
Node* gotopos(Node*, int);

// insert at head
void insert_at_head(Node**, int);

// insert at tail
void insert_at_tail(Node**, int);

// to insert a node at position 
void insert_at_pos(Node**,int, int);

// to insert a node after given data
void insert_after_data(Node**, int, int);

// to insert a node before given data
void insert_before_data(Node**, int, int);

// delete node
void delete_node(Node*);

// delete from head
void del_from_head(Node**);

// to delete a node at position 
void del_at_pos(Node**, int);

// to delete a node after given data
void del_after_data(Node**, int);

// to delete a node before given data
void del_before_data(Node**, int);

// to replace node at given position
void replace_at_pos(Node**, int, Node*);
 
// to replace a node having some data with a new node having some other data
void replace_at_data(Node**, int, int);

// to search for node with given data
int search(Node*, int);

// to print the entire list 
void print(Node*);

// perform operation 
Node* perform(int, Node*);

int main(){
	// to get the user input for operation
	int oprtn;
	Node* head = NULL;
	// list out the available operations
	list_avail_ops();
	
	// operation loop  	
	while(1){
		printf("\n>>>");
	
		// input validation loop		
	  	while(scanf(" %d", &oprtn)==0){
	  		printf("\nINVALID INPUT\n");
	  		scanf("%*[^\n]\n");
	  	}
		// -1 indicates user wants to exit 
	  	if(oprtn==-1)break;

		// if request is valid, perform operation 
	  	else if(oprtn>=0 && oprtn<=10) head = perform(oprtn, head);			  		
	  	
	  	else printf("\nUNIDENTIFIED REQUEST\n");
	}	
	return 0;
}

// create and prepare new node
Node* create(int data, Node* prev, Node* next){
	Node* new = malloc(sizeof(Node));
	new->data = data;
	new->prev = prev;
	new->next = next;
	return new;
}


// length of the list
int length(Node* head){
	int len = 0;
	while(head!=NULL) {len++;	head = head->next;}
	return len;
}


// list operations
void list_avail_ops(){
	
	printf("\nIDENTIFIED OPERATIONS:\n");
	
	for(int i=0;i<NUM_AVAIL_OPS;i++){

		if(i==11) printf("%d %s\n",-1, AVAIL_OPS[i]);
		else printf("%d %s\n",i, AVAIL_OPS[i]);
	}			
}


// check if pointer is null
int valid(Node* ptr){
	if(ptr == NULL){ printf("\nNULL POINTER EXCEPTION\n"); return 0;}
	return 1;
}


// check if pointer to pointer is null
int validref(Node** ptrref){
	if(ptrref == NULL){ printf("\nNULL POINTER REFERENCE EXCEPTION\n"); return 0;}
	return 1;
}


// go to the required position 
Node* gotopos(Node* head, int p){

	// validate pointer 
	if(!valid(head))return NULL;

	Node* ptr = head;
	
	// traverse list until either position is reached, or list ends.	
	for(int i=0;i<p && ptr!=NULL;i++)ptr = ptr->next;

	// return pointer to node at required position.
	return ptr;
}


// insert at head
void insert_at_head(Node** href, int data){

	// check if head reference is valid
	if(!validref(href)) return;

	/* create new node,	
	 point the next of new node to current head, and 
	 point previous of new node to null*/
	Node* new = create(data, NULL, *href);

	// point prev of current head to new node if current head is not null
	if(*href != NULL)(*href)->prev = new;
	
	// change the head reference to new node
	*href = new;
}


// insert at tail
void insert_at_tail(Node** href, int data){
	if(!validref(href))return;
		
	// go to the end
	Node* tail = gotopos(*href, length(*href)-1);

	//create new node, insert data and link to the tail.
	Node* new = create(data, tail, NULL);

	// link tail to new node
	tail->next = new;
}


// insert at tail
void insert_at_pos(Node** href,int pos, int data){

	// check if head reference is valid 
	if(!validref(href)) return;

	// if pos is zero, redirect to insert_at_head
   if(pos == 0){insert_at_head(href, data); return;}

	// if position is +1 of last position, call insert_end()
	if(length(*href)==pos){insert_at_tail(href, data);return;}

	/* if position is not zero, and head is NULL insertion is not possible, 
	since there is no valid position other than zero. */
	if(!valid(*href)){ printf("\nLIST IS EMPTY, POSITION %d NOT AVAILABLE\n",pos); return; };		

	// temporary pointer to traverse the list
   Node* temp = *href;
   
	// go to the position 
	temp = gotopos(*href, pos);

	if(temp == NULL){ printf("\nPOSITION NOT AVAILABLE\n"); return;};	

   /* create new node,
	point next of new node to temp and prev of new node prev of temp*/
   Node* new = create(data, temp->prev, temp);
	
	// point next of prev of temp and prev of temp to new
	temp->prev->next = new;
	temp->prev = new;
}


// to insert a node after given data
void insert_after_data(Node** href, int search_data, int new_data){

	// check if head reference is valid
	if(!validref(href)) return;

	// search for first occurance of matching data item
	int pos = search(*href, search_data);

	if(pos == -1){ printf("\nERROR: data not found.\n"); return; }
	// insert 
	insert_at_pos(href, pos+1, new_data);
}


// to insert a node before given data
void insert_before_data(Node** href, int search_data, int new_data){
	// validate href
	if(!validref(href))return;
	
	// search for first occurance of matching data item
	int pos = search(*href, search_data);

	// if there is no such data item, abort.
	if(pos == -1){ printf("\nERROR: data not found.\n"); return;}

	// else insert at the position
	insert_at_pos(href, pos, new_data);
}


// delete from head
void del_from_head(Node** href){
	if(!validref(href))return;

	/* dereference the double pointer to head, to get the pointer to head,
		and if it is null, no need to delete anything, return.*/
	Node* head = *href;
	if(!valid(head))return;
	
	//delink the old head, and make the second node as new head.
	head->next->prev = NULL;
	*href = (*href)->next;

	free(head);
}


// delete given node
void delete_node(Node* node){
	if(!valid(node))return;
	
	// link the left and right nodes of the one that is deleted
	if(valid(node->next))node->next->prev = node->prev;
	if(valid(node->prev))node->prev->next = node->next;
	
	// free the node memory
	free(node);
}


// to delete a node at position 
void del_at_pos(Node** href, int pos){
	if(!validref(href))return;
	
	// if the position is head, call del_from_head()
	if(pos==0) {del_from_head(href); return;}

	// else go to position 
	Node* tmp = gotopos(*href, pos);

	// delete it
	delete_node(tmp);
}


// to delete a node after given data
void del_after_data(Node** href, int data){
	if(!validref(href))return;

	// get the position of node after given data item
	int pos = search(*href, data);
	
	// if position is after the tail, abort 
	Node* tmp = gotopos(*href, pos+1);
	if(tmp == NULL);	
	
	delete_node(tmp);
}


// to delete a node before given data
void del_before_data(Node** href, int data){
	if(!validref(href))return;
	
	// get the position of node before the one having rqd data
	int pos = search(*href, data);
	
	// if there is no such data item in the list, abort the operation 
	if(pos == -1){printf("\nERROR: data not found.\n"); return;}	
	
	// if node having reqd data is head, there is no data before that, so return.
	if(pos == 0){printf("\nERROR: no item before head.\n"); return;}	
	
	// if pos to be deleted is head call del_from_head()
	if(pos == 1){del_from_head(href); return;}
	
	// else goto the position and delete the node
	Node* tmp = gotopos(*href, pos-1);
	delete_node(tmp);
}


// to replace node at given position
void replace_at_pos(Node** href, int pos, Node* new){
	if(!validref(href))return;
	
	// get pointer to node, which will be replaced
	Node* tmp = gotopos(*href, pos);

	/* connect new node to left and right of current node at that position */	
	new->next = tmp->next;
	new->prev = tmp->prev;

	if(pos == 0){ *href = new; }
	
	/* connect left and right nodes of old one to new node */
	if(valid(tmp->next))tmp->next->prev = new;
	if(valid(tmp->prev))tmp->prev->next = new;
}
 
 
// to replace a node having some data with a new node having some other data
void replace_at_data(Node** href, int old_data, int new_data){

	if(!validref(href))return;
	
	// search position of node with given data
	int pos = search(*href, old_data);

	// create new node, with data to insert
	Node* new = create(new_data, NULL, NULL);
	
	// call function to replace node at given position
	replace_at_pos(href, pos, new);
}


// to search for node with given data
int search(Node* head, int data){
	if(!valid(head))return -1;
	int pos = 0;
	while(head!=NULL) { if(head->data == data) return pos; head = head->next; pos++; }
	return -1;
}


// to print the entire list 
void print(Node* head){
	while(head!=NULL) {printf(" <-> %d ", head->data);	head = head->next;}
}


// perform operation 
Node* perform(int oprtn, Node* head){
	int pos, search_data, new_data, del_data;
	switch(oprtn){
		case 0:
			list_avail_ops();
			break;
		case 1:
			printf("\nPOSITION: ");
			scanf("%d", &pos);
			printf("\nDATA: ");
			scanf("%d", &new_data);
			insert_at_pos(&head,pos,new_data);
			break;
		case 2:
			printf("\nINSERT NODE AFTER DATA: ");
			scanf("%d", &search_data);
			printf("\nDATA TO INSERT: ");
			scanf("%d", &new_data);
			insert_after_data(&head, search_data, new_data);
			break;
		case 3:
			printf("\nINSERT NODE BEFORE DATA: ");
			scanf("%d", &search_data);
			printf("\nDATA TO INSERT: ");
			scanf("%d",&new_data);					
			insert_before_data(&head, search_data, new_data);
			break;
		case 4:
			printf("\nPOSITION: ");
			scanf("%d", &pos);
			del_at_pos(&head, pos);
			break;
		case 5:
			printf("\nDELETE NODE AFTER DATA: ");
			scanf("%d", &del_data);
			del_after_data(&head, del_data);
			break;
		case 6:
			printf("\nDELETE NODE BEFORE DATA: ");
			scanf("%d", &del_data);
			del_before_data(&head, del_data);
			break;
		case 7:
			printf("\nREPLACE: ");
			scanf("%d", &search_data);
			printf("\nWITH: ");
			scanf("%d", &new_data);
			replace_at_data(&head, search_data, new_data);
			break;
		case 8:
			printf("\nSEARCH DATA: ");
			break;
		case 9:
			printf("\nLIST: \n");
			print(head);
			break;
	}	
	return head;
}