# -------------------------------------------------
# Project created by QtCreator 2011-07-19T15:43:50
# -------------------------------------------------

TARGET = qt_simul
TEMPLATE = app
CONFIG += staticlib
CONFIG += static

INCLUDEPATH += ./usr/include/GL
INCLUDEPATH += ./libku/libmodbus
INCLUDEPATH += ./libku/libmodbus/src

SOURCES += main.cpp \
    mainwindow.cpp \
    param_vibrasi.cpp \
    create_sinus.cpp \
    libku/fft/fourierf.c \
    libku/fft/fftmisc.c \
    libku/libmodbus/src/modbus.c \
    libku/libmodbus/src/modbus-data.c \
    libku/libmodbus/src/modbus-rtu.c \
    libku/dsp/integrasi.c \
    libku/windowing/windowkan.c \
    libku/windowing/buat_filter.c \
    simpanthread.cpp \
    libku/dsp/itung_rms.c \
    kanalview.cpp \
    waterfall.cpp \
    spektrum.cpp \
    waveform.cpp \
    signalgeneratorset.cpp \
    modulsetting.cpp \
    dbcontrol.cpp \
    motorcontrol.cpp \
    versusview.cpp \
    waveformvs.cpp \
    polar.cpp \
    libku/dsp/filter_lib.c

# libku/dsp/buat_filter.c
HEADERS += mainwindow.h \
    lain.h \
    create_sinus.h \
    libku/libmodbus/src/modbus.h \
    libku/libmodbus/config.h \
    libku\dsp\integrasi.h \
    simpanthread.h \
    mainwindow.h \
    libku/windowing/buat_filter.h \
    libku/windowing/windowkan.h \
    kanalview.h \
    waterfall.h \
    spektrum.h \
    waveform.h \
    alokasi.h \
    signalgeneratorset.h \
    modulsetting.h \
    dbcontrol.h \
    motorcontrol.h \
    libku/dsp/itung_rms.h \
    libku/dsp/integrasi.h \
    versusview.h \
    waveformvs.h \
    polar.h \
    libku/dsp/filter_lib.h \
    libku/dsp/rute.h

# libku/dsp/buat_filter.h
FORMS += mainwindow.ui \
    kanalview.ui \
    signalgeneratorset.ui \
    modulsetting.ui \
    dbcontrol.ui \
    motorcontrol.ui \
    versusview.ui

static{
QT += core \
    gui \
    network \
    sql \
    opengl

LIBS += -lc \
    -lgcc \
    -lm \
    -lGLU \
    -lglut \
    -lGLC


}



LIBS += -L./libku/libmodbus/src

# ditambah sendiri
unix:DEFINES = _TTY_POSIX_
win32:DEFINES = _TTY_WIN_




#EXTSERIALPORT
unix:!macx:!symbian: LIBS += -L$$PWD/libku/qextserialport-1.2beta2/lib/ -lqextserialport-1.2

INCLUDEPATH += $$PWD/libku/qextserialport-1.2beta2/src
DEPENDPATH += $$PWD/libku/qextserialport-1.2beta2/src

unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/libku/qextserialport-1.2beta2/lib/libqextserialport-1.2.a


