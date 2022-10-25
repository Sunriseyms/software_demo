#ifndef LOG_FILTER_LOGGER_H_
#define LOG_FILTER_LOGGER_H_
#include <atomic>
#include <string>
#include <tuple>
#include <unordered_map>
namespace px {
namespace logger {
using CfgData = std::tuple<int, bool, bool, bool>;
class Cfg {
 public:
  Cfg();
  const CfgData& GetCfgData(const std::string& module_name);

 private:
  CfgData global_cfg_;
  std::unordered_map<std::string, CfgData> module_cfgs_;
};

extern Cfg global_cfgs;

class Logger {
 public:
  static void LOG(const std::string& module_name = "");
};
}  // namespace logger
}  // namespace px

#endif  // LOG_FILTER_LOGGER_H_
