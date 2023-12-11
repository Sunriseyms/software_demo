#include <string.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char** argv) {
  std::thread t1 = std::thread([&] {
    int sum = 0;
    for (int i = 0;; i++) {
      void* p = malloc(i * 1024);
      sum += i;
      std::cout << "0malloc " << sum << "Kb memory" << std::endl;
      if (p == nullptr) {
        std::cout << "malloc " << i * 1024 << "bytes failed" << std::endl;
        return -1;
      }
      std::cout << "1malloc " << sum << "Kb memory" << std::endl;
      /*
      std::vector<int> v;
      v.reserve(i * 1024 * 10);
      for (int j = 0; j < i * 1024 * 10; j++) {
        v.emplace_back(j);
        if (j % (1024 * 1024) == 0) {
          std::cout << "v:" << v[j] << std::endl;
        }
      }
      std::cout << "v size:" << v.size() << std::endl;
      std::cout << "2malloc " << sum << "kb memory" << std::endl;
      */
      memset(p, '0', i * 1024);
      std::cout << "3malloc " << sum << "Kb memory" << std::endl;
      std::this_thread::sleep_for(
          std::chrono::milliseconds(1 * std::stoi(argv[1])));

      std::cout << "4malloc " << sum << "Kb memory" << std::endl;
      // free(p);
    }
  });
  /*
  std::thread t2 = std::thread([] {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    std::vector<void*> mem_pool;
    mem_pool.reserve(100);
    for (int i = 0; i < 100; i++) {
      auto elem = malloc(1024 * 1024);
      memset(elem, '1', 1024 * 1024);
      mem_pool.emplace_back(elem);
    }

    for (auto& elem : mem_pool) {
      std::cout << "free begin" << std::endl;
      //free(elem);
      std::cout << "free end" << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
  });
  */

  while (1) {
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxtest" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
  if (t1.joinable()) {
    t1.join();
  }
  //if (t2.joinable()) {
  //  t2.join();
 //}

  return 0;
}