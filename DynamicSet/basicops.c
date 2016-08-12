#include<stdio.h>
#include<stdlib.h>

// maximum size of the set, as we are using array to implement set, we have to 
// declare a fixed size of the array.
#define MAX_SIZE 100

typedef enum boolean{FALSE, TRUE}Boolean;

// structure for the Dynamic Set
typedef struct dset{int elements[MAX_SIZE];int count;}DSet;

// returns pointer to an empty set
DSet* New(){
 DSet* S = (DSet*)malloc(sizeof(DSet));
 if(!S){printf("memory error\n");return NULL;}
 S->count=0;
 return S;
}

// returns TRUE if given element is present in the set, FALSE otherwise
Boolean IsIn(DSet* S, int e){
 if(!S){printf("Invalid Set");return FALSE;}
 for(int i=0;i<S->count;i++){
  if(S->elements[i] == e)return TRUE;
 }
 return FALSE;
}

// returns pointer to given set with new element inserted
DSet* Insert(DSet* S, int e){
 if(!S){printf("Invalid Set\n");return NULL;}
 if(S->count == MAX_SIZE){printf("Set Overflow\n");return S;}
 if(IsIn(S, e)){printf("Duplication not allowed\n");return S;}
 S->elements[S->count++] = e;
 return S;
}

// returns pointer to given set with an element removed
DSet* Delete(DSet* S, int e){
 if(!S){printf("Invalid Set\n");return NULL;}
 if(S->count == 0){printf("Set Underflow\n");return S;}
 if(!IsIn(S,e)){printf("Element not present in set\n");return S;}
 for(int i=0;i<S->count;i++){
  if(S->elements[i] == e){
   S->elements[i] = S->elements[S->count-1];
   return S;
  }
 }
}

// driver
int main(){
 DSet* set = New();
 Insert(set, 4);
 IsIn(set, 3);
 IsIn(set, 4);
 Delete(set, 4);
 IsIn(set, 4);
 return 0;
}
