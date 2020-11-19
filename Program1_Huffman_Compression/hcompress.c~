#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

tnode* createFreqTable(char* text);
tnode* createHuffmanTree(tnode* leafNodes);
void encodeFile(char* text, tnode* leafNodes);
void decodeFile(char* text, tnode* root);

int main(int argc, char* argv[]){
  // Check the make sure the input parameters are correct
  if (argc!=3){
    printf("Error: the correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n");
    fflush(stdout);
    exit(1);
  }
  // Create the frequency table by reading the genereic file
  tnode* leafNodes = createFreqTable("decind.txt");
  
  // Create the huffman tree from the frequency table
  tnode* treeRoot = createHuffmanTree(leafNodes);

  //encode
  if (strcmp(argv[1],"-e")==0){
    // Pass the leafNodes since it will process bottom up
    encodeFile(argv[2],leafNodes);
  }
  else{ // decode
    // Pass the tree root since it will process top down
    decodeFile(argv[2],treeRoot);
  }
  
  free(leafNodes);
  //free(treeRoot);
  return 0;

}


// method that creates the frequency table
tnode* createFreqTable(char* text){
  // creating a file object and opening it as a readable 
  FILE* fp;
  fp = fopen(text, "r");

  // creating an array of tree nodes for the first 128 ASCII characters
  tnode* leafNodes = (tnode*)malloc(129 * sizeof(tnode));

  // setting the characters for the leaf to i, its freq to 0 and its parents and children to null
  for(int i = 0; i < 128; i++){
    leafNodes[i].ch = i;
    leafNodes[i].weight = 0;
    leafNodes[i].parent = NULL;
    leafNodes[i].left = NULL;
    leafNodes[i].right = NULL;
    
  }
  
  // reading in characters from the text file and adds 1 to the weight of the character read
  int i = fgetc(fp);
  while(i != EOF){
    leafNodes[i].weight++;
    i = fgetc(fp);
  }
  
  // closing the link to the file since all reading of data is complete
  fclose(fp);
  //returning the leaf nodes
  return leafNodes;
}


// method that creates the huffman tree
tnode* createHuffmanTree(tnode* leafNodes){

  // creating an array of linked lists
  LinkedList* tnodes = llCreate();

  // adding all elements of the leaf node into the linked list
  for(int i = 0; i < 128; i++){
    list_add_in_order(&tnodes, leafNodes+i);
  }
  
  LinkedList* p = tnodes;
  
  while(p->next != NULL){

    // getting the lowest two nodes
    tnode* left = p->entry;
    tnode* right =p->next->entry;

    // combining the lowest of the two nodes into a singlular node
    tnode* newtnode = (tnode*)malloc(sizeof(tnode));
    newtnode->ch = -2; // setting the character of the newtnode to a random character of -2
    // adding the weights of the left and right child to get the combined weight for the newtnode
    newtnode->weight = left->weight + right->weight;

    //setting the tnodes children to left and right
    newtnode->right = right;
    newtnode->left = left;

    // setting left and right's parents to the newtnode
    right->parent = newtnode;
    left->parent = newtnode;

    // adding the newtnode back into the list
    list_add_in_order(&p, newtnode);
    p = p->next->next;
  }
  // setting the root to the current entry in the list
  tnode* root = (*p).entry;
  llFree(tnodes);
  
  // returning the root
  return root;
  
}

