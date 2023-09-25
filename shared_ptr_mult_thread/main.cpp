// Type your code here, or load an example.
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
using namespace std::chrono_literals;

struct Data {
  int i;
};

class Monitor {
 public:
  Monitor() { data_vector.resize(1); }
  void update() {
    std::shared_ptr<Data> tmp = std::make_shared<Data>();
    data_ptr_ = tmp;
    data_vector[0] = data_ptr_;
  }
  std::shared_ptr<Data> data_ptr_;
  std::vector<std::shared_ptr<Data>> data_vector;

  void run() {
    std::thread run_thread = std::thread([&]() {
      while (1) {
        update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
    run_thread.detach();
  }
};

class ReportMonitor {
 public:
  void pop() {
    std::shared_ptr<Data>& tmp = m->data_vector[0];
    auto elem = tmp;
  }

  void run() {
    std::thread run_thread = std::thread([&]() {
      while (1) {
        pop();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
    run_thread.detach();
  }

  Monitor* m;
};

int main() {
  Monitor m;
  ReportMonitor report_monitor;
  report_monitor.m = &m;

  m.run();
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  report_monitor.run();

  while (1) {
  }
  return 0;
}