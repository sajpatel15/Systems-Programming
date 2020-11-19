#include <iostream>
#include <string.h>
#include "Dog.h"

Dog::Dog() : Animal(){
  std::cout << "Dog constructor called\n";
  strcpy(this->name, "Goofy");
  strcpy(this->sound, "woof");
}

Dog::Dog(const char* c, const char* n) : Animal(c){
  std::cout << "Dog 2 parm constructor called\n";
  strcpy(this->name, n);
  strcpy(this->sound, "woof");
}

Dog::Dog(const Dog& d) : Animal(d){
  std::cout << "Dog copy constructor called\n";
  strcpy(this->name, d.name);
  strcpy(this->sound,d.sound);
}

Dog::~Dog(){
  std::cout << "Dog destructor called\n";
}

char* Dog::getName(){
  std::cout << "Dog getName called\n";
  return this->name;
}

void Dog::makeSound(){
  std::cout << "Dog makeSound called\n";
  std::cout << this->sound << "\n";
}
