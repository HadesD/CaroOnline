#ifndef COMMON_MESSAGE_STRUCT_HPP
#define COMMON_MESSAGE_STRUCT_HPP
#include <string>

#include "Config.hpp"

namespace common {

  // MessageType must be char
  // static_cast<MessageType>('a')
  enum class MessageType
  {
    LOGIN = 'a',
    SET_MOVE,
  };

  struct MessageStruct
  {
    MessageStruct(const std::string &/* msg */);
    ~MessageStruct();

    // Checksum code
    // char *sum;
    std::string sum;

    // Sequence Number

    MessageType msgType;

    unsigned int seqNum;

    // Message
    const std::string &data;

    bool isValidSum();
  };

}

#endif
