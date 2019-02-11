TEMPLATE = app
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CFLAGS += -std=c++17
LIBS += -pthread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    matrix_sum.cpp

HEADERS += \
    profile.h \
    test_runner.h


