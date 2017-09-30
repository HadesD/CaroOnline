#ifndef COMMON_MESSAGE_STRUCT_HPP
#define COMMON_MESSAGE_STRUCT_HPP
#include <string>

namespace common {

  enum class MessageType
  {
    LOGIN,
    SET_MOVE,
  };

  struct MessageStruct
  {
    MessageStruct(const std::string &/* msg */);

    // Checksum code
    char sum[4];

    // Sequence Number
    unsigned int seqNum;

    // Message
    const std::string &data;

    bool isValidSum();
  };

}

#endif
