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
    UPDATE_GAME,
    GAME_OVER,
    QUIT_GAME,
  };

  struct MessageStruct
  {
    MessageStruct(const std::string &/* msg */);
    ~MessageStruct();

    // Checksum code
    std::string sum;

    // Sequence Number

    MessageType msgType;

    unsigned int seqNum;

    // Message
    const std::string &data;
    std::string msg;

    bool isValidSum();
  };

}

#endif
