QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    curveutil.cpp \
    main.cpp \
    mainwindow.cpp \
    mathutil.cpp \
    mesh.cpp \
    painterwindow.cpp \
    plane.cpp \
    renderwindow.cpp \
    xcurve.cpp \
    xnurbscircle.cpp \
    xnurbscurve.cpp \
    xnurbsfit.cpp \
    xnurbssurface.cpp

HEADERS += \
    bsplinecurve.h \
    curveutil.h \
    mainwindow.h \
    mathutil.h \
    mesh.h \
    painterwindow.h \
    plane.h \
    point3d.h \
    point3dw.h \
    renderwindow.h \
    vector3d.h \
    xcurve.h \
    xnurbscircle.h \
    xnurbscurve.h \
    xnurbsfit.h \
    xnurbssurface.h

FORMS += \
    mainwindow.ui \
    painterwindow.ui \
    renderwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += F:/Qt15/5.15.2/msvc2019_64/lib/freeglut.lib

DISTFILES += \
    line.frag \
    line.vert
