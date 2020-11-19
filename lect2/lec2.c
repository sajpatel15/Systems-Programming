#include <stdio.h> // printf/scanf
#include <stdlib.h> // malloc

int* fill( int* cnt){
  int max = 10;
  // int b[max]; // array on runtime stack
  int* b = (int*)malloc(max * sizeof(int)); // bytes on the heap
  
  int c = 6;
  for (int i = 0; i < c; i++){
    b[i] = i*2;
  }

  *cnt = c; // "returns" c's value to count in main

  return b;
}

void foo() {
  int x[20];

  for(int i = 0; i < 20; i++){
    x[i] = i;
  }

}

int main() {
  
  int count;
  int* a;

  a = fill(&count);
  
  for(int i = 0; i < count; i++){
    printf("in main: %d: %d\n",i, a[i]);
  }

  foo();

  printf("Here\n");
  for(int i = 0; i < count; i++){
    printf("in main: %d: %d\n",i, a[i]);
  }

 
}
