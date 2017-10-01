#include <iostream>
#include <cstring>

#include "MessageStruct.hpp"

#include "Logger.hpp"

namespace common {

  MessageStruct::MessageStruct(const std::string &msg) : data(msg)
  {
  }

  bool MessageStruct::isValidSum()
  {
    Log::info("MessageStruct :: isValidSum() :: start");
    auto &config_sum = common::config::networkCheckSum;

    if (data.empty() || data.size() < config_sum.size())
    {
      return false;
    }

    for (std::size_t i = 0; i < config_sum.size(); i++)
    {
      if (data.at(i) != config_sum.at(i))
      {
        return false;
      }
    }

    Log::info("MessageStruct :: isValidSum() :: true");

    return true;
  }

}
