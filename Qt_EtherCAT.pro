QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += ./zmotion.so
SOURCES += \
    dialog.cpp \
    login.cpp \
    loginaaaa.cpp \
    main.cpp \
    mainwindow.cpp \
    zaux.cpp

HEADERS += \
    dialog.h \
    includes/zmotion.h \
    login.h \
    loginaaaa.h \
    mainwindow.h \
    zaux.h \
    zmotion.h

FORMS += \
    dialog.ui \
    loginaaaa.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc



unix|win32: LIBS += -L$$PWD/./ -lzmotion

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
