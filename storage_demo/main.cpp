#include "a.h"
#include "b.h"

int main() {
  A::Print();
  B::Print();
  std::cout << std::endl;

  A::SetA(10);
  A::Print();
  B::Print();
  std::cout << std::endl;

  B::SetA(100);
  A::Print();
  B::Print();

  std::cout << std::endl;
  hello = 1000;
  A::Print();
  B::Print();
}
