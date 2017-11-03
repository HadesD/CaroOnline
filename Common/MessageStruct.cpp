#include <iostream>
#include <cstring>

#include "MessageStruct.hpp"

#include "Logger.hpp"

namespace common {

  MessageStruct::MessageStruct(const std::string &m) : data(m)
  {
    auto config_sum = common::config::networkCheckSum;

    // Must check received data has correct sum 's size
    if (!data.empty() && (data.size() >= config_sum.size()))
    {
      // Sum
      sum = std::string(data.cbegin(), data.cbegin() + config_sum.size());

      // Request Method
      msgType = static_cast<MessageType>(data.at(sum.size()));
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

    try
    {
      msg = std::string(
        data.cbegin()
        + sum.size()
        + sizeof(static_cast<char>(msgType))
        ,
        data.cend()
        );
    }
    catch(...)
    {
      Log::error("Error msg");
    }

    if (!msg.empty())
    {
      Log::info("Message: " + msg);
    }

    return true;
  }

}
