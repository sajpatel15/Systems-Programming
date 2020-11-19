
typedef struct treeNode {
  double weight; // number of times the char occurs
  int ch; // the char itself (used as int cause in c we an interchange ints and chars as they all work on ascii)
  struct treeNode* left; // the left child of the current node
  struct treeNode* right; // the right child of the current node
  struct treeNode* parent; // the parent of the current node
}tnode;

typedef struct node {

  tnode* entry; // the entry occupied in the list
  struct node* next; // the next value that is on the list

} LinkedList;

// all the methods needed to creat this tree
LinkedList* llCreate();
int llIsEmpty(LinkedList* list);
void llDisplay(LinkedList* list);
void llAdd (LinkedList** list, tnode* newEntry);
void list_add_in_order(LinkedList** list, tnode* newEntry);
void llFree(LinkedList* list);
tnode* removeFirst(LinkedList** first);
  
