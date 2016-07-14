#include<stdio.h>
// list of available operations
const char *AVAILABLE_OPERATIONS[]={"list available operations","insert at position","insert after","insert before",
	"delete node at position","delete node after","delete node before","replace node","search for data",
	"print entire list", "reverse list","exit"
};
const int NUMBER_OF_AVAILABLE_OPERATIONS=12;
//node of the doubly linked list
typedef struct node{
	int data;
	struct node* prev;
	struct node* next;
}Node;
// to list available operations
void list_avail_ops();

// check if pointer is null
int valid(Node*);

// go to the required position 
Node* gotopos(Node*, int);

// insert at head
void insert_at_head(Node**, int);

// to insert a node at position 
void insert_at_pos(Node**,int, int);

// to insert a node after given data
void insert_after_data(Node**, int, int);

// to insert a node before given data
void insert_before_data(Node**, int, int);

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
void search(Node*, int);

// to print the entire list 
void print(Node*);

// to reverse the list 

int main(){
	// to get the user input for operation
	int oprtn,pos;
	//head of the linked list
	Node *head=NULL;
	
	// list out the available operations
	list_avail_ops();
	// operation loop  	
	while(1){
		printf("\nWhat do you want me to do? ");
	  	while(scanf(" %d", &oprtn)==0){
	  		printf("dude what are you saying! give me an integer value please.");
	  		scanf("%*[^\n]\n");
	  	}
	  	if(oprtn==-1)break;
	  	else if(oprtn>=0 && oprtn<=10){
			// stores the response code of operation performed	  		
	  		int resp;
			switch(oprtn){
				case 0:
					list_avail_ops();
					break;
				case 1:
					printf("\nWhat position you want to insert data at? ");
					scanf("%d", &pos);
					resp=insert_at_pos(&head,pos);
					if(resp==100)printf("I have successfully performed the operation");
					else printf("Sorry, Something went wrong, I tried my best but failed.");
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;	
			}	
	  	}
	  	else printf("Sorry, I don't know how to do that, please ask my master teach me first.");
	}	
	return 0;
}
void list_avail_ops(){
	printf("\nI can do the following operations on this data structure\n");
	for(int i=0;i<NUMBER_OF_AVAILABLE_OPERATIONS;i++){
		if(i==11) printf("%d %s\n",-1, AVAILABLE_OPERATIONS[i]);
		else printf("%d %s\n",i, AVAILABLE_OPERATIONS[i]);
	}		
}

// check if pointer is null
int valid(Node* ptr){
	if(ptr == NULL)return 0;
	return 1;
}

// go to the required position 
Node* gotopos(Node* head, int p){
	// validate pointer 
	if(!valid(head))return;
	for(int i=0;i<pos && p!=NULL;i++) {
		head = head->next;
	}
	return head;
}

void insert_at_head(Node** href, int data){	
	// check if head reference is valid
	if(!valid(href)) return;
	// create a new node
	Node* new = malloc(sizeof(Node));
	new->data = data;	
	// point the next of new node to current head 
	new->next = *href;
	// point previous of new node to null
	new->prev = NULL;
	// point prev of current head to new node
	(*href)->prev = new;
	// change the head reference to new node
	*href = new;
}

void insert_at_pos(Node** href,int pos, int data){
	// check if head reference is valid 
	if(!valid(href)) return;
	// if pos is zero, redirect to insert_at_head
   if(pos == 0){	
		insert_at_head(href, data);
		return;	
	}		
	// temporary pointer to traverse the list
   Node* temp = *href;
   // create new node
   Node* new = malloc(sizeof(Node));
	// go to the position 
	temp = gotopos(*href, pos);	
	// point next of new node to temp and prev of new node prev of temp
	new->next = temp;
	new->prev = temp->prev;
	// point next of prev of temp and prev of temp to new
	temp->prev->next = new;
	temp->prev = new;
}

// to insert a node after given data
void insert_after_data(Node** href, int search_data, int new_data){
	// check if head reference is valid
	if(!valid(href)) return;
	// search for first occurance of matching data item
	pos = search(*href, search_data);
	insert_at_pos(href, pos+1, new_data);
}

// to insert a node before given data
void insert_before_data(Node** href, int search_data, int){
	// validate href
	if(!valid(href))return;
	// search for first occurance of matching data item
	pos = search(*href, search_data);
	insert_at_pos(href, pos-1, new_data);
}

// delete from head
void del_from_head(Node** href){
	// validate
	if(!valid(href))return;
	head = *href;
	head->next->prev = NULL;
	*href = (*href)->next;
	free(head);
}

// delete given node
void delete_node(Node* node){
	if(!valid(node))return;
	if(valid(node->next))node->next->prev = node->prev;
	if(valid(node->prev))node->prev->next = node->next;
	free(node);
}

// to delete a node at position 
void del_at_pos(Node** href, int pos){
	if(!valid(href))return;
	// go to position 
	Node* tmp = gotopos(*href, pos);
	// delete it
	delete_node(tmp);
}

// to delete a node after given data
void del_after_data(Node** href, int data){
	if(!valid(href))return;
	pos = search(*href, data);
	Node* tmp = gotopos(*href, pos+1);
	delete_node(tmp);
}

// to delete a node before given data
void del_before_data(Node** href, int data){
	if(!valid(href))return;
	pos = search(*href, data);
	Node* tmp = gotopos(*href, pos-1);
	delete_node(tmp);
}

// to replace node at given position
void replace_at_pos(Node** href, int pos, Node* new){
	if(!valid(href))return;
	Node* tmp = gotopos(*href, pos);
	new->next = tmp->next;
	new->prev = tmp->prev;
	tmp->next->prev = new;
	tmp->prev->next = new;
}
 
// to replace a node having some data with a new node having some other data
void replace_at_data(Node** href, int old_data, int new_data){
	if(!valid(href))return;
	pos = search(*href, old_data);
	Node* new = malloc(sizeof(Node));
	new->data = new_data;
	replace_at_pos(href, pos, new);
}

// to search for node with given data
void search(Node* head, int data){
	if(!valid(head))return;
	int pos = 0;
	while(head!=NULL) {
		if(head->data == data) return pos;
		pos++;
	}
	return -1;
}

// to print the entire list 
void print(Node*){}
