#ifndef TEMPLATE_DEMO_NATIVE_LOG_H_
#define TEMPLATE_DEMO_NATIVE_LOG_H_

#include "log.h"
#include <string>
#include <queue>
#include <functional>

class NativeType{};
template <class T>
inline std::function<void()> CreateFunc(const std::string& topic, const T& msg, NativeType) {
    auto func = [&](){
        std::cout << "native record: " << topic << std::endl;
    };
    return func;
}

#endif  // TEMPLATE_DEMO_NATIVE_LOG_H_
