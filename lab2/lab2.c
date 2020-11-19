# include <stdio.h>
# include <stdlib.h>

// structure that stores the value and freqeuncy of the histogram
typedef struct freq{
  int value;
  int frequency;
} histogram;


// function prototypes
int* readScore(int* count);
void printScores(int* arr, int count);
int calcHistogram (histogram** hist, int* entries, int count);
void displayScores(histogram* hist, int count);
void sortHistogram(histogram* hist, int size);
  
int main(){

  int* arr;
  int count;
  int max;
  histogram*  hist;
  // calling the read score function to check the input of scores that the system/file gives
  arr = readScore(&count);

  // calling the printScore fuction to print all the scores that were read
  printScores(arr, count);
  printf("\n");

  max = calcHistogram(&hist, arr, count);
  printf("Max is: %d\n",max); 
  displayScores(hist, max);
  printf("\n");

  sortHistogram(hist,max);
  displayScores(hist, max);
  free(hist);

  
  return 0;
}

void sortHistogram(histogram* hist, int size){
  histogram temp;

  for (int i = 0; i < size; i++){
    for (int j = 0; j < (size - 1 - i); j++){

      if(hist[j].frequency < hist[j + 1].frequency){

	temp = hist[j];
	hist[j] = hist[j+1];
	hist[j+1] = temp;
	
      }
      
    }

  }

}
void displayScores(histogram* hist, int count){
  
  for(int i = 0; i < count; i++){
    if((hist + i)->frequency != 0){
      printf("value %d: freq %d\n", (hist + i)->value, (hist + i)->frequency);
     }
  }
  
}
int calcHistogram (histogram** hist, int* entries, int count){

  *hist = (histogram*) malloc(count * sizeof(histogram)); 

  int filled = 0;
  for(int i = 0; i < count; i++){
    int target = *(entries + i);
    int j = 0;
    while ( j < count && target != (*hist + j)->value){
      j++;
     
    }

    if (j != count){
      (*hist + j)->frequency++;
    }else{
      (*hist + filled)->value = target;
      (*hist + filled)->frequency = 1;
      filled++;
    }
  }
 
  free(entries);
  
  return filled;
  
}

  // function that prints the scores that were read by the scanner
void printScores(int* arr, int count){
  for (int i = 0; i < count; i++){
    printf("Score %d: %d\n", i, arr[i]);
  }

}

  // function that reads the score using the scanner
int* readScore(int* count){

  int max = 100;
  int* arr = (int*)malloc(max * sizeof(int)); // array bytes on heap
  
  //looping though file
  int x = 1;
  int c = 0;
  while(x > 0){
    int k = 0;
    scanf("%d",&k);
    if (k != -1){
      *(arr+c) = k;
     
      c = c + 1;
    } else {
      x = -1;
    }
  }
  *count = c; // "returns" c's value to count in main
  return arr;
}
