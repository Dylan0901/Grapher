QT += opengl

DESTDIR = ../grapher/build
TARGET = grapher

SOURCES += \
    src\main.cpp \
    src\glwidget.cpp \
    src\model.cpp \
    src\player.cpp \
    src\scene.cpp \
    src\objloader.cpp

INCLUDEPATH += include

HEADERS += \
    include\glwidget.h \
    include\types3d.h \
    include\model.h \
    include\player.h \
    include\scene.h \
    include\objloader.h \
    include\events.h

RESOURCES += \
    resources.qrc


