#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

void write_file(const std::string& filename, const std::string& value) {
  std::ofstream ofs(filename);
  if (!ofs) throw std::runtime_error("Failed to open " + filename);
  ofs << value;
  if (ofs.fail()) throw std::runtime_error("Failed to write to " + filename);
}

int main(int argc, char** argv) {
  int pid = std::stoi(argv[1]);
  std::cout << "pid:" << pid << std::endl;

  // 创建一个新的 cgroup
  std::string cgroup_path = "/sys/fs/cgroup/memory/test_mem_group2";
  mkdir(cgroup_path.c_str(), 0755);

  // 设置 memory.limit_in_bytes 到 200M
  write_file(cgroup_path + "/memory.limit_in_bytes", "204857600");
  write_file(cgroup_path + "/cgroup.procs", std::to_string(pid));

  // 创建 eventfd 和 epoll 实例
  int efd = eventfd(0, EFD_CLOEXEC);
  if (efd == -1) throw std::runtime_error("Failed to create eventfd");

  int epfd = epoll_create1(0);
  if (epfd == -1) throw std::runtime_error("Failed to create epoll instance");

  // 添加 eventfd 到 epoll 实例
  epoll_event ev = {};
  ev.events = EPOLLIN;
  ev.data.fd = efd;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, efd, &ev) == -1)
    throw std::runtime_error("Failed to add eventfd to epoll");

  // 打开 memory.usage_in_bytes 文件
  int cgfd = open((cgroup_path + "/memory.usage_in_bytes").c_str(), O_RDONLY);
  if (cgfd == -1) throw std::runtime_error("Failed to open cgroup file");

  // 注册 cgroup 事件
  double thr = 188743680.00000;
  write_file(cgroup_path + "/cgroup.event_control",
             std::to_string(efd) + " " + std::to_string(cgfd) + " " + std::to_string(long(thr)));

  // 等待事件通知
  while (true) {
    epoll_event events[10];
    int nfds = epoll_wait(epfd, events, 10, 1000);
    if (nfds == -1) throw std::runtime_error("Failed in epoll_wait");

    for (int n = 0; n < nfds; ++n) {
      if (events[n].data.fd == efd) {
        uint64_t count;
        read(efd, &count, sizeof(count));
        std::cout << "Received cgroup event, count: " << count << "\n";
      }
    }
  }

  // 清理
  close(efd);
  close(cgfd);
  close(epfd);
  rmdir(cgroup_path.c_str());

  return 0;
}