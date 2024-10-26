QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    TDA.cpp \
    main.cpp \
    menuAdm.cpp \
    menuPri.cpp \
    Utilidades.cpp \
    menuUsr.cpp \
    registro.cpp \
    reportes.cpp

HEADERS += \
    ArbolAVL.h \
    ArbolB.h \
    ArbolBB.h \
    Grafo.h \
    ListaCDE.h \
    ListaDE.h \
    ListaSE.h \
    Matriz.h \
    Nodos.h \
    Pila.h \
    SimpleMap.h \
    TDA.h \
    Utilidades.h \
    menuAdm.h \
    menuPri.h \
    menuUsr.h \
    registro.h \
    reportes.h

FORMS += \
    menuAdm.ui \
    menuPri.ui \
    menuUsr.ui \
    registro.ui \
    reportes.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
