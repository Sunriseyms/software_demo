#include <dlfcn.h>
#include <iostream>
#include "person.h"

int Hello() { std::cout << "Hello World\n"; }

int main(int argc, char** argv) {
  Hello();
  if (argc != 3) {
    std::cout << "usage: ./dlopen_demo so_path class_so_path\n";
    return -1;
  }

  std::string so_path = argv[1];

  void* handle = nullptr;
  handle = dlopen(so_path.c_str(), RTLD_LAZY | RTLD_GLOBAL);

  if (!handle) {
    std::cout << dlerror() << std::endl;
    return -1;
  }

  dlerror();

  int (*add_method)(int, int);
  add_method = (int (*)(int, int))dlsym(handle, "Add");

  char* error = dlerror();
  if (error != nullptr) {
    std::cout << error << std::endl;
    return -1;
  }

  int result = add_method(1, 2);
  std::cout << "Add(1, 2) from " << so_path << " is " << result << std::endl;
  // dlclose(handle);

  std::string class_so_path = argv[2];
  void* handle1 = dlopen(class_so_path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
  if (!handle1) {
    std::cout << dlerror() << std::endl;
    return -1;
  }

  dlerror();

  Create_t create = reinterpret_cast<Create_t>(dlsym(handle1, "Create"));
  error = dlerror();
  if (error != nullptr) {
    std::cout << error << std::endl;
    return -1;
  }
  //{
  std::shared_ptr<Person> person = create();
  person->SetName("Tom");
  std::cout << "person name: " << person->GetName() << std::endl;
  //}

  std::cout << "main end\n";
  while (true) {}

  return 0;
}
