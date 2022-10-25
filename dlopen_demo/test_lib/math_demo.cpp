#include "math_demo.h"
#include <iostream>
#include "math1.h"
#include "static_lib/a.h"

class Demo {
 public:
  int Add(int a, int b) { return a + b; }
};

int Add(int a, int b) {
  auto& demo1 = DemoInstance();
  demo1.i++;
  std::cout << "demo:" << demo1.i << " address:" << &demo1 << std::endl;
  Demo demo;
  return demo.Add(a, b) + math1::Add(a, b);
}
