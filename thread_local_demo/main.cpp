#include <iostream>
#include <string>
#include <thread>

thread_local int hello[20] = {1, 2, 3, 4};
int world;

int main(int agrc, char** argv) {
  std::cout << std::this_thread::get_id() << " hello: " << hello[0]
            << std::endl;
  /*
    std::thread t1 = std::thread([]() {
      std::cout << std::this_thread::get_id() << " hello: " << hello[0]
                << std::endl;
    });

    t1.join();
    */
  return 0;
}
