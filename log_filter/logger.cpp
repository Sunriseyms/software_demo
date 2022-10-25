#include "logger.h"
#include <linux/limits.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

namespace px {
namespace logger {
Cfg::Cfg() {
  std::string cfg_file;
  char current_path[PATH_MAX]{0};
  if (getcwd(current_path, sizeof(current_path)) != nullptr) {
    cfg_file.append(current_path);
    cfg_file.append("/px_log.cfg");
  }

  std::ifstream ifile(cfg_file, std::ios::in | std::ios::binary);
  if (!ifile.is_open()) {
    global_cfg_ = std::make_tuple(0, true, true, true);
    return;
  }

  std::string line;
  CfgData cfg_data = std::make_tuple(0, true, true, true);
  global_cfg_ = cfg_data;

  while (std::getline(ifile, line)) {
    std::cout << line << std::endl;
    if (line.empty() || line.front() == '#') { continue; }
    auto pos = line.find_first_of(':');
    if (pos == std::string::npos) { continue; }
    std::string module_name = line.substr(0, pos);
    module_name.erase(0, module_name.find_first_not_of("\r\t\n "));
    module_name.erase(module_name.find_last_not_of("\r\t\n ") + 1);

    auto pos1 = line.find_first_of('[', pos);
    auto pos2 = line.find_last_of(']');
    std::string value_str = line.substr(pos1, pos2);
    if (value_str.empty()) { continue; }
    std::cout << value_str << std::endl;

    char delem;
    int value;
    std::istringstream in(value_str);
    in >> delem;
    in >> std::get<0>(cfg_data) >> delem;
    in >> std::get<1>(cfg_data) >> delem;
    in >> std::get<2>(cfg_data) >> delem;
    in >> std::get<3>(cfg_data) >> delem;

    if (module_name == "global") {
      global_cfg_ = cfg_data;
      continue;
    } else {
      std::cout << "insert module cfgs:" << module_name << " "
                << std::get<0>(cfg_data) << std::get<1>(cfg_data)
                << std::get<2>(cfg_data) << std::get<3>(cfg_data) << std::endl;
      module_cfgs_.insert(std::make_pair(module_name, cfg_data));
    }
  }
}

const CfgData& Cfg::GetCfgData(const std::string& name) {
  if (module_cfgs_.count(name) == 0) {
    return global_cfg_;
  } else {
    return module_cfgs_[name];
  }
}

Cfg global_cfgs;

void Logger::LOG(const std::string& module_name) {
  const CfgData& CfgData = global_cfgs.GetCfgData(module_name);
  std::cout << std::get<0>(CfgData) << std::get<1>(CfgData)
            << std::get<2>(CfgData) << std::get<3>(CfgData) << std::endl;
}

}  // namespace logger
}  // namespace px
