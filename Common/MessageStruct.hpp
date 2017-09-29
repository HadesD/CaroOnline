#ifndef COMMON_MESSAGE_STRUCT_HPP
#define COMMON_MESSAGE_STRUCT_HPP
#include <string>

namespace common {

  struct MessageStruct
  {
    MessageStruct(const std::string &/* data */);

    // Checksum code
    char sum[4];

    // Sequence Number
    unsigned int seqNum;

    // Message
    std::string msg;

    bool isValidSum();
  };

}

#endif
