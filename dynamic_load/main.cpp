#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  {
    void *handle1;
    void *handle2;
    char *error;
    // load library
    std::cout << "load library a begin" << std::endl;
    handle1 = dlopen(argv[1], RTLD_LAZY);
    if (!handle1) {
      std::cout << "dlopen failed: " << dlerror() << std::endl;
      return -1;
    }

    auto f1 = (void (*)())dlsym(handle1, "f1");
    error = dlerror();
    if (error != nullptr) {
      std::cout << "dlsym failed:" << error << std::endl;
      return -1;
    }
    f1();
    dlclose(handle1);
    std::cout << "load library a end" << std::endl;

    std::cout << "load library b begin" << std::endl;
    handle2 = dlopen(argv[2], RTLD_LAZY);
    if (!handle2) {
      std::cout << "dlopen failed: " << dlerror() << std::endl;
      return -1;
    }

    auto f2 = (void (*)())dlsym(handle2, "f2");
    error = dlerror();
    if (error != nullptr) {
      std::cout << "dlsym failed:" << error << std::endl;
      return -1;
    }
    f2();
    dlclose(handle2);
    std::cout << "load library b end" << std::endl;
  }
  std::cout << "main end" << std::endl;

  return 0;
}