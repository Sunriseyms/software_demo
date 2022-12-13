#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <memory>
using namespace std;

class Demo {
public:
  int operator()(int i, int j) const noexcept {
    std::cout << "i*i:" << i * i << std::endl;
    return i * i;
  }
  void print(int i) {
    std::cout << "print i:" << i << std::endl;
  } // void print(Demo* d, int i);

  static void print1() {
    std::cout <<"print1" << std::endl;
  } // Demo::print1()
};

int main() {
  list<int> lst = {1, 2, 3, 4};
  list<int> lst2, lst3; // empty lists
  // after copy completes, lst2 contains 4 3 2 1
  copy(lst.cbegin(), lst.cend(), front_inserter(lst2));
  cout << "lst2:";
  for (auto &&elem : lst2) {
    cout << elem << " ";
  }
  cout << endl;
  // after copy completers, lst3 contains 1 2 3 4
  copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
  cout << "lst3:";
  for (auto &&elem : lst3) {
    cout << elem << " ";
  }
  cout << endl;

  // std::cout << std::hash<string>()("test") << std::endl;

  // std::cout << Demo()(5, 1) << std::endl; // Demo tmp = Demo();;
  // tmp.operator(5);
  Demo d;
  // std::cout << d(5,1) << std::endl; // d.operator(int i);

  auto f = std::bind(&Demo::print, &d, std::placeholders::_1);
  // f(1) ==> f(d, 1);
  std::for_each(lst.begin(), lst.end(), f); // f(int i);

  std::map<string, int> word_count;
  ++word_count["a"]; // 1. word_count[word]; ==> T tmp; word_count->insert(word,
                     // tmp); // ++value

  std::list<std::string> num{"ab", "abc"};
  // TODO: question 1
  auto count = std::count(num.cbegin(), num.cend(), "abc");
  std::cout << "count result: " << count << std::endl;

  std::multiset<int> s;
  Demo::print1();

  std::vector<int> v;
  v.push_back(1);
  v.emplace_back(1);


  return 0;
}
