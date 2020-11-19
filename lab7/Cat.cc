#include <iostream>
#include <string.h>
#include "Cat.h"

Cat::Cat() : Animal(){
  std::cout << "Cat constructor called\n";
  strcpy(this->name, "Mr.Cat");
  strcpy(this->sound, "meeow");
}

Cat::Cat(const char* c, const char* n) : Animal(c){
  std::cout << "Cat 2 parm constructor called\n";
  strcpy(this->name, n);
  strcpy(this->sound, "meeow");
}

Cat::Cat(const Cat& c) : Animal(c){
  std::cout << "Cat copy constructor called\n";
  strcpy(this->name, c.name);
  strcpy(this->sound,c.sound);
}

Cat::~Cat(){
  std::cout << "Cat destructor called\n";
}

char* Cat::getName(){
  std::cout << "Cat getName called\n";
  return this->name;
}

void Cat::makeSound(){
  std::cout << "Cat makeSound called\n";
  std::cout << this->sound << "\n";
}
