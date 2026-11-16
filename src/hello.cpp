#include <iostream>
#include "hello.hpp"

void Hello::sayHello() const
{
  std::cout << "Hello " + name << std::endl;
}