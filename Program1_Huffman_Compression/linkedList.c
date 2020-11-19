#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"


LinkedList* llCreate()
{
  return NULL;
}

int llIsEmpty(LinkedList* ll)
{
  return (ll==NULL);
}

void llDisplay(LinkedList* ll)
{
  LinkedList* p = ll;

  printf("[");

  while (p!=NULL)
    {
      printf("%d, ", p->entry->ch); // prints out the character of the tnode entry
      p = p->next;
    }

  printf("]\n");
}

void llAdd(LinkedList** ll, tnode* newEntry)
{
  LinkedList* newNode = (LinkedList*)malloc(1*sizeof(LinkedList));
  newNode->entry = newEntry;
  newNode->next = NULL;

  LinkedList*p = *ll;

  if (p==NULL)
    {
      *ll = newNode;
    }
  else
    {
      while (p->next!=NULL)
	{
	  p = p->next;
	}
      p->next = newNode;
    }
}

void list_add_in_order(LinkedList** ll, tnode* newEntry)
{
  LinkedList* newNode = (LinkedList*)malloc(1*sizeof(LinkedList));
  newNode->entry = newEntry;

  LinkedList* p = *ll;
  if (p==NULL)
    {
      newNode->next = NULL;
      *ll = newNode;
    }
  // if the list is empty this adds the new node to the beginning of the list
  else
    {
      if (newEntry->weight<p->entry->weight)
	{
	  newNode->next=*ll;
	  *ll = newNode;
	}
      // if the frequency of the new node's tnode is less than the frequency of the first element then it puts it at
      // the front of the list
      else
	{
	  while (p->next!=NULL && !(newEntry->weight<p->next->entry->weight && newEntry->weight>=p->entry->weight))
	    {
	      p = p->next;
	    }
	  // loops until the new entry's frequency is greater than the next entry in the list's frequency or the new
	  // entry's frequency is less than the current entry in the list's frequency or the next entry in the list is
	  //null
	  if (p->next==NULL)
	    {
	      newNode->next = NULL;
	      p->next = newNode;
	    }
	  // if the next element in the list is null then the new node is placed at the end of the list
	  else
	    {
	      newNode->next=p->next;
	      p->next=newNode;
	    }
	  // otherwise make the new node the next element in the list where the loop had stopped
	}
    }
}

void llFree(LinkedList* ll)
{
  LinkedList* p = ll;

  while (p!=NULL)
    {
      LinkedList* oldP = p;
      p = p->next;
      free(oldP);
    }
}





/*
# include <stdio.h>
# include <stdlib.h>
# include "linkedList.h"

LinkedList* llCreate(){
  return NULL;
}

int llIsEmpty(LinkedList* list){
  return (list == NULL);
}

void llDisplay(LinkedList* list){

  LinkedList* p = list;

  printf("[");

  while (p != NULL){
    printf("%d, ", p->entry->ch);
    p = p->next;
  }
  printf("]\n");
  
}

void llAdd(LinkedList** list, tnode* newEntry){

  //creating a new node
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->entry = newEntry;
  newNode->next = NULL;

  //finding the end of the lsit
  LinkedList* p = *list;

  if(p == NULL){
    *list = newNode;
  }
  else {
    while(p->next != NULL){
      p = p->next;
    }
    // attaching it to the end
    p->next = newNode;
  }
}

void list_add_in_order(LinkedList** list, tnode* newEntry){

  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->entry = newEntry;

  LinkedList* p = *list;
  // if the list is empty it will add the new node to the beginning of the list
  if(p == NULL){
    newNode->next = NULL;
    *list = newNode;
  }
  else {
    // if the frequency of the newNodes's tnode is less than the frequency of the first node then it pushed the newNode to the top of the list  
    if(newEntry->weight < p->entry->weight){
      newNode->next = *list;
      *list = newNode;
    }
    else {
      // loop untill newEntry's freq(weight) is greater than the next entry in the list or the new entry's freq is less that the current entry or the next entry is NULL
      while ( (p->next != NULL) && !((newEntry->weight < p->next->entry->weight) && (newEntry->weight >= p->entry->weight))){
	p = p->next;
      }

      // if p->next is NULL then the newNode is added to the end of the list
      if(p->next == NULL){
	newNode->next = NULL;
	p->next = newNode;
	  
      }
      // else it will add the node next to where the loop stopped.
      else{
	newNode->next = p->next;
	p->next = newNode;
      } 
    }
  }
}

void llFree(LinkedList* list){
  LinkedList* p = list;

  while(p != NULL){
    LinkedList* temp = p;
    p = p->next;
    free(temp);
  }
}

tnode* removeFirst(LinkedList** list){

  LinkedList* p = *list;
  tnode* val = p->entry;
  p = p->next;

  *list = p;
  free(p);
  return val;
  
}
*/
