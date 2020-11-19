#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "duSocket.h"
#include <omp.h>
int main(){

  int numThreads = 5;
  omp_set_num_threads(numThreads);
  //int numPrime[numThreads];

  int ss = setupServerSocket(7000);
  int s[5];

  int range_start = 100;
  int range_end = 1000;

  int n = range_end - range_start;

  int totalPrimes = 0;

  for(int i = 0; i < numThreads; i++){
    s[i] = serverSocketAccept(ss);
  }

#pragma omp parallel reduction(+:totalPrimes)
  {
    int threadNum = omp_get_thread_num();
    int start = ((n / numThreads) * threadNum) + range_start;
    int stop = ((n / numThreads) * (threadNum + 1)) + range_start;

    writeInt(start, s[threadNum]);
    writeInt(stop, s[threadNum]);
    
    int prime = readInt(s[threadNum]);
    totalPrimes += prime;
  }
  printf("Prime on [%d, %d] is %d\n", range_start, range_end, totalPrimes);

  for(int i = 0; i < numThreads; i++){
    close(s[i]);
  }
  close(ss);



}
