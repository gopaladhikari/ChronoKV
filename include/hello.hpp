#pragma once

#include <string>

class Hello
{
private:
  std::string name;

public:
  Hello(std::string incomingName) : name(incomingName) {}

  void sayHello() const;
};
