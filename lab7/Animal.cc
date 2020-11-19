#include <iostream>
#include <string.h>
#include "Animal.h"


Animal::Animal(){
  std::cout << "Animal default constructor called\n";
  strcpy(this->color, "White");
  strcpy(this->sound, "Random sound");
}

Animal::Animal(const char* c){
  std::cout << "Animal 1 parm constructor called\n";
  strcpy(this->color, c);
  strcpy(this->sound, "Random sound");
}

Animal::Animal(const Animal& a){
  std::cout << "Animal copy constructor called\n";
  strcpy(this->color, a.color);
  strcpy(this->sound, a.sound);
}

Animal::~Animal(){
  std::cout << "Animal destructor called\n";
}

char* Animal::getColor(){
  std::cout << "Animal get color called\n";
  return this->color;
}

void Animal::makeSound(){
  std::cout << "Animal makeSound called\n";
  std::cout << this->sound << "\n";
}

