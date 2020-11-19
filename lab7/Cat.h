#ifndef CAT_H
#define CAT_H
#include <iostream>
#include <string.h>
#include "Animal.h"


class Cat : public Animal{

 private:
  char name[20];
  char sound[20];

 public:
  Cat();
  Cat(const char* c,const char* n);
  Cat(const Cat& c);
  virtual ~Cat();
  char* getName();
  void makeSound();

};

#endif
