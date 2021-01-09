TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    mapwindow.cc \
    gameeventhandler.cpp \
    objectmanager.cpp \
    dialog.cpp \
    gameengine.cpp \
    customgamescene.cpp \
    custommapitem.cpp \
    dialogtile.cpp \
    oremine.cpp \
    mountain.cpp \
    desert.cpp \
    swamp.cpp \
    icefield.cpp \
    bank.cpp \
    sawmill.cpp \
    miner.cpp \
    lumberjack.cpp \
    dialoginfo.cpp \
    dialogstory.cpp

HEADERS += \
    mapwindow.hh \
    gameeventhandler.hh \
    objectmanager.hh \
    dialog.hh \
    gameengine.hh \
    customgamescene.hh \
    custommapitem.hh \
    customresourcemap.hh \
    dialogtile.hh \
    oremine.hh \
    mountain.hh \
    desert.hh \
    swamp.hh \
    icefield.hh \
    bank.hh \
    sawmill.hh \
    miner.hh \
    lumberjack.hh \
    dialoginfo.hh \
    dialogstory.hh

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    dialog.ui \
    dialogtile.ui \
    dialoginfo.ui \
    dialogstory.ui

DISTFILES +=
