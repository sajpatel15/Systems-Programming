#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char str1[6]; // str's type is char*
  // char* str1 = (char*)malloc(5*sizeof(char)); // HEAP

  str1[0] = 'h';
  str1[1] = 'e';
  str1[2] = 'l';
  str1[3] = 'l';
  str1[4] = 'o';
  str1[5] = '\0';
  
  printf("My string is %s\n", str1);

  int len = strlen(str1);
  printf("%d\n", len);

  char* str2 = "howdy";

  if(strcmp(str1, str2) == 0){ // CompareTo -- not equals
    printf("equals\n");
  } else {
    printf("not equal\n");
  }

  strcpy(str2, str1); // strcpy(dst, from)

  
  /*
  int i = 0;
  while(str1[i] != '\0'){
    printf("%c", str1[i]);
    i++;
  }
  printf("\n");
  */
}
