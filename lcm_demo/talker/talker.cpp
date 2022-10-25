#include <chrono>
#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include <thread>

#include "exlcm/example_t.hpp"

constexpr int LCM_SIZE = 1024;

int main(int argc, char** argv) {
  lcm::LCM lcm;
  if (!lcm.good()) return 1;

  /*
  lcm::LCM lcm1;
  lcm::LCM lcm2;
  lcm::LCM lcm3;
  std::vector<lcm::LCM> lcm_vec;
  lcm_vec.resize(LCM_SIZE);
  */

  /*
  for (int i = 0; i < LCM_SIZE; ++i) {
    lcm_vec.emplace_back(lcm::LCM());
    std::cout << "create " << i << " lcm" << std::endl;
  }*/
  /*
  exlcm::example_t my_data;
  my_data.timestamp = 0;
  my_data.index = 0;

  my_data.position[0] = 1;
  my_data.position[1] = 2;
  my_data.position[2] = 3;

  my_data.orientation[0] = 1;
  my_data.orientation[1] = 0;
  my_data.orientation[2] = 0;
  my_data.orientation[3] = 0;

  my_data.num_ranges = 15;
  my_data.ranges.resize(my_data.num_ranges);
  for (int i = 0; i < my_data.num_ranges; i++) my_data.ranges[i] = i;

  my_data.name = "example string";
  my_data.enabled = true;
  std::thread t1 = std::thread([&]() {IPPROTO_IP
      my_data1.index++;
      my_data1.name = "thread 1";
      lcm.publish("EXAMPLE", &my_data1);
    }
  });

  while (1) {
    my_data.name = "main thread";
    my_data.index++;
    lcm.publish("EXAMPLE", &my_data);
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }*/
  exlcm::example_t my_data;
  my_data.timestamp = 0;
  my_data.num_ranges = 15;
  my_data.ranges.resize(my_data.num_ranges);

  while (true) {
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
      my_data.index++;
      lcm.publish("EXAMPLE", &my_data);
    }
  }
  return 0;
}
