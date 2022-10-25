#include "node_handler.h"
#include <boost/thread.hpp>
#include <iostream>
#include <string>

namespace test {
class Stu {
 public:
  explicit Stu(std::string name) : name(name) {
    std::cout << "Stu construct " << name << "\n";
  }
  ~Stu() { std::cout << "Stu desconstruct " << name << "\n"; }
  void Test() {}
  std::string name;
};

boost::mutex g_mutex;
Stu g_demo("global");
// int NodeHandler::init() { return 1; }

NodeHandler::~NodeHandler() {
  boost::mutex::scoped_lock lock(g_mutex);
  g_demo.Test();
  std::cout << "NodeHandler deconstruct\n";
}

NodeHandler::NodeHandler() {
  boost::mutex::scoped_lock lock(g_mutex);
  std::cout << "NodeHandler construct\n";
}
}  // namespace test
