#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T18:58:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CaroOnlineQt
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

DEFINES += IS_QT_CLIENT

win32: LIBS += $$PWD/../Lfs/libs/WS2_32.Lib

Release: CONFIG += static
Debug: DEFINES += DEBUG
#Release: DESTDIR = $$PWD/Release
#Release: OBJECTS_DIR = $$PWD/Release/.obj
#Release: MOC_DIR = $$PWD/Release/.moc
#Release: RCC_DIR = $$PWD/Release/.rcc
#Release: UI_DIR = $$PWD/Release/.ui

#Debug: DESTDIR = $$PWD/Debug
#Debug: OBJECTS_DIR = $$PWD/Debug/.obj
#Debug: MOC_DIR = $$PWD/Debug/.moc
#Debug: RCC_DIR = $$PWD/Debug/.rcc
#Debug: UI_DIR = $$PWD/Debug/.ui

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
        main.cpp \
        MainWindow.cpp \
        AppConfig.cpp

HEADERS += \
        ../Common/Logger.hpp \
        MainWindow.hpp \
        AppConfig.hpp

FORMS += \
        MainWindow.ui

DISTFILES += \
    styles.qml
