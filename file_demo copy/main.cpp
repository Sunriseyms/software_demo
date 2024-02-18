/*
 * @Author: your name
 * @Date: 2021-10-19 09:40:53
 * @LastEditTime: 2021-11-25 18:41:50
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置:
 * https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /demo/file_demo/main.cpp
 */
#include <unistd.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "file_demo.h"

int main() {
  // BaseSink* p = new RotatingFileSink(filename, 3, 100);
  /*
  std::unique_ptr<BaseSink> p = SinkFactory::CreateSink();

  for (int i = 0; i < 30; i++) {
    std::string buf = "hellooo";
    buf.append(std::to_string(i) + "\n");
    p->Log(buf.c_str(), buf.size());
  }*/

  std::string s = "AA 00 00 05 00 00 00 01 1D E8 03 00 00 00 00 00";
  std::string s1 = "=1|1000|1||";
  std::vector<std::string> v;
  for (int i = 1; i <= 127; ++i) {
    std::stringstream stream;
    stream << std::setfill('0') << std::setw(2) << std::hex << i;
    std::string result(stream.str());
    s.replace(21, 2, result);
    // std::cout << s << std::endl;
    std::string temp = std::to_string(i) + s1 + s;
    v.emplace_back(temp);
  }

  for (auto r : v) { std::cout << r << std::endl; }

  // p->Flush();
}
