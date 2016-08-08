#include <stdio.h>
#include <stdlib.h>

#define M 113 // modulo for hash function 
#define S 234 // table size

typedef struct cnode{ // chain node structure, for storing key value pairs having same hash values 
	int k; // key
	int v; // value (satellite data)
	struct cnode* link; // link for next node
}CNode;

int division(int k){ // hash function
	return k%M;
}

void insert(CNode* T[],int k,int v){ // insert key value pair in hash table
	int h=division(k); // compute hash value
	CNode* n=malloc(sizeof(CNode)); n->k=k;	n->v=v;// create new node and insert k,v pair
	CNode* t=T[h]; T[h]=n; n->link=t; // insert node at head of chain
}

void delete(CNode* T[], int k){ // delete k,v pair for given key
	int h=division(k);
	CNode* c=T[h],*p=c;
	if(T[h]->k==k){ // if at head of chain
		T[h]=T[h]->link;
		free(c);
	}
	else{
		while(c!=NULL){ // search key and delete node.
			p=c;
			c=c->link;
			if(c->k==k){
				p->link=c->link;
				free(c);
				return;
			}
		}
	}
}

int search(CNode* T[], int k){ // return v for given k
	int h=division(k);
	CNode* c=T[h];
	while(c!=NULL){ // traverse the chain, until node with given k not found
		if(c->k==k)return c->v; // return v for given k
		c=c->link;
	} 
	return -1; // return -1 if not found
}

void disp(CNode* T[]){ // display all k,v pairs in table
	for(int i=0;i<S;i++){
		int h=division(i);
		CNode* c=T[h];
		while(c!=NULL){
			printf("key: %d, value: %d\n",c->k, c->v);
			c=c->link;
		}
	}
}

int main(){
	CNode* T[S];
	for(int i=0;i<S;i++)T[i]=NULL;
	insert(T,234,100001);
	printf("\nvalue for key %d is %d\n",234,search(T,234));
	delete(T,234);
	printf("\nvalue for key %d is %d\n",234,search(T,234));
	disp(T);
	return 0;
}