#include "instance.h"

void Instance::Add(std::shared_ptr<test::NodeHandler> node_handle) {
  node_handlers_.insert({1, node_handle});
}
