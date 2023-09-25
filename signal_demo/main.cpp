#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

class Demo {
public:
  ~Demo() {
    for (int i = 0; i < 100; i++) {
      std::cout << "i:" << i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
};

static Demo demo;

void signal_handle(int sig) {
  if (sig == SIGINT) {
    signal(SIGTERM, SIG_IGN);
    std::cout << "handle single:" << sig << std::endl;
    exit(0);
    std::raise(SIGSEGV);
    std::cout << "end" << std::endl;
  } else if(sig == SIGTERM) {
    std::cout << "handle single:" << sig << std::endl;
  }
}

int main() {
  std::signal(SIGINT, signal_handle);
  std::signal(SIGTERM, signal_handle);

  while (1) {
  }
}