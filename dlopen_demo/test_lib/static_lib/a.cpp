#include "a.h"
#include <iostream>

Demo1::Demo1() { std::cout << "Demo1 construnct" << std::endl; }

Demo1& DemoInstance() {
  static Demo1 d;
  return d;
}
