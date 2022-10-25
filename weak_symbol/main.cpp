#include <iostream>

void Hello(int i) __attribute__((weak));
template <class T>
void Test(T t) __attribute__((weak));

/*
template <>
void Test(double d) {
  std::cout << "Test double\n";
}*/

template <class T>
void Test0(T t) {
  if (Test<T>) {
    Test(t);
  } else {
    std::cout << "Test0\n";
  }
}
// template <class T>
// void Test(T t);

int main() {
  if (Hello) {
    Hello(10);
    std::cout << "Hello is strong symbol\n";
  } else {
    std::cout << "Hello is weak symbol\n";
  }

  Test0(10);
  Test0(10.3);
  /*
if (Test<int>) {
  std::cout << "Test<int> is strong symbol\n";
} else {
  std::cout << "Test<int> is weak symbol\n";
}*/
  return 0;
}
