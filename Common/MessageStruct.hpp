#ifndef COMMON_MESSAGE_STRUCT_HPP
#define COMMON_MESSAGE_STRUCT_HPP
#include <string>

namespace common {

  struct MessageStruct
  {
    typedef int Sum;

    Sum sum;
    unsigned int sequenceNumber;
    std::string message;

    bool isValidSum();
  };

}

#endif
