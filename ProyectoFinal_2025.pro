QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemigo.cpp \
    entidad.cpp \
    hitbox.cpp \
    juego.cpp \
    luchador.cpp \
    main.cpp \
    mainwindow.cpp \
    nivel.cpp \
    nivel2_3.cpp \
    nivel_1.cpp \
    obstaculo.cpp \
    personajejugador.cpp \
    personajejugadornivel_1.cpp

HEADERS += \
    GameTypes.h \
    enemigo.h \
    entidad.h \
    hitbox.h \
    juego.h \
    luchador.h \
    mainwindow.h \
    nivel.h \
    nivel2_3.h \
    nivel_1.h \
    obstaculo.h \
    personajejugador.h \
    personajejugadornivel_1.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc \
    Sonidos.qrc \
    Sprites.qrc
