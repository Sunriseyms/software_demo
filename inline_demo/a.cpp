#include "a.h"

// namespace {
inline int sum(int a, int b) { return a + b; }
//}  // namespace

namespace test {
int add(int a, int b) {
  int result = sum(a, b);
  return result;
}
}  // namespace test
