TEMPLATE = app
CONFIG += console c++17
QMAKE_CXXFLAGS += -std=c++17 -pthread
QMAKE_CFLAGS += -std=c++17 -pthread
LIBS += -pthread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    priority_collection_2.cpp

HEADERS += \
    test_runner.h
