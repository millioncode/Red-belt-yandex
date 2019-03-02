TEMPLATE = app
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    server_stats.cpp

HEADERS += \
    http_request.h \
    stats.h \
    test_runner.h
