CXX=g++ -std=gnu++1z -g
LIBS=$()
FLAGS=
RM=/bin/rm -rf

.PHONY: run clean

default: build

build:
	$(CXX) -I. \
		-I../Common/third_party/asio/asio/include \
		-I../Common/third_party/spdlog/include \
		-lpthread \
		-pthread \
		-o bin/caro \
		../Common/Config.cpp \
		src/main.cpp \
		src/core/Game.cpp \
		src/input/Kbhit.cpp \
		src/Player.cpp \
		src/WindowManager.cpp \
		src/Config.cpp \
		src/Scene.cpp \
		src/Point2D.cpp \
		src/scenes/PlayScene.cpp \
		src/scenes/IntroScene.cpp

run:
	cd bin && ./caro

clean:
	$(RM) bin/*