void encodeFile(char* text, tnode* leaves){
  FILE* fpi = fopen(text, "r");
  
  char filename[strlen(text+4)];
  strcpy(filename, text);
  strcat(filename, ".huf");
  
  FILE* fpo = fopen(filename, "w"); // this will create a file that is the text.huf that we will write to
  
  char in;
  unsigned char out = 0; // this is the character we will write out to the file when we have enough bits processed
  
  in = fgetc(fpi);
  
  int sizeOfOut = 0;
  
  while(in != EOF){
      unsigned long bin = 0; //
      tnode* current = leaves + in; // finds the leafNode corresponding with the character read in from the file
      int length = 0; // keeps track of how many branches are traversed

      tnode* old; //tnode pointer to keep track of the previous node
      // loop that runs over all tnodes and adds its value to the bin varible which is then uploaded to the .huf fil
      while(current->parent != NULL){
	  old = current; // sets old to the current node read in
	  current = current->parent; // sets current equal to the parent of the current node
	  length++; // increments number of brances traversed
	  
	  if(current->right == old){
	    
	      bin |= 1; // if the branch that was read in was a right child then or bin with 1 to put a 1 as the LSB
	  }
	  else{
	    // otherwise a 0 is read in and nothing needs to be done as shifting left will add a 0 to the bitstring
	  }
	  bin <<= 1; // shifts bin left by 1 so another bit can be put in as another branch is traversed
	}
      bin >>= 1; // shifts bin to the right by 1 as the while loop shifts to the left one too far
      
      // loops for the amount of times a branch was traversed
      for(int i = 0; i < length; i++){
	
	  out |= (bin&1); // sets out to out or bin and 1 to get the last bit that was processed from the tree

	  bin >>= 1; // right shifts bin by one to repeat the process in the next iteration
	  sizeOfOut++; // increments the size of out by 1
	  
	  // if the size of out is less than 8 bits then shift out to the left by 1 
	  if(sizeOfOut < 8){  
	      out <<= 1;
	  }
	  
	  // if the size of out is 8 then write out the bits to the file and set size of out and out back to 0
	  if(sizeOfOut == 8){
	    //printf("Encode Out:%d\n", out);
	    fputc(out, fpo);
	    sizeOfOut = 0;
	    out = 0;
	  }
	 
	} // loops for the amount of times a branch was traversed
      in = fgetc(fpi); // read in the next character
    }
  // the loop runs until it reaches the end of the file being read in
  fclose(fpi);
  
  fclose(fpo);
}


void decodeFile(char* text, tnode* root){
  //printf("HERE");
  // making a pointer and setting it to the root of the tnode* tree
  tnode* r = root;
  //printf("Size of root %ld\n", sizeof(root));
  
  FILE* fpin = fopen(text, "r"); // opening the compressed file to read data from
  //printf("File reading open");
  
  // carrying out string manipulation to name the decompressed file
  char file_name[strlen(text) + 4];
  strcpy(file_name, text);
  strcat(file_name, ".dec");
  FILE* fpout = fopen(file_name, "w");
  //printf("File out open");
  
  char out = 1; // starting out with the output as 1 so the first iteration of the loop will run
  
  // varaible storing the number of bits that are remaining to be decompressed in that variable
  int remainingBits = 8;
  
  // reading in the first character from the encoded
  char in;
  int scan = fscanf(fpin,"%c", &in); 
   
  while(scan != -1){
   
    out = 0;
    tnode* cur = r; // setting the current node pointing at the root
    
    // loop that runs as long as the current node's ch is -2 which was the arbituary character it was set to when encoding the file
    while(cur->ch == -2){
      // sets the current node point to the right child if the current bit of the string is 1
      if(in & (1 << (remainingBits - 1))){
	cur = cur->right;
	
      }
      // else it sets it to the left child
      else{
	cur = cur->left;
      }
      //decrements the number of bits left to process by
      remainingBits--;

      // checks to see if there are no more remianingBits in which case it resets it to 8 and read in a new character from the encoded file
      if(remainingBits == 0){
	//printf("getting another input\n");
	scan = fscanf(fpin, "%c", &in);
	remainingBits = 8;
      }
    }
    
    // sets out to the current character of the node it is at
    out = cur->ch;
    
    
    // this checks if it is not an ending character it which case it will just write out to the file
    fputc(out, fpout);
    
  }
  // closing both instances of files because nothing more is being written to or read from either files
  fclose(fpin);
  fclose(fpout);
}
