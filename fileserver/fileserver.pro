QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp \
    requestdispatcherthread.cpp \
    requestworker.cpp \
    readerwritercache.cpp \
    readerwriterlock.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h \
    buffern.h \
    requestdispatcherthread.h \
    requestworker.h \
    option.h \
    readerwritercache.h \
    readerwriterlock.h

EXAMPLE_FILES += fileclient.html

