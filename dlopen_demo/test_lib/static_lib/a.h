#ifndef DLOPEN_DEMO_TEST_LIB_STATIC_LIB_A_H_
#define DLOPEN_DEMO_TEST_LIB_STATIC_LIB_A_H_
class Demo1 {
 public:
  Demo1();
  int i{0};
};

Demo1& DemoInstance();

#endif  // DLOPEN_DEMO_TEST_LIB_STATIC_LIB_A_H_
