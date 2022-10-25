#include <iostream>
void Hello(int i) { std::cout << "Hello " << i << std::endl; }

template <class T>
void Test(T t) {
  std::cout << "Test " << sizeof(t) << std::endl;
}
/*
template <>
void Test(int i) {
  std::cout << "Test int\n";
}
*/
