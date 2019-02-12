TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CFLAGS += -std=c++17
LIBS += -pthread
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    explore_key_words.cpp
