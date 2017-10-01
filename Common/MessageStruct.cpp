#include <iostream>
#include <cstring>

#include "MessageStruct.hpp"

#include "Logger.hpp"

namespace common {

  MessageStruct::MessageStruct(const std::string &msg) : data(msg)
  {
    auto &config_sum = common::config::networkCheckSum;

    if (!data.empty() && (data.size() < config_sum.size()))
    {
      sum = std::string(msg.cbegin(), msg.cbegin() + 4);
    }
  }

  MessageStruct::~MessageStruct()
  {
    // delete sum;
  }

  bool MessageStruct::isValidSum()
  {
    Log::info("MessageStruct :: isValidSum() :: start");

    Log::info("MessageStruct :: isValidSum() :: true");

    return true;
  }

}
