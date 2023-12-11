#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char** argv) {
  std::vector<std::thread> t;
  t.reserve(std::stoi(argv[1]));
  for (int i = 0; i < std::stoi(argv[1]); ++i) {
    t.emplace_back(std::thread([]() {
      int i = 0;
      while (true) {
        if (i % 100000 == 0) {
          std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
        i++;
      }
    }));
  }

  for (auto&& thread : t) {
    if (thread.joinable()) {
      thread.join();
    }
  }

  return 0;
}