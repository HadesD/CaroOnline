CXX=g++ -std=gnu++1z -g
LIBS=$()
FLAGS=
RM=/bin/rm -rf

.PHONY: run clean

default: build

build:
	$(CXX) -I. -o bin/caro \
		src/main.cpp \
		src/Game.cpp \
		src/Kbhit.cpp \
		src/MoveManager.cpp \
		src/Player.cpp

run:
	cd bin && ./caro

clean:
	$(RM) bin/*

