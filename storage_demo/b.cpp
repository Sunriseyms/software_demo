#include "b.h"
#include <iostream>
#include "a.h"

namespace B {
void Print() {
  std::cout << "B:" << hello << " address of hello:" << &hello << std::endl;
  Demo::GetInstance().Print();
}
void SetA(int val) {
  hello = val;
  Demo::GetInstance().SetVal(val);
}
}  // namespace B
