QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += G:\pxr\opencode\XCurve\test\XNurbs\eigen-3.4.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    renderwindow.cpp \
    xnurbs.cpp

HEADERS += \
    mainwindow.h \
    point3d.h \
    point3dw.h \
    renderwindow.h \
    xnurbs.h

FORMS += \
    mainwindow.ui \
    renderwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += F:/Qt15/5.15.2/msvc2019_64/lib/freeglut.lib OpenGL32.Lib
