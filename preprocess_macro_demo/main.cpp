#include <iostream>

int main() {
#ifdef Test
  std::cout << "has Test preprocess macro\n";
#else
  std::cout << "don't have Test preprocess macro\n";
#endif
  return 0;
}
