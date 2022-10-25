#include <thread>
#include <unordered_map>
#include "node_handler.h"
class Instance {
 public:
  Instance() { std::cout << "Instance construct\n"; }
  ~Instance() {
    std::cout << "Instance desconstruct\n";
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // std::cout << "Instance deconstruct endl\n";
  }

  static Instance& GetInstance() {
    static Instance demo1;
    return demo1;
  }

  void Add(std::shared_ptr<test::NodeHandler> node_handle);

 private:
  std::unordered_map<int, std::shared_ptr<test::NodeHandler>> node_handlers_;
};
