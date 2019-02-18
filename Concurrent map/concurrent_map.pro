TEMPLATE = app
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17 -pthread
QMAKE_CFLAGS += -std=c++17 -pthread
LIBS += -pthread

CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    profile.h \
    test_runner.h

DISTFILES += \
    text
