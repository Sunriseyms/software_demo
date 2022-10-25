#ifndef DLOPEN_DEMO_PEOPLE_H_
#define DLOPEN_DEMO_PEOPLE_H_
#include <string>
#include <utility>
#include <memory>
#include <iostream>
class Person {
 public:
    Person() {
        std::cout << "Person constructor\n";
    }
    virtual std::string GetName() const = 0;
    void SetName(const std::string& name) {
        name_ = std::move(name);
    }
    virtual ~Person() {
        std::cout << "Person destructor\n";
    }
 protected:
    std::string name_;
};

//typedef std::shared_ptr<Person> Create_t();
using Create_t = std::shared_ptr<Person>(*)();
#endif  // DLOPEN_DEMO_PEOPLE_H_
