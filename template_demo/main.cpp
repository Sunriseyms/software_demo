#include <memory>
#include "demo.h"
#include "log.h"
//#include "ros_log.h"
#include "native_log.h"

void Test(std::vector<Demo>&& d) {
  std::vector<Demo> test = std::forward<std::vector<Demo>>(d);
}

std::queue<std::function<void()>> queue_;
int main(int argc, char** argv) {
  /*
  std::vector<Demo> d;
  d.emplace_back(Demo(1));
  std::cout << "===========\n";
  Test(std::move(d));
  std::cout << "===========\n";
  */

  LogData("hello", 3);
  //Test();
  return 0;
}
