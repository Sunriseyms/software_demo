#ifndef TEMPLATE_DEMO_LOG_H_
#define TEMPLATE_DEMO_LOG_H_
#include <string>
#include <queue>
#include <functional>
#include "ros_log.h"
#include "native_log.h"

extern std::queue<std::function<void()>> queue_;

class RosType{};
class NativeType{};

template <class T, class V>
std::function<void()> CreateFunc(const std::string& topic, const T& msg, V v);

inline RosType CreateRosType() {
    return RosType();
}

inline NativeType CreateNativeType() {
    return NativeType();
}

#ifdef ROS_DEPEND
#define CreateType CreateRosType()
#else
#define CreateType CreateNativeType()
#endif

template <class T>
void LogData(const std::string& topic, const T& msg) {
    auto func = CreateFunc(topic, msg, CreateType);
    queue_.push(func);

    std::cout << "queue size: " << queue_.size() << std::endl;
    queue_.front()();
}

#endif  // TEMPLATE_DEMO_LOG_H_
