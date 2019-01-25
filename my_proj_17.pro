TEMPLATE = app
# подключаю С++17
CONFIG += console c++17
QMAKE_CXXFLAGS += -std=c++17

CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
