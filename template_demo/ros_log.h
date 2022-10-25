#ifndef TEMPLATE_DEMO_ROS_LOG_H_
#define TEMPLATE_DEMO_ROS_LOG_H_

#include "log.h"
#include <string>
#include <queue>
#include <functional>

class RosType{};
template <class T>
inline std::function<void()> CreateFunc(const std::string& topic, const T& msg, RosType) {
    auto func = [&](){
        std::cout << "ros record: " << topic << std::endl;
    };
    return func;
}

#endif  // TEMPLATE_DEMO_ROS_LOG_H_
