#include "a.h"
#include <iostream>

namespace A {
void Print() {
  std::cout << "A:" << hello << " address of hello:" << &hello << std::endl;
  Demo::GetInstance().Print();
}
void SetA(int val) {
  hello = val;
  Demo::GetInstance().SetVal(val);
}
}  // namespace A
