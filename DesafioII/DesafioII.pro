QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        anuncios.cpp \
        listaFavoritos.cpp \
        main.cpp \
        medidorRecursos.cpp \
        plataforma.cpp \
        credito.cpp \
        cancion.cpp \
        album.cpp \
        sistemaReproduccion.cpp \
        usuario.cpp \
        artista.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    anuncios.h \
    listaFavoritos.h \
    medidorRecursos.h \
    plataforma.h\
    credito.h \
    cancion.h \
    album.h \
    sistemaReproduccion.h \
    usuario.h\
    artista.h
