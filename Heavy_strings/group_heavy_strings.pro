TEMPLATE = app
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    group_heavy_strings.cpp

HEADERS += \
    test_runner.h

DISTFILES += \
    task
