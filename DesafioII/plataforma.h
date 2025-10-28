#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "cancion.h"
#include "album.h"
#include "credito.h"
#include "artista.h"
#include "usuario.h"
#include "Anuncios.h"

using namespace std;

class Plataforma {
private:
    // estructuras de datos para indexación
    int capacidadCanciones;
    int cantidadCanciones;
    int* idsCanciones;
    string* lineasCanciones;

    int capacidadCreditos;
    int cantidadCreditos;
    int* idCancionesCred;
    string* lineasCreditos;

    int capacidadAlbumes;
    int cantidadAlbumes;
    int* idArtistas;
    int* idAlbumes;
    string* lineasAlbumes;

    // arreglos dinámicos de objetos
    int capacidadArtistas;
    int cantidadArtistas;
    Artista** artistas;

    int capacidadUsuarios;
    int cantidadUsuarios;
    Usuario** usuarios;

    int capacidadAnuncios;
    int cantidadAnuncios;
    Anuncio** anuncios;

public:
    // constructor y destructor
    Plataforma();
    ~Plataforma();

    // canciones
    void indexarCanciones(const string& ruta);
    void ordenarCancionesPorId();
    void quickSortCanciones(int izq, int der);
    int particionCanciones(int izq, int der);
    Cancion* cargarCancion(int id);
    Cancion* cargarCancion(int id, int& iteraciones);
    Cancion* parsearCancion(const string& linea);
    void guardarCanciones(const string& ruta);
    void actualizarLineaCancion(int idCancion);
    void agregarCancion(Cancion* cancion);
    bool eliminarCancion(int idCancion);
    Cancion* seleccionarCancionAleatoria(int ultimoID);

    // álbumes
    void indexarAlbumes(const string& ruta);
    void ordenarAlbumesPorId();
    void quickSortAlbumes(int izq, int der);
    int particionAlbumes(int izq, int der);
    long long combinarIds(int idArtista, int idAlbum);
    Album* cargarAlbum(int idArtista, int idAlbum);
    Album* cargarAlbum(int idArtista, int idAlbum, int& iteraciones);
    Album* parsearAlbum(const string& linea);
    void guardarAlbumes(const string& ruta);
    void actualizarLineaAlbum(int idArtista, int idAlbum);
    void agregarAlbum(int idArtista, Album* album);

    // créditos
    void indexarCreditos(const string& ruta);
    void ordenarCreditosPorId();
    void quickSortCreditos(int izq, int der);
    int particionCreditos(int izq, int der);
    Credito* cargarCredito(int idCancion);
    Credito* cargarCredito(int idCancion, int& iteraciones);
    Credito* parsearCredito(const string& linea);
    void guardarCreditos(const string& ruta);
    void actualizarLineaCredito(int idCancion);

    // artistas
    void cargarArtistas(const string& ruta);
    Artista* buscarArtista(int idArtista);
    void guardarArtistas(const string& ruta);
    void agregarArtista(Artista* artista);
    bool eliminarArtista(int idArtista);

    // usuarios
    void cargarUsuarios(const string& ruta);
    Usuario* buscarUsuario(const string& nickname);
    void guardarUsuarios(const string& ruta);
    void agregarUsuario(Usuario* usuario);
    bool eliminarUsuario(const string& nickname);
    Usuario* login(const string& nickname);

    // anuncios
    void cargarAnuncios(const string& ruta);
    Anuncio* obtenerAnuncioAleatorio(int ultimoIndice);
    void guardarAnuncios(const string& ruta);

    // getters para anuncios
    Anuncio** getListaAnuncios() const { return anuncios; }
    int getTotalAnuncios() const { return cantidadAnuncios; }

    // listas de favoritos
    void cargarListasFavoritosDesdeArchivo(const string& ruta);
    void guardarListasFavoritosEnArchivo(const string& ruta);

};

#endif
