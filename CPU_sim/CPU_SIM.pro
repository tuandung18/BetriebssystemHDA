TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        akkumulator.cpp \
        cpu.cpp \
        main.cpp \
        process.cpp \
        programcounter.cpp

HEADERS += \
    akkumulator.h \
    cpu.h \
    process.h \
    programcounter.h
