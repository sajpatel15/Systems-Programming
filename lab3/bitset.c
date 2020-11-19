#include <stdio.h>
#include <math.h>

typedef unsigned short bitSet;

bitSet makeBitSet(){
  bitSet bs = 0;
  return bs;
}

int bitValue(bitSet bs, int index){
  int val = (bs>>index) & 1u;
  return val;
}

void displayBitSet(bitSet bs){
  for(int i = 15; i >= 0; i--){
    printf("%d ", bitValue(bs,i));
  }
  printf("\n");

}

void setBit(bitSet* bs, int index){
  *bs = (1u<<index) | *bs;
}

void clearBit(bitSet* bs, int index){

  *bs = ~(1u<<index) & *bs;
}



int main(){

  bitSet bs = makeBitSet();
  
  printf("Unfilled bitset\n");
  displayBitSet(bs);
  
  for(int i = 0; i < 16; i += 2){
    setBit(&bs,i);
  }
  printf("filled bitset with alterative 1's \n");
  displayBitSet(bs);
  
  for(int i = 0; i < 16; i++){
    setBit(&bs,i);
  }

  for(int i = 0; i < 16; i += 5){
    clearBit(&bs,i);
  }
  printf("filled bitset with reccuring 0's every 5 iteration\n");
  displayBitSet(bs);

  int val = bitValue(bs,5);
  printf("printing the value of the 5th index bit in the bitset: %d\n", val);
   
}
