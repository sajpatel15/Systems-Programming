# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// structure that stores the value and freqeuncy of the histogram
typedef struct freq{
  char* word;
  int frequency;
} histogram;


// function prototypes
char** readWord(int* count);
void displayWord(char** arr, int count);
int calcHistogram (histogram** hist, char** entries, int count);
void displayHistogram(histogram** hist, int count);
void sortHistogram(histogram* hist, int size);
  
int main(){

  char** arr;
  int count = 0;
  int max;
  histogram*  hist;
  // calling the read score function to check the input of scores that the system/file gives
  arr = readWord(&count);

  printf("count: %d",count);
  // calling the printScore fuction to print all the scores that were read
  displayWord(arr, count);
  printf("\n");

  max = calcHistogram(&hist, arr, count);
  printf("Max: %d", max); 
  displayHistogram(&hist, max);
  printf("\n");

  sortHistogram(hist, max);
  displayHistogram(&hist, max);
  printf("\n");
  
 
  free(hist);
  
  return 0;
}

void sortHistogram(histogram* hist, int size){

  for (int i = 0; i < size - 1; i++){
    int maxIndex = i;
    for (int j = i + 1; j < size; j++){

      if ((*(hist + j)).frequency > (*(hist + maxIndex)).frequency){
	maxIndex = j;
      }
    }
    histogram temp = *(hist + maxIndex);
    *(hist+maxIndex) = *(hist + i);
    *(hist + i) = temp;

  }

}
void displayHistogram(histogram** hist, int count){
  
  for(int i = 0; i < count; i++){
    
    printf("word %s: freq %d\n", (*hist + i)->word, (*hist + i)->frequency);
    
  }
  
}
int calcHistogram (histogram** hist, char** entries, int count){

  *hist = (histogram*) malloc(count * sizeof(histogram)); 

  int filled = 0;
  for(int i = 0; i < count; i++){
    int bool = 0;
    int j = 0;
    while ( j < filled && !bool){

      if(!strcmp(*(entries + i),(*((*hist) + j)).word)){
	bool = 1;
      } else {
	j++;
      }
     
    }

    if (!bool){
      (*((*hist) + j)).word = *(entries + i);
      (*((*hist) + j)).frequency = 1;
      filled++;
    }else{
      ((*((*hist) + j)).frequency)++;

	}
  }
  free(entries);
  return filled;
}

void displayWord(char** arr, int count){
  for (int i = 0; i < count; i++){
    printf("Word %d: %s\n", i, *(arr + i));
  }

}

  // function that reads the score using the scanner
char** readWord(int* count){

  
  char** arr = (char**)malloc(100 * sizeof(char*)); // array bytes on heap
  char word[15];
  
  //looping though file
  while(scanf("%s", word) != EOF){
    char c = *word;
    int length = 0;

    while(c != '\0'){
      length++;
      c = *(word + length);
    }

    char* next = (char*)malloc((length+1)*sizeof(char));
    for(int i = 0; i < length + 1; i++){
      *(next + i) = *(word + i);
     
    }
  

    *(arr + (*count)) = next;
    (*count)++;
  }
  
  return arr;
}
