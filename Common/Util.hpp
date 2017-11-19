#ifndef COMMON_UTIL_HPP
#define COMMON_UTIL_HPP
#include <vector>
#include <string>
#include <sstream>

namespace Util {


  std::vector<std::string> split(const std::string &s, const char delim);

  char getMark(const int markNum);

}

#endif
