#include <iostream>
#include <mutex>
#include <thread>


class spinlock_mutex {
    std::atomic_flag flag;
 public:
    spinlock_mutex(): flag(ATOMIC_FLAG_INIT) {}
    void lock() { while (flag.test_and_set(std::memory_order_acquire)); }
    void unlock() { flag.clear(std::memory_order_release); }
};

//std::mutex m;
//spinlock_mutex m;
std::timed_mutex m;

void func1() {
    m.lock();
    //m.try_lock_for(std::chrono::milliseconds(100000));
    while (true) {}
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    std::thread t1(func1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //m.lock();
    m.try_lock_for(std::chrono::milliseconds(100000));
    t1.join();
    //m.lock();
    //while (m.try_lock()) {
        //i++;
    //    m.unlock();
    //}

    return 0;
}
