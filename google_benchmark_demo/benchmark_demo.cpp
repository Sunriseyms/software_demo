
#include <array>
#include <chrono>
#include <iostream>
#include <memory>

using TimePoint = std::chrono::high_resolution_clock::time_point;
class Timer {
 public:
  Timer() { start_time_point_ = std::chrono::high_resolution_clock::now(); }
  ~Timer() { Stop(); }
  void Stop() {
    TimePoint end_time_point = std::chrono::high_resolution_clock::now();

    auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(
                     start_time_point_)
                     .time_since_epoch()
                     .count();
    auto end =
        std::chrono::time_point_cast<std::chrono::nanoseconds>(end_time_point)
            .time_since_epoch()
            .count();
    auto duration = end - start;

    std::cout << duration << "ns(" << duration * 0.001 << "us)" << std::endl;
  }

 private:
  TimePoint start_time_point_;
};

struct Point {
  float x{0};
  float y{0};
};

int main() {
  std::cout << "shared_ptr make_shared:";
  {
    std::array<std::shared_ptr<Point>, 1000> ptr_array;
    Timer timer;
    for (int i = 0; i < ptr_array.size(); ++i) {
      ptr_array[i] = std::make_shared<Point>();
    }
  }

  std::cout << "shared_ptr new:";
  {
    std::array<std::shared_ptr<Point>, 1000> ptr_array;
    Timer timer;
    for (int i = 0; i < ptr_array.size(); ++i) {
      ptr_array[i] = std::shared_ptr<Point>(new Point());
    }
  }

  std::cout << "unique_ptr make_shared:";
  {
    std::array<std::unique_ptr<Point>, 1000> ptr_array;
    Timer timer;
    for (int i = 0; i < ptr_array.size(); ++i) {
      ptr_array[i] = std::make_unique<Point>();
    }
  }

  std::cout << "pecise test:";
  {
    Timer timer;
    int i = 0;
    i++;
    i++;
  }

  return 0;
}
