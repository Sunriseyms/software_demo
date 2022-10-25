#include <iostream>
#include <memory>
#include <utility>
#include "../person.h"
#include "static_lib/a.h"

class Student : public Person {
 public:
  Student() { std::cout << "Student constructor\n"; }
  std::string GetName() const override {
    auto& demo = DemoInstance();
    demo.i++;
    std::cout << "Student demo:" << demo.i << " address:" << &demo << std::endl;
    return name_;
  }
  virtual ~Student() { std::cout << "Student destructor\n"; }
};

extern "C" std::shared_ptr<Person> Create() {
  return std::make_shared<Student>();
}
