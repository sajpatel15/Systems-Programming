#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binToDec(char* bin){
  int d = 0;
  int rem;
  int p = 0;
  int count = 0;
  while(bin[count] != '\0'){
    count++;
  }
 
  for(int i = count - 1; i >= 0; i--){
    
      d += (bin[i] - 48) * pow(2, p);
      p++;
      
  }
  return d;
}


int baseToDec(int base, char* bin){
  int d = 0;
  int rem;
  int p = 0;
  int count = 0;
  while(bin[count] != '\0'){
    count++;
  }
 
  for(int i = count - 1; i >= 0; i--){
    if(bin[i] < 58){
      d += (bin[i] - 48) *  pow(base, p);
      p++;
    } else if(bin[i] > 96){
      d += ((bin[i] - 97) + 10) * pow(base,p);
      p++;
    }
      
  }
  return d;
}

void reverse(char* str){

  int len = strlen(str);

  for(int i = 0, j = len - 1; i < j; i++, j--){
    char ch = str[i];
    str[i] = str[j];
    str[j] = ch;
  }
}

char* decToBin(int dec){
  char* bin = (char*) malloc(32);
  int i = 0;

  while(dec != 0){
    int r = dec % 2;
    if (r == 1){
      *(bin + i) = '1';
    } else {
      *(bin + i) = '0';
    }
    i++;
    dec = dec/2;
  }
  
  *(bin + i) = '\0';
  reverse(bin);
  return bin;
}

char* decToBase(int base, int dec){
  char* bin = (char*) malloc(32);
  int i = 0;

  while(dec != 0){
    int r = dec % base;
    
    if (r < 10){
      *(bin + i) = 48 + r;
    } else if (r >= 10) {
      *(bin + i) = (97+(r-10));
    }
    i++;
    dec = dec/base;
  }
  
  *(bin + i) = '\0';
  reverse(bin);
  return bin;
}

int main(){

  char* bin = "11001";
  int dec = baseToDec(2,bin);
  int dec2 = baseToDec(8, "157");
  int dec3 = baseToDec(16, "f8");
  
  printf("binary: %s, decimal: %d\n", bin, dec);
  printf("decimal: %d\n", dec2);
  printf("decimal: %d\n", dec3);
  
  bin = decToBase(2,dec);
  printf("binary: %s, decimal: %d\n", bin, dec);
  free(bin);
  
  bin = decToBase(8,111);
  printf("octal: %s\n", bin);
  free(bin);
  
  bin = decToBase(16, 248);
  printf("hex: %s\n", bin);
  free(bin);

  return 0;
}
