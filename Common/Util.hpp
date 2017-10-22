#ifndef COMMON_UTIL_HPP
#define COMMON_UTIL_HPP
#include <vector>
#include <string>
#include <sstream>

namespace Util {

  std::vector<std::string> str_split(
    const std::string &str,
    const char delimiter
    )
  {
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;

    while(std::getline(ss, tok, delimiter))
    {
      internal.emplace_back(tok);
    }

    return internal;
  }

}

#endif
