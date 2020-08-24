QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    d2ag022.cpp \
    d2hk264.cpp \
    d2pa019.cpp \
    d2py081.cpp \
    d2va010.cpp \
    d2vk023.cpp \
    d2vk024.cpp \
    d2vv048.cpp \
    drivecells.cpp \
    form.cpp \
    main.cpp \
    mysocket.cpp \
    widget.cpp

HEADERS += \
    d2ag022.h \
    d2hk264.h \
    d2pa019.h \
    d2py081.h \
    d2va010.h \
    d2vk023.h \
    d2vk024.h \
    d2vv048.h \
    drivecells.h \
    form.h \
    mysocket.h \
    widget.h

FORMS += \
    form.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
