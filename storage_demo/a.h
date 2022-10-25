#ifndef STORAGE_DEMO_A_H_
#define STORAGE_DEMO_A_H_
#include <iostream>
class Demo {
 public:
  static Demo& GetInstance() {
    static Demo demo;
    return demo;
  }
  void SetVal(int val) { val_ = val; }
  void Print() {
    std::cout << "Demo:" << val_ << " address of Demo:" << this << std::endl;
  }

 private:
  Demo() {}
  int val_{0};
};

static int hello = 3;

namespace A {
void Print();
void SetA(int a);
}  // namespace A

#endif  // STORAGE_DEMO_A_H_
