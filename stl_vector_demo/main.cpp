#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;
int main() {
    vector<double> a{1.0,2.0};
    std::cout << "00 capacity:" << a.capacity() << std::endl;
    //a.clear(); // for(auto it=a.begin(), it!=a.end(); ++it) { 调用元素的析构函数，再将_M_finish设置为_M_start }
    //a.erase(a.begin()); // std::memmove(a.begin(), a.begin()+1, a.end()-a.begin()-1)
    std::cout << "01 capacity:" << a.capacity() << std::endl;
    std::cout << "size:" << a.size() << std::endl;
    std::cout << "t:" << a[0] << std::endl;
    std::cout << "t:" << a[1] << std::endl;
    std::cout << "0 capacity:" << a.capacity() << std::endl;
    a.push_back(3.0);
    std::cout << "1 capacity:" << a.capacity() << std::endl;
    a.resize(5);
    std::cout << "2 capacity:" << a.capacity() << std::endl;
    vector<double> b;
    b.resize(5);
    std::cout << "3 capacity:" << b.capacity() << std::endl;
    return 0;
}