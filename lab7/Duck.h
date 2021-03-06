#ifndef DUCK_H
#define DUCK_H
#include <iostream>
#include <string.h>
#include "Animal.h"


class Duck : public Animal{

 private:
  char sound[20];

 public:
  Duck();
  Duck(const char* c);
  Duck(const Duck& d);
  virtual ~Duck();
  void makeSound();
  char* getName();

};

#endif
