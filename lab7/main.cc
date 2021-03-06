// compile with:
// g++ Main.cc Animal.cc Dog.cc Cat.cc Duck.cc -o Animaltest
#include <iostream>
#include <string.h>
#include "Animal.h"
#include "Dog.h"
#include "Cat.h"
#include "Duck.h"

int main(){
  
  Dog* d1 = new Dog("Fido", "Brown");

  std::cout << d1->getName() << "\n";
  std::cout << "dog as dog making sound\n";
  d1->makeSound();

  std::cout << "\n";
  
  Animal* a1 = new Dog("Stricker", "Brown");
  std::cout << a1->getName() << "\n";
  std::cout << "animal as dog making sound\n";
  a1->makeSound();

  std::cout << "\n";

  Cat* c1 = new Cat("Whiskers", "Tabby");
  std::cout << c1->getName() << "\n";
  std::cout << "cat as cat making sound\n";
  c1->makeSound();

  std::cout << "\n";

  Cat* c2 = new Cat(*c1);
  std::cout << c2->getName() << "\n";
  std::cout << "cat 2 as cat making sound\n";
  c2->makeSound();

  std::cout << "\n";

  Duck* d2 = new Duck("Grey");
  std::cout << d2->getColor() << "\n";
  std::cout << "Duck as Duck making sound\n";
  d2->makeSound();

  std::cout << "\n";
  
  Animal* a2 = new Duck(*d2);
  std::cout << a2->getColor() << "\n";
  std::cout << "Duck as Animal making sound\n";
  a2->makeSound();

  std::cout << "\n";
  
}
