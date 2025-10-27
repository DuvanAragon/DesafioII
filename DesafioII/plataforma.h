#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <iostream>
#include <fstream>
#include <string>
#include <random>

#include "cancion.h"
#include "credito.h"
#include "album.h"
#include "artista.h"
#include "Usuario.h"
#include "Anuncios.h"
using namespace std;

class Plataforma {
private:
    // ====== CANCIONES (INDEXADAS) ======
    int* idsCanciones;
    string* lineasCanciones;
    int cantidadCanciones;
    int capacidadCanciones;

    // ====== CREDITOS (INDEXADOS) ======
    int* idCancionesCred;
    string* lineasCreditos;
    int cantidadCreditos;
    int capacidadCreditos;

    // ====== ALBUMES (INDEXADOS) ======
    int* idArtistas;
    int* idAlbumes;
    string* lineasAlbumes;
    int cantidadAlbumes;
    int capacidadAlbumes;

    // ====== ARTISTAS (CARGA COMPLETA) ======
    Artista** artistas;
    int cantidadArtistas;
    int capacidadArtistas;

    // ====== USUARIOS (CARGA COMPLETA) ======
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

    // ====== ANUNCIOS (CARGA COMPLETA) ======
    Anuncio** anuncios;
    int cantidadAnuncios;
    int capacidadAnuncios;

    // Métodos auxiliares para parsear
    Cancion* parsearCancion(const string& linea);
    Credito* parsearCredito(const string& linea);
    Album* parsearAlbum(const string& linea);


public:
    Plataforma();
    ~Plataforma();

    // ==== MÉTODOS CANCIONES ====
    void indexarCanciones(const string& ruta);
    Cancion* cargarCancion(int id);
    int getCantidadCanciones() { return cantidadCanciones; }

    // ==== MÉTODOS CREDITOS ====
    void indexarCreditos(const string& ruta);
    Credito* cargarCredito(int idCancion);
    int getCantidadCreditos() { return cantidadCreditos; }

    // ==== MÉTODOS ALBUMES ====
    void indexarAlbumes(const string& ruta);
    Album* cargarAlbum(int idArtista, int idAlbum);
    int getCantidadAlbumes() { return cantidadAlbumes; }

    // ==== MÉTODOS ARTISTAS ====
    void cargarArtistas(const string& ruta);
    Artista* buscarArtista(int idArtista);
    int getCantidadArtistas() { return cantidadArtistas; }

    // ==== MÉTODOS USUARIOS ====
    void cargarUsuarios(const string& ruta);
    Usuario* buscarUsuario(const string& nickname);
    int getCantidadUsuarios() { return cantidadUsuarios; }

    // ==== MÉTODOS ANUNCIOS ====
    void cargarAnuncios(const string& ruta);
    Anuncio* obtenerAnuncioAleatorio(int ultimoIndice);
    int getCantidadAnuncios() { return cantidadAnuncios; }
    Anuncio* getAnuncio(int i) { return (i >= 0 && i < cantidadAnuncios) ? anuncios[i] : nullptr; }

    // ==== MÉTODOS PERSISTENCIA LISTAS ====
    void cargarListasFavoritosDesdeArchivo(const string& ruta);
    void guardarListasFavoritosEnArchivo(const string& ruta);

    // En la sección public de la clase Plataforma:

    // ==== MÉTODOS DE GUARDADO ====
    void guardarCanciones(const string& ruta);
    void guardarCreditos(const string& ruta);
    void guardarAlbumes(const string& ruta);
    void guardarArtistas(const string& ruta);
    void guardarUsuarios(const string& ruta);
    void guardarAnuncios(const string& ruta);

    // ==== MÉTODOS DE ACTUALIZACIÓN (para datos indexados) ====
    void actualizarLineaCancion(int idCancion);
    void actualizarLineaCredito(int idCancion);
    void actualizarLineaAlbum(int idArtista, int idAlbum);

    // ==== MÉTODOS DE AGREGADO ====
    void agregarCancion(Cancion* cancion);
    void agregarAlbum(int idArtista, Album* album);
    void agregarArtista(Artista* artista);
    void agregarUsuario(Usuario* usuario);

    // ==== MÉTODOS DE ELIMINACIÓN ====
    bool eliminarCancion(int idCancion);
    bool eliminarArtista(int idArtista);
    bool eliminarUsuario(const string& nickname);

    // ==== MÉTODO DE LOGIN ====
    Usuario* login(const string& nickname);
    Cancion* seleccionarCancionAleatoria(int ultimoID = -1);

};

#endif
