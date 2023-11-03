#include <sys/syscall.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

std::string mem_sys_path_="/sys/fs/cgroup/memory";

bool is_mem_enable() {
  if (mem_sys_path_.empty()) {
    return false;
  }

  // check /sys/fs/cgroup/memory/test_group/memory.limit_in_bytes can write
  std::string test_group("test_group");
  std::string test_group_dir = mem_sys_path_ + "/" + test_group;
  if (mkdir(test_group_dir.c_str(), 0755) == -1) {
    std::cout << "errno:" << errno << " errstr:" << strerror(errno)
              << std::endl;
    return false;
  }

  std::string test_group_memory_limit =
      test_group_dir + "/memory.limit_in_bytes";
  std::string limit_bytes = "1024";

  // write limit_bytes to
  // /sys/fs/cgroup/memory/test_group/memory.limit_in_bytes
  FILE *file = fopen(test_group_memory_limit.c_str(), "w");
  if (file == nullptr) {
    std::cout << "errno:" << errno << " errstr:" << strerror(errno)
              << std::endl;
    rmdir(test_group_dir.c_str());
    return false;
  }
  (void)fprintf(file, "%s" ,limit_bytes.c_str());
  (void)fclose(file);

  // read /sys/fs/cgroup/memory/test_group/memory.limit_in_bytes
  std::ifstream read_file(test_group_memory_limit.c_str());
  if (!read_file) {
    std::cout << "errno:" << errno << " errstr:" << strerror(errno)
              << std::endl;
    rmdir(test_group_dir.c_str());
    return false;
  }
  std::string acct_limit_bytes;
  (void)std::getline(read_file, acct_limit_bytes);
  if (limit_bytes == acct_limit_bytes) {
    rmdir(test_group_dir.c_str());
    return true;
  }
  std::cout << "not support" << std::endl;
  rmdir(test_group_dir.c_str());
  return false;
}

int main(int args, char** argv) {
  /*
  int thread_count = 0;
  try {
    thread_count = std::stoi(argv[1]);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  std::vector<std::thread> threads(thread_count);
  for (auto&& t : threads) {
    t = std::thread([]() {
      std::cout << "Current thread ID is: " << std::this_thread::get_id() <<
  std::endl; std::cout << "system call tid:" << syscall(SYS_gettid) <<
  std::endl; int i = 0; int sum =0; while (true) { i++; sum += i;
        //std::this_thread::sleep_for(std::chrono::microseconds(1));
      }
    });
  }
  */
  /*
          int i = 0;
        int sum =0;
        while (true) {
          i++;
          sum += i;
          std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
  */
  /*
    for (auto&& t : threads) {
      if (t.joinable()) {
        t.join();
      }
    }
    */

  std::ifstream file("/proc/mounts");
  std::string line;
  bool cgroup_enabled = false;
  std::string path;

  while (std::getline(file, line)) {
    if ((line.find("cgroup") != std::string::npos) &&
        (line.find("memory") != std::string::npos)) {
      std::cout << "line:" << line << std::endl;
      std::vector<std::string> tokens;
      std::istringstream token_stream(line);
      std::string token;
      while(std::getline(token_stream, token, ' ')) {
        tokens.emplace_back(token);
      }
      if(tokens.size() > 1) {
        path = tokens[1];
      }
      std::cout << "path:" << path << std::endl;

      cgroup_enabled = true;
      break;
    }
  }


  std::cout << "is_mem_enable: " << is_mem_enable() << std::endl;;

  return 0;
}