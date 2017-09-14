CXX=g++ -std=gnu++1z -g
LIBS=$()
FLAGS=
RM=/bin/rm -rf

.PHONY: run clean

default: build

build:
	$(CXX) -I. \
		-I../Common/third_party/asio/asio/include \
		-lpthread \
		-pthread \
		-o bin/server \
		../Common/Config.cpp \
		../Common/net/Socket.cpp \
		src/main.cpp \
		src/Server.cpp

run:
	cd bin && ./server

clean:
	$(RM) bin/*

