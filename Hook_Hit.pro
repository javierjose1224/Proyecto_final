QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    disparo.cpp \
    endgame.cpp \
    hd_nivel.cpp \
    main.cpp \
    mainwindow.cpp \
    muro.cpp \
    nivel.cpp \
    partidas.cpp \
    pelota.cpp \
    personaje.cpp \
    pua.cpp \
    puntaje.cpp \
    senoidal.cpp \
    sesion.cpp \
    settingswindow.cpp \
    tiempo_juego.cpp \
    vida.cpp

HEADERS += \
    disparo.h \
    endgame.h \
    endgame.h \
    hd_nivel.h \
    mainwindow.h \
    muro.h \
    nivel.h \
    partidas.h \
    pelota.h \
    personaje.h \
    pua.h \
    puntaje.h \
    senoidal.h \
    sesion.h \
    sesion.h \
    settingswindow.h \
    tiempo_juego.h \
    vida.h

FORMS += \
    endgame.ui \
    mainwindow.ui \
    partidas.ui \
    sesion.ui \
    settingswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
