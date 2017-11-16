#include "Util.hpp"

namespace Util {

  std::vector<std::string> split(const std::string &s, const char delim)
  {
    unsigned int i = 0;
    auto pos = s.find(delim);
    std::vector<std::string> v;

    while (pos != std::string::npos) {
      v.emplace_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);
    }

    if (pos == std::string::npos)
    {
      v.emplace_back(s.substr(i, s.length()));
    }

    return v;
  }

  char getMark(const int markNum)
  {
    char m = '-';
    switch (markNum)
    {
      case 0:
        m = ' ';
        break;
      case 1:
        m = 'X';
        break;
      case 2:
        m = 'o';
        break;
      default:
        break;
    }

    return m;
  }
}
