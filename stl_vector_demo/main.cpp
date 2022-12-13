#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;
int main() {
    vector<double> a{1.0,2.0};
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