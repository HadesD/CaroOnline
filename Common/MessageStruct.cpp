#include <iostream>

#include "MessageStruct.hpp"

#include "Logger.hpp"

namespace common {

  MessageStruct::MessageStruct(const std::string &msg) : data(msg)
  {
    try
    {
      std::size_t maxI = sizeof(sum);
      if (data.length() >= maxI)
      {
        for (std::size_t i = 0; i < maxI; i++)
        {
          sum[i] = data.at(i);
        }
        std::cout << sum << std::endl;
      }
    }
    catch(const std::out_of_range &e)
    {
      Log::error(e.what());
    }
    catch(...)
    {
      Log::error("MessageStruct :: construct() :: Error not found!");
    }
  }

  bool MessageStruct::isValidSum()
  {
    return false;
  }

}
