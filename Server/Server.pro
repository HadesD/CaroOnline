#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T18:58:31
#
#-------------------------------------------------

#QT       += core

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32: LIBS += $$PWD/../Lfs/libs/WS2_32.Lib

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
    DEFINES += DEBUG
} else {
    DESTDIR = build/release
    CONFIG += static
}

CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += USE_SPDLOG
DEFINES += IS_SERVER

INCLUDEPATH += ../Common/third_party/asio/asio/include \
            ../Common/third_party/spdlog/include \
            .

SOURCES += \
        ../Common/Util.cpp \
        ../Common/Point2D.cpp \
        ../Common/Config.cpp \
        ../Common/GameBoard.cpp \
        ../Common/Logger.cpp \
        ../Common/MessageStruct.cpp \
        ../Common/net/Socket.cpp \
        ../Common/net/socket/Udp.cpp \
        src/main.cpp \
        src/Room.cpp \
        src/Server.cpp

HEADERS += \
        app/App.hpp \
        app/Config.hpp \
        app/Server.hpp \
        app/Type.hpp
