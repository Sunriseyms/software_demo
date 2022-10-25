#ifndef TEMPLATE_DEMO_DEMO_H_
#define TEMPLATE_DEMO_DEMO_H_
#include <iostream>
#include <memory>
#include <vector>

class Demo {
 public:
  Demo(int id) : id_(id) { std::cout << "Demo construct\n"; }
  Demo(const Demo& d) {
    this->id_ = d.id_;
    std::cout << "Demo copy construct\n";
  }
  ~Demo() { std::cout << "Demo destruct\n"; }

  int id_{0};
};

struct Data {
  std::vector<Demo> data_;
};

class DataWrap {
 public:
  DataWrap(const Data& msg) : msg_(msg) {}
  DataWrap(Data&& msg) {
    std::cout << "&&\n";
    msg_.data_ = std::move(msg.data_);
  }
  Data msg_;
};

void Log(const Data& t) {
  std::cout << "log const& begin\n";
  {
    std::shared_ptr<DataWrap> data_ptr = std::make_shared<DataWrap>(t);
    std::cout << "size:" << data_ptr->msg_.data_.size() << "\n";
    for (auto& num : data_ptr->msg_.data_) { std::cout << num.id_ << "\n"; }
  }
  std::cout << "log const& end\n";
}

void Log(Data&& t) {
  std::cout << "log && begin\n";
  {
    std::shared_ptr<DataWrap> data_ptr =
        std::make_shared<DataWrap>(std::forward<Data>(t));
  }
  std::cout << "log && end\n";
}

#endif  // TEMPLATE_DEMO_DEMO_H_
