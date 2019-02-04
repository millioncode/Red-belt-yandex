TEMPLATE = app
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -Ofast


SOURCES += \
    airport_counter.cpp
