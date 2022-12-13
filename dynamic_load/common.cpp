#include "common.h"

Data &Data::GetInstance() {
  static Data data;
  std::cout << "Data GetInstance address:" << &data << std::endl;
  return data;
}

Data::Data() { std::cout << "Data construct" << std::endl; }
Data::~Data() { std::cout << "Data destruct" << std::endl; }