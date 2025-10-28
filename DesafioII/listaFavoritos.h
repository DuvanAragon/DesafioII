#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <iostream>
using namespace std;

class Usuario;
class Cancion;

class ListaFavoritos {
private:
    // propiedades del usuario
    Usuario* usuarioPropietario;

    // gestión de canciones
    Cancion** canciones;
    int capacidadCanciones;
    int cantidadCanciones;

    // gestión de listas seguidas
    ListaFavoritos** listasSeguidas;
    int capacidadListasSeguidas;
    int cantidadListasSeguidas;

    // métodos de redimensionamiento
    void redimensionarCanciones();
    void redimensionarListasSeguidas();

public:
    // constructores y destructor
    ListaFavoritos();
    ListaFavoritos(Usuario* _usuario);
    ~ListaFavoritos();

    // getters
    Cancion** getCanciones();
    int getCantidadCanciones();
    ListaFavoritos** getListasSeguidas();
    Usuario* getUsuarioPropietario();
    int getCantidadListasSeguidas() const;

    // operaciones con canciones
    bool existeCancion(int _id);
    void agregarCancion(Cancion* _cancion);
    void eliminarCancion(int _id);
    Cancion* getCancionEn(int index);
    void mostrarCanciones();

    // operaciones con listas seguidas
    void seguirLista(ListaFavoritos* _lista);

    // operaciones combinadas
    Cancion** obtenerTodasLasCanciones(int& cantidadTotal);
    int getCantidadTotalCanciones();
};

#endif
