#include "logger.h"

int main() {
  px::logger::Logger::LOG();
  px::logger::Logger::LOG("A");
  px::logger::Logger::LOG("B");
  px::logger::Logger::LOG("C");
  px::logger::Logger::LOG("D");
}
