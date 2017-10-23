#ifndef COMMON_UTIL_HPP
#define COMMON_UTIL_HPP
#include <vector>
#include <string>
#include <sstream>

namespace Util {

  std::vector<std::string> str_split(
    const std::string &str,
    const char delimiter
    );

}

#endif
