#ifndef DOG_H
#define DOG_H
#include <iostream>
#include <string.h>
#include "Animal.h"


class Dog : public Animal{

 private:
  char name[20];
  char sound[20];

 public:
  Dog();
  Dog(const char* c,const char* n);
  Dog(const Dog& d);
  virtual ~Dog();
  char* getName();
  void makeSound();

};

#endif
