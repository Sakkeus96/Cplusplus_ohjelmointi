QT       += testlib

QT       += gui

QT       += widgets

TARGET = gameeventhandlertest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++14
TEMPLATE = app

DESTDIR = bin

INCLUDEPATH += \
    ../../Course/CourseLib/\
    ../../Game/

DEPENDPATH += \
    ../../Course/CourseLib/\
    ../../Game/

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS +=\
    ../../Game/objectmanager.hh \
    ../../Game/gameeventhandler.hh \
    ../../Course/CourseLib/interfaces/igameeventhandler.h \
    ../../Course/CourseLib/interfaces/iobjectmanager.h \
    ../../Course/CourseLib/buildings/buildingbase.h \
    ../../Course/CourseLib/buildings/farm.h \
    ../../Course/CourseLib/buildings/headquarters.h \
    ../../Course/CourseLib/buildings/outpost.h \
    ../../Course/CourseLib/core/basicresources.h \
    ../../Course/CourseLib/core/coordinate.h \
    ../../Course/CourseLib/core/gameobject.h \
    ../../Course/CourseLib/core/placeablegameobject.h \
    ../../Course/CourseLib/core/playerbase.h \
    ../../Course/CourseLib/core/resourcemaps.h \
    ../../Course/CourseLib/core/worldgenerator.h \
    ../../Course/CourseLib/exceptions/baseexception.h \
    ../../Course/CourseLib/exceptions/illegalaction.h \
    ../../Course/CourseLib/exceptions/invalidpointer.h \
    ../../Course/CourseLib/exceptions/keyerror.h \
    ../../Course/CourseLib/exceptions/notenoughspace.h \
    ../../Course/CourseLib/exceptions/ownerconflict.h \
    ../../Course/CourseLib/graphics/simplegamescene.h \
    ../../Course/CourseLib/graphics/simplemapitem.h \
    ../../Course/CourseLib/interfaces/igameeventhandler.h \
    ../../Course/CourseLib/interfaces/iobjectmanager.h \
    ../../Course/CourseLib/tiles/forest.h \
    ../../Course/CourseLib/tiles/grassland.h \
    ../../Course/CourseLib/tiles/tilebase.h \
    ../../Course/CourseLib/workers/basicworker.h \
    ../../Course/CourseLib/workers/workerbase.h \



SOURCES += tst_objectmanagertest.cpp \
    ../../Game/objectmanager.cpp \
    ../../Game/gameeventhandler.cpp \
    ../../Course/CourseLib/buildings/buildingbase.cpp \
    ../../Course/CourseLib/buildings/farm.cpp \
    ../../Course/CourseLib/buildings/headquarters.cpp \
    ../../Course/CourseLib/buildings/outpost.cpp \
    ../../Course/CourseLib/core/basicresources.cpp \
    ../../Course/CourseLib/core/coordinate.cpp \
    ../../Course/CourseLib/core/gameobject.cpp \
    ../../Course/CourseLib/core/placeablegameobject.cpp \
    ../../Course/CourseLib/core/playerbase.cpp \
    ../../Course/CourseLib/core/worldgenerator.cpp \
    ../../Course/CourseLib/graphics/simplegamescene.cpp \
    ../../Course/CourseLib/graphics/simplemapitem.cpp \
    ../../Course/CourseLib/tiles/forest.cpp \
    ../../Course/CourseLib/tiles/grassland.cpp \
    ../../Course/CourseLib/tiles/tilebase.cpp \
    ../../Course/CourseLib/workers/basicworker.cpp \
    ../../Course/CourseLib/workers/workerbase.cpp \

QMAKE_CXXFLAGS += --coverage
QMAKE_LFLAGS += --coverage

SUBDIRS += \
    ../../Course/CourseLib/CourseLib.pro
