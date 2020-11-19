#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "duSocket.h"

int isPrime(int num){

  for(int i = 2; i < num/2; i++){
    if(num % i == 0){
      return 0;
    }
  }
  return 1;  
}

int primeRange(int start, int stop){
  int count = 0;
  for(int i = start; i < stop; i++){
    if(isPrime(i)){
      count++;
    }
  }
  return count;
}

int main(){

  int s = callServer("localHost", 7000);
  int start = readInt(s);
  int stop = readInt(s);
  int prime = primeRange(start, stop);
  writeInt(prime, s);
  close(s);

}
