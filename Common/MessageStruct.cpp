#include <iostream>
#include <cstring>

#include "MessageStruct.hpp"

#include "Logger.hpp"

namespace common {

  MessageStruct::MessageStruct(const std::string &msg) : data(msg)
  {
    auto &config_sum = common::config::networkCheckSum;

    // Must check received data has correct sum 's size
    if (!data.empty() && (data.size() > config_sum.size()))
    {
      // Sum
      sum = std::string(msg.cbegin(), msg.cbegin() + config_sum.size());

      // Request Method
      msgType = static_cast<MessageType>(msg.at(sum.size()));
    }
  }

  MessageStruct::~MessageStruct()
  {
    // delete sum;
  }

  bool MessageStruct::isValidSum()
  {
    Log::info("MessageStruct :: isValidSum() :: start");

    if (sum.empty())
    {
      return false;
    }

    Log::info("MessageStruct :: isValidSum() :: true");

    return true;
  }

}
