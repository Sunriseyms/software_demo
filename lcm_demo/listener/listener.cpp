#include <lcm/lcm.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include <thread>
#include "exlcm/example_t.hpp"

class Handler {
 public:
  ~Handler() {}
  void handleMessage(const lcm::ReceiveBuffer* rbuf,
                     const std::string& chan,
                     const exlcm::example_t* msg) {
    int i;
    printf("name=%s index=%lld\n", msg->name.c_str(), (long long)msg->index);
  }
  /*
  void handleMessage2(const lcm::ReceiveBuffer* rbuf,
                      const std::string& chan,
                      const exlcm::example_t* msg) {
    int i;

    printf("Received message on channel \"%s\":\n", chan.c_str());
    printf("  timestamp   = %lld\n", (long long)msg->timestamp);
    printf("  position    = (%f, %f, %f)\n", msg->position[0], msg->position[1],
           msg->position[2]);
    printf("  orientation = (%f, %f, %f, %f)\n", msg->orientation[0],
           msg->orientation[1], msg->orientation[2], msg->orientation[3]);
    printf("  ranges:");
    for (i = 0; i < msg->num_ranges; i++) printf(" %d", msg->ranges[i]);
    printf("\n");
    printf("  name        = '%s'\n", msg->name.c_str());
    printf("  enabled     = %d\n", msg->enabled);

  }
  */
};

int main(int argc, char** argv) {
  lcm::LCM lcm;

  if (!lcm.good()) return 1;

  Handler handlerObject;
  lcm::Subscription* sub =
      lcm.subscribe("EXAMPLE", &Handler::handleMessage, &handlerObject);
  std::cout << "sub queue size=" << sub->getQueueSize() << std::endl;
  sub->setQueueCapacity(2000);
  std::cout << "sub queue size=" << sub->getQueueSize() << std::endl;

  // lcm::LCM lcm1;
  // lcm.subscribe("EXAMPLE", &Handler::handleMessage, &handlerObject);

  while (true) {
    // Do nothing
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    int i;
    std::cin >> i;
    lcm.handle();
    std::cout << "sub queue size=" << sub->getQueueSize() << std::endl;
  }

  return 0;
}
