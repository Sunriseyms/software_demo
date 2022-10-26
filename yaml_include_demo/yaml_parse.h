#include <yaml-cpp/yaml.h>
#include <string>

namespace yaml_include_demo {
    bool ParseYaml(const std::string& file_path, YAML::Node& out_node);
}