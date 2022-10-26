#include <iostream>

#include "yaml_parse.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    return -1;
  }
  YAML::Node node;
  bool ret = yaml_include_demo::ParseYaml(argv[1], node);
  if (ret) {
    std::cout << "Load yaml file success\n";
    std::cout << "===================yaml output begin========================\n";
    for(auto&& n : node) {
        std::cout << "module_name:" << n.first.as<std::string>() << std::endl; 
        for(auto&& n1 : n.second) {
            std::cout << "key:" << n1.first.as<std::string>() << " value:" << n1.second << std::endl;
        }
    }
    std::cout << "===================yaml output end========================\n";
    return 0;
  } else {
    std::cerr << "Load yaml file failed. file path is " << argv[1] << std::endl;
    return -1;
  }
}