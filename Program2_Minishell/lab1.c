#include <stdio.h>

struct freq {
  int number;
  int frequency;
};

//prototypes
void readScores(int* ar, int* cnt);
void displayScores(int* ar, int cnt);
void calcHistogram(int* ar, int cnt, int* values, struct freq* scrs);
void displayHistogram(int values, struct freq* scrs);
void sortHistogram(int* values, struct freq* scrs);
void swap(struct freq* scr1, struct freq* scr2);

int main(){
  int values[100];
  int count = 0;
  readScores(values, &count);
  displayScores(values, count);
  struct freq scores[count];
  int distinctScores = 0;
  calcHistogram(values, count, &distinctScores, scores);
  printf("Histogram\n");
  displayHistogram(distinctScores, scores);
  printf("Sorted Histogram\n");
  sortHistogram(&distinctScores, scores);
  displayHistogram(distinctScores, scores);
}

void readScores(int* ar, int* cnt)
{
  int x = 0;
  while(x!=EOF)
    {
      x = scanf("%d", &ar[*cnt]);
      if (x!=EOF)
	{
	  (*cnt)++;
	}
    }
}

void displayScores(int* ar, int cnt)
{
  for (int i = 0; i<cnt; i++)
    {
      printf("score %d: %d\n", i, ar[i]);
    }
}

void calcHistogram(int* ar, int cnt, int* values, struct freq* scrs) {
  int frequencies;
  for (int i = 0; i<cnt; i++)
    {
      frequencies = 1;
      for (int j = i+1; j<cnt; j++)
	{
	  if (ar[i]==ar[j])
	    {
	      frequencies++;
	      scrs[j].number = 0;
	    }
	}
      if (scrs[i].number!=0)
	{
	  scrs[*values].number = ar[i];
	  scrs[*values].frequency = frequencies;
	  (*values)++;
	}
    }

}

void displayHistogram(int values, struct freq* scrs)
{
  for (int i = 0; i<values; i++)
    {
      printf("value %d: freq %d\n", scrs[i].number, scrs[i].frequency);
    }
}

void swap(struct freq* scr1, struct freq* scr2)
{
  struct freq temp = *scr2;
  *scr2 = *scr1;
  *scr1 = temp;
}

void sortHistogram(int* values, struct freq* scrs)
{
  for (int i=0; i<*values-1; i++)
    {
      int maxIndex = i;
      for (int j = i + 1; j<*values; j++)
	{
	  if (scrs[j].frequency>scrs[maxIndex].frequency)
	    {
	      maxIndex = j;
	    }
	}
      if (maxIndex!=i)
	{
	  swap(&scrs[i], &scrs[maxIndex]);
	}
    }
}
