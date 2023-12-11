#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char** argv) {
  int epollfd = epoll_create1(0);
  if (epollfd == -1) {
    perror("epoll create failed");
    return -1;
  }
  int timerfd;
 {

  int timerfd1 = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);
  if (timerfd1 == -1) {
    perror("timerfd create failed");
    return -1;
  }
    timerfd = timerfd1;
 }

  struct itimerspec new_value;
  new_value.it_value.tv_sec = 5;
  new_value.it_value.tv_nsec = 0;
  new_value.it_interval.tv_sec = 5;
  new_value.it_interval.tv_nsec = 500000;

  int result = timerfd_settime(timerfd, 0, &new_value, nullptr);
  if (result == -1) {
    perror("timerfd settime failed");
    return -1;
  }

  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = timerfd;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, timerfd, &ev) == -1) {
    perror("epoll ctl add failed");
    return -1;
  }

  while (true) {
    struct epoll_event events[10];
    int nfds = epoll_wait(epollfd, events, 10, 1000);
    if (nfds == -1) {
      perror("epoll wait");
      continue;
    }

    for (int n = 0; n < nfds; ++n) {
      //if (events[n].data.fd == timerfd) {
        uint64_t expirations;
        ssize_t s = read(timerfd, &expirations, sizeof(uint64_t));
        if (s != sizeof(uint64_t)) {
          perror("read failed");
          return -1;
        }
        auto now = std::chrono::system_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(
                         now.time_since_epoch())
                         .count()
                  << "timefd event receive" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      //}
    }
  }

  return 0;
}