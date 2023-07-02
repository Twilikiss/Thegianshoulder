#-------------------------------------------------
#
# Project created by QtCreator 2021-07-09T19:54:15
#
#-------------------------------------------------

QT       += core gui
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += G://tsttt//Thegianshoulder//includes
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp \
    point.cpp \
    checks.cpp \
    Box.cpp \
    Edge.cpp \
    Situation1.cpp \
    AI.cpp \
    ThreadForAI.cpp \
    AI_small.cpp \
    redis.cpp




HEADERS  += widget.h \
    point.h \
    checks.h \
    Box.h \
    Edge.h \
    Situation1.h \
    AI.h \
    Ai_uct.h \
    ThreadForAI.h \
    AI_small.h \
    includes/adapters/qt.h \
    includes/alloc.h \
    includes/async.h \
    includes/async_private.h \
    includes/dict.h \
    includes/fmacros.h \
    includes/hiredis.h \
    includes/hiredis_ssl.h \
    includes/net.h \
    includes/read.h \
    includes/sds.h \
    includes/sdsalloc.h \
    includes/sockcompat.h \
    includes/win32.h \
    situation.h \
    ui_widget.h \
    redis.h

FORMS    += widget.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    lib/libQtHiRedis.a \
    lib/QtHiRedis.dll

unix|win32: LIBS += -L$$PWD/lib/ -lQtHiRedis

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/QtHiRedis.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/libQtHiRedis.a
