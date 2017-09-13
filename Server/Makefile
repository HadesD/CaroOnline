CXX=g++ -std=gnu++1z -g
LIBS=$()
FLAGS=
RM=/bin/rm -rf

.PHONY: run clean

default: build

build:
	$(CXX) -I. \
		-lpthread \
		-pthread \
		-o bin/server \
		src/main.cpp \
		../Common/Config.cpp \
		../Common/Net/Socket.cpp \
		src/Server.cpp

run:
	cd bin && ./server

clean:
	$(RM) bin/*

