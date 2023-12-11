#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <time.h>
#include <sys/time.h>

std::condition_variable cv;
std::mutex cvMutex;

void waitForEvent() {
  std::unique_lock<std::mutex> lock(cvMutex);
  std::cout << "Waiting for event..." << std::endl;
  std::system("ll");
  // 等待一定时间，或直到被通知
  if (cv.wait_for(lock, std::chrono::seconds(10))) {
    std::cout << "Event signaled!" << std::endl;
  } else {
    std::cout << "Timeout occurred!" << std::endl;
  }
}



void change_time_thread() {
    // 等待足够的时间让 wait_thread 开始执行 wait_for
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 模拟更改系统时间
    std::cout << "Simulating a forward time jump of 1 hour..." << std::endl;
    std::system("sudo date --set='+1 hour'");
    
    // 在这里可以插入实际更改系统时间的代码，例如使用 system 调用
    // std::system("sudo date --set='+1 hour'"); // 需要具有 root 权限

    // 注意：实际的系统时间修改可能需要管理员权限，并且在真实的系统上运行可能不安全。
    // 在生产环境中不建议这样做。

    // 模拟代码结束
}

int main() {
  std::thread waiter(waitForEvent);
  std::thread time_changer(change_time_thread);

  // 等待线程完成
  if(waiter.joinable()) {
    waiter.join();
  }
  if(time_changer.joinable()) {
    time_changer.join();
  }

  return 0;
}