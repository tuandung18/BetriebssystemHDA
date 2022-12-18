TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        akkumulator.cpp \
        cpu.cpp \
        main.cpp \
        mmu.cpp \
        page.cpp \
        process.cpp \
        programcounter.cpp \
        ram.cpp \
        virtualmemory.cpp

HEADERS += \
    akkumulator.h \
    cpu.h \
    mmu.h \
    page.h \
    process.h \
    programcounter.h \
    ram.h \
    virtualmemory.h
