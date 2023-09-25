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
  std::vector<std::string> data;
};

using DataPtr = std::shared_ptr<Data>;
class ManifestData {
 public:
  ManifestData() {
    current_ptr = std::make_shared<Data>();
    next_ptr = std::make_shared<Data>();
  }

  DataPtr get_data() { return current_ptr; }

  bool init(const Data& data) {
    current_ptr->data = data.data;
    return true;
  }

  bool reload(const Data& data) {
    next_ptr->data = data.data;
    return true;
  }

  void swap_data() { std::swap(next_ptr, current_ptr); }

 private:
  DataPtr current_ptr;
  DataPtr next_ptr;
};

int main() {
  
  ManifestData manifest_data;
  Data d1;
  d1.data = std::vector<std::string>(10,std::string(10, 0));
  manifest_data.init(d1);
  std::thread reload_thread = std::thread([&manifest_data](){
      int i = 2;
      for(;;) {
          Data d2;
          d2.data = std::vector<std::string>(i%20,std::string(i%20, i));
          manifest_data.reload(d2);
          i++;
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
  });

  std::thread read_thread = std::thread([&manifest_data](){
      for(;;) {
          std::cout << "data:";
          for(auto&& elem : manifest_data.get_data()->data) {
              std::cout << elem << " ";
          }
          std::cout << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
  });

  std::thread swap_thread = std::thread([&manifest_data](){
      for(;;) {
         manifest_data.swap_data();
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
  });

  reload_thread.join();
  read_thread.join();
  swap_thread.join();
  

  /*
  DataPtr test_data_ptr = std::make_shared<Data>();
  std::mutex mtx;
  std::thread write_thread = std::thread([&]() {
    int i = 1;
    for (;;) {
      {
        std::lock_guard<std::mutex> lck(mtx);
        test_data_ptr->data =
            std::vector<std::string>(i % 20, std::string(i % 20, i));
      }
      i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  });

  std::thread read_thread = std::thread([&]() {
    for (;;) {
      std::cout << "data:";
      {
        std::lock_guard<std::mutex> lck(mtx);
        for (auto&& elem : test_data_ptr->data) {
          std::cout << elem << " ";
        }
      }
      std::cout << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  });
  write_thread.join();
  read_thread.join();
  */

  return 0;
}