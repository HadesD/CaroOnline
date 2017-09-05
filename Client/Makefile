CXX=g++ -std=gnu++1z -g
LIBS=$()
FLAGS=
RM=/bin/rm -rf

.PHONY: run clean

default: build

build:
	$(CXX) -I. -o bin/caro \
		src/main.cpp \
		src/core/Game.cpp \
		src/Kbhit.cpp \
		src/Player.cpp \
		src/WindowManager.cpp \
		../Common/Config.cpp \
		src/Config.cpp \
		src/Scene.cpp \
		src/Point2D.cpp \
		src/scenes/PlayScene.cpp \
		src/scenes/IntroScene.cpp

run:
	cd bin && ./caro

clean:
	$(RM) bin/*

