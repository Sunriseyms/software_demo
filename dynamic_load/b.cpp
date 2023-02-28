#include "common.h"

extern "C" void f2() {
    std::cout << "b so" <<std::endl;
}
 
class Test {
    public:
        Test() {
            std::cout << "Test construct" << std::endl;
        }
};

static Test t;