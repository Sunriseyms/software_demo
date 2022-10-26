#include "yaml_parse.h"
#include <iostream>

bool yaml_include_demo::ParseYaml(const std::string &file_path,
                                  YAML::Node &out_node) {
  try {
    YAML::Node nodes = YAML::LoadFile(file_path);
    std::cout << "Type:" << nodes.Type() << std::endl;
    for (auto &&node : nodes) {
      std::cout << "key:" << node.first.as<std::string>() << std::endl;
      std::cout << "first Type:" << node.first.Type() << std::endl;
      std::cout << "secode Type:" << node.second.Type() << std::endl;
      if (node.second.IsMap()) {
        out_node[node.first] = node.second;
      }

      if (node.first.as<std::string>().compare("include") == 0) {
        if (!node.second.IsSequence()) {
          std::cout << node.first.as<std::string>() << " is not sequence"
                    << std::endl;
          return false;
        }
        for (auto &&file_path : node.second) {
          if (!ParseYaml(file_path.as<std::string>(), out_node)) {
            return false;
          }
        }
      }
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << " file_path:" << file_path << '\n';
    return false;
  }
  return true;
}