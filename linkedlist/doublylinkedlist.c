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
// to insert a node at position 
int insert_at_pos(Node**,int);
// to insert a node after given data
// to insert a node before given data
// to delete a node at position 
// to delete a node after given data
// to delete a node before given data
// to replace node at given position 
// to replace a node having some data with a new node having some other data
// to search for node with given data
// to print the entire list 
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
int insert_at_pos(Node** href,int pos){
	return 100;
}