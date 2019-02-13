TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++17 -pthread
QMAKE_CFLAGS += -std=c++17 -pthread
LIBS += -pthread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    synchronized.cpp
