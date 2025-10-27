#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include "Cancion.h"
#include "sistemareproduccion.h"
#include <iostream>

class Usuario; // Declaración adelantada

class ListaFavoritos {
private:
    Cancion** canciones;
    int capacidadCanciones;
    int cantidadCanciones;

    ListaFavoritos** listasSeguidas;
    int capacidadListasSeguidas;
    int cantidadListasSeguidas;

    Usuario* usuarioPropietario;

public:
    ListaFavoritos();
    ListaFavoritos(Usuario* _usuario);

    // Getters
    Cancion** getCanciones();
    int getCantidadCanciones();
    ListaFavoritos** getListasSeguidas();
    Usuario* getUsuarioPropietario();

    // Funciones principales
    bool existeCancion(int _id);
    void agregarCancion(Cancion* _cancion);
    void eliminarCancion(int _id);
    void seguirLista(ListaFavoritos* _lista);

    // NUEVO: Mostrar canciones dinámicamente
    void mostrarCanciones();

    // NUEVO: Reproducir lista considerando listas seguidas
    void reproducirLista(bool aleatorio, SistemaReproduccion* sistema);

    ~ListaFavoritos();
};

#endif
