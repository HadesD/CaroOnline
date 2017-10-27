cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

message(" ${CMAKE_CXX_COMPILER_ID} ")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limited configs" FORCE)
set(APP_NAME CaroServer)
project(${APP_NAME})
# find_package(Tcmalloc)
# find_package(Threads)
# include(CheckCXXSourceCompiles)

#############################################################################
#
# Required Lib List
#
#############################################################################

set(APP_REQUIRED_LIB
  ${CMAKE_THREAD_LIBS_INIT}
  pthread
  )

set(INCLUDE_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}/../Common/third_party/asio/asio/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../Common/third_party/spdlog/include"
  )

#############################################################################
#
# Application Cpp file need to build
#
#############################################################################

set(APP_SRC
  # Common
  ../Common/Config.cpp
  ../Common/Logger.cpp
  ../Common/GameBoard.cpp
  ../Common/MessageStruct.cpp
  ../Common/net/Socket.cpp
  ../Common/net/socket/Udp.cpp
  ../Common/Util.cpp
  ../Common/Point2D.cpp

  # Application
  src/main.cpp
  src/Server.cpp
  )

#############################################################################
#
# Setup various build flags for different supported compilers and systems
#
#############################################################################

set(CXX_FLAGS "-std=c++11 -D DEBUG")

# if(IS_WINDOWS OR CYGWIN OR MINGW OR WIN32 OR ("$ENV{OSTYPE}" STREQUAL "msys"))
if (MSYS)
  add_compile_options(-D__USE_W32_SOCKETS)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS} -Wall")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
include_directories(${INCLUDE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#############################################################################
#
# Build project
#
#############################################################################

# Application build
add_executable(${APP_NAME} ${APP_SRC})
target_link_libraries(${APP_NAME} ${APP_REQUIRED_LIB})
