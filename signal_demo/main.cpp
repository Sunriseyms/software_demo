#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>
#include <vector>
#include <signal.h>
#include <unistd.h>

void signal_handle1(int sig) {
  std::cout << "signal_handle1 sig:" << sig <<  " thread id:" << std::this_thread::get_id()<< std::endl;
}

void signal_handle2(int sig) {
  std::cout << "signal_handle2 sig:" << sig <<  " thread id:" << std::this_thread::get_id()<< std::endl;

  int j = 0;
  while (j < 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "signal_handle2 " << j++ << std::endl;
  }
  char i;
  std::cout << "please enter any key to exit signal_handle2" << std::endl;
  std::cin >> i;
  //std::cout << "exit signal_handle2" << std::endl;
}

void signal_handle3(int sig) {
  std::cout << "signal_handle3 sig:" << sig <<  " thread id:" << std::this_thread::get_id()<< std::endl;
  int j = 0;
  while (j < 100) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "signal_handle3 " << j++ << std::endl;
  }

  std::cout << "exit signal_handle3" << std::endl;
}

enum class HandleSignalStrategy {
  kSignal = 0,
  kSigaction = 1,
  kSigWaitInfo = 2
};

int main(int argc, char** argv) {
  std::cout << "main thread id:" << std::this_thread::get_id() << std::endl;

  int thread_num = 1;
  if (argc == 2) {
    thread_num = std::stoi(argv[1]);
  }

  HandleSignalStrategy handle_signal_strategy = HandleSignalStrategy::kSignal;

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout << "signal SIGINT with signal_handle1" << std::endl;
  std::signal(SIGINT, signal_handle1);
  char i;
  std::cout << "please enter any key to signal SIGINT with signal_handle2"
            << std::endl;
  std::cin >> i;
  std::signal(SIGINT, signal_handle2);
  std::cout << "signal SIGTERM with signal_handle3" << std::endl;
  std::signal(SIGTERM, signal_handle3);

  std::vector<std::thread> child_threads;
  int child_thread_num = thread_num - 1;
  child_threads.reserve(child_thread_num);
  for (int i = 0; i < child_thread_num; i++) {
    child_threads.emplace_back(std::thread([i]() {
      std::cout << "child thread id:" << std::this_thread::get_id()
                << std::endl;
      while (1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }));
  }

  while (1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}