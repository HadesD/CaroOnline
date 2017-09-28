CXX=g++ -std=gnu++1y -g
LIBS=$()
FLAGS=
RM=/bin/rm -rf

.PHONY: run clean

default: cmake

cmake:
	cd build && cmake .. && make

build:
	$(CXX) -I. \
		-I../Common/third_party/asio/asio/include \
		-I../Common/third_party/spdlog/include \
		-lpthread \
		-pthread \
		-o bin/server \
		../Common/Config.cpp \
		../Common/Logger.cpp \
		../Common/MessageStruct.cpp \
		../Common/net/Socket.cpp \
		../Common/net/socket/Udp.cpp \
		src/main.cpp \
		src/Server.cpp

run:
	cd bin && ./CaroServer

clean:
	$(RM) bin/*

