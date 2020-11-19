# include <stdio.h>

// structure that stores the value and freqeuncy of the histogram
struct freq{
  int value;
  int frequency;
};


// function prototypes
void readScore(int* arr, int* count);
void printScores(int* arr, int count);
void calcHistogram (struct freq* histogram, int* entries, int sizeEntries, int sizeHist);
void displayScores(struct freq* histogram, int count);
void sortHistogram(struct freq* histogram, int size);
  
int main(){

  // initializing the arr to store the values from the file
  int arr[100];
  int count = 0;

  // setting all values in the array to 0
  for(int i = 0; i < 100; i++){
    arr[i] = 0;
  }

  // calling the read score function to check the input of scores that the system/file gives
  readScore(arr, &count);

  // caalling the printScore fuction to print all the scores that were read
  printScores(arr, count);
  printf("\n");
  // calculating the maximum in the array
  int max = 0;
  for(int i = 0; i < count; i++){
    if (arr[i] > max){
      max = arr[i];
    }
  }
  // calculating the size of the arr
  int arrSize = sizeof(arr) / sizeof(arr[0]);

  // creating a structure call histogram
  struct freq histogram[max];
  // setting all the values from max down and the freuqnecy to 0
  for(int i = 0; i <= max; i++){
    histogram[max-i].value = i;
    histogram[max-i].frequency = 0;
  }

  // calling the calcHistogram function to check value and frequency
  calcHistogram(histogram, arr, arrSize, max);

  // calling the displayScore funciton to show the histogram
  displayScores(histogram, max);
  printf("\n");
  // calling the sortHistogram function that sorts the histogram according to frequency
  sortHistogram(histogram, max);

  // calling the displayScores function that shows the sorted histogram
  displayScores(histogram, max);
  return 0;
}

void sortHistogram(struct freq* histogram, int size){
  struct freq temp;

  for (int i = 0; i < size; i++){
    for (int j = 0; j < (size - 1 - i); j++){

      if(histogram[j].frequency < histogram[j + 1].frequency){

	temp = histogram[j];
	histogram[j] = histogram[j+1];
	histogram[j+1] = temp;
	
      }
      
    }

  }

}
void displayScores(struct freq* histogram, int count){
  for(int i = 0; i < count; i++){
     if(histogram[i].frequency != 0){
      printf("value %d: freq %d\n", histogram[i].value, histogram[i].frequency);
     }
  }
  
}
void calcHistogram(struct freq* histogram, int* entries, int sizeEntries, int sizeHist){
  printf("Size Entries %d and Size Histogram %d\n", sizeEntries, sizeHist);
  
  for(int i = 0; i < sizeEntries-1; i++){
    int target = entries[i];
    int foundIt = 0;
    int j = 0;
    while ( j < sizeHist && histogram[j].value == entries[i]){
      j++;
      foundIt = 1;
    }

    if (foundIt){
      histogram[j].frequency++;
    }
    /*
    for(int j = 0; j < sizeHist; j++){
      if (entries[i] == histogram[j].value){
	histogram[j].frequency++;
      }
    }
    */
  }
  
}

  // function that prints the scores that were read by the scanner
void printScores(int* arr, int count){
  for (int i = 0; i < count-1; i++){
    printf("Score %d: %d\n", i, arr[i]);
  }

}

  // function that reads the score using the scanner
void readScore(int* arr, int* count){

  //looping though file
  int x = 1;

  while(x > 0){
    if (x == -1){
      break;
    }
	
    scanf("%d", &arr[*count]);
    x = arr[*count];
    *count = *count + 1;
    
  }

}
