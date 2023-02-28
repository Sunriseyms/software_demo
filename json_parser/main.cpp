#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <algorithm>
int main(int argc, char* argv[]) {
  Json::Value root;
  std::ifstream ifs;
  ifs.open(argv[1]);

  Json::CharReaderBuilder builder;
  builder["collectComments"] = true;
  JSONCPP_STRING errs;
  if (!parseFromStream(builder, ifs, &root, &errs)) {
    std::cout << errs << std::endl;
    return EXIT_FAILURE;
  }
  //std::cout << root << std::endl;
  
  std::cout << root.getMemberNames().size() << std::endl;
  auto member_names = root.getMemberNames(); 
  std::for_each(member_names.begin(), member_names.end(), [](auto && member_name){
    std::cout << "memberName:" << member_name << std::endl;
  });

  std::cout << root["key"] << std::endl;
  for(auto&& obj : root["value"]["object[]"]) {
    std::cout << "xxxx:" << std::endl;
    std::cout << obj["key"] << std::endl;
  }
  std::cout << root["value"]["object[]"][0] << std::endl;
  return EXIT_SUCCESS;
}