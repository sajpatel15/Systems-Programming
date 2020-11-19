#include <iostream>
#include <string.h>
#include "Duck.h"

Duck::Duck() : Animal(){
  std::cout << "Duck constructor called\n";
  strcpy(this->sound, "Quack");
}

Duck::Duck(const char* c) : Animal(c){
  std::cout << "Duck 1 parm constructor called\n";
  strcpy(this->sound, "Quack");
}

Duck::Duck(const Duck& d) : Animal(d){
  std::cout << "Duck copy constructor called\n";
  strcpy(this->sound,d.sound);
}

Duck::~Duck(){
  std::cout << "Duck destructor called\n";
}

void Duck::makeSound(){
  std::cout << "Duck makeSound called\n";
  std::cout << this->sound << "\n";
}

char* Duck::getName(){
  return 0;
}
