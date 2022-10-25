#include <iostream>
#include <memory>
#include "instance.h"
#include "node_handler.h"
using namespace test;
int main() {
  Instance::GetInstance();
  std::shared_ptr<NodeHandler> n_ptr = std::make_shared<NodeHandler>();
  // Instance::GetInstance().Add(n_ptr);
  // n_ptr->init();
  // n.init();
}
