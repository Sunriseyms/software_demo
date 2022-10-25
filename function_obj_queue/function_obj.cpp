#include <functional>
#include <iostream>
#include <memory>
#include <queue>

std::queue<std::function<void(int)>> q;

template <class T>
class Person {
 public:
  T GetId() { return val_; }
  int Log(const T& t) { val_ = t; }
  int Log(const T&& t) { val_ = t; }
  ~Person() { std::cout << "~Person()" << std::endl; }
  void operator()(int i) const { std::cout << i << " " << val_ << '\n'; }

 private:
  int id_;
  T val_;
};

template <class T>
void Log(const T& t, int size) {
  std::shared_ptr<Person<T>> p = std::make_shared<Person<T>>();
  // Person<T> p;

  q.push([p](int val) -> void { (*p)(val); });
  // q.push(p);
}

class Demo {
 public:
  template <class T>
  void Print(const T& t) {
    std::cout << t << std::endl;
  }
};

class RecordBaseSink {
 public:
  template <class T>
  void Record(T t, const std::string topic){};
};

class RecordRosbagSink : public RecordBaseSink {
 public:
  RecordRosbagSink() : bag_(1) {
    std::cout << "RecordRosbagSink construct" << std::endl;
  }
  template <class T>
  void Record(T t, const std::string topic) {
    std::cout << "bag_:" << bag_ << "T: " << t << " topic: " << topic
              << std::endl;
  };

 private:
  int bag_;
};

int main() {
  Log<int>(1, 10);
  std::function<void(int)> fun = q.front();
  fun(100);

  Demo d;
  d.Print(1);

  std::shared_ptr<RecordBaseSink> sink = std::make_shared<RecordRosbagSink>();
  sink->Record(1, "hello");

  return 0;
}
