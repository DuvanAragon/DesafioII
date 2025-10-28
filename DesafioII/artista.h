#ifndef ARTISTA_H
#define ARTISTA_H

#include "Album.h"

class Artista {
private:
    // datos personales
    int idArtista;
    char* nombre;
    int edad;
    char* paisOrigen;
    int seguidores;
    int posicionGlobal;

    // gestión de álbumes
    Album** albumes;
    int cantidadAlbumes;
    int capacidadAlbumes;

    void expandirCapacidadAlbumes();
    void copiarAlbumes(Album** origen, int cantidad);
    void liberarAlbumes();

    // gestión de cadenas
    char* copiarCadena(const char* origen);
    void liberarCadena(char*& cadena);
    int longitudCadena(const char* cadena) const;

public:
    // constructores y destructor
    Artista();
    Artista(int id, const char* nombre, int edad, const char* pais,
            int seguidores, int posicion);
    Artista(const Artista& otro);
    ~Artista();

    // getters
    int getIdArtista() const;
    const char* getNombre() const;
    int getEdad() const;
    const char* getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionGlobal() const;
    Album** getAlbumes() const;
    int getCantidadAlbumes() const;

    // setters
    void setIdArtista(int id);
    void setNombre(const char* nombre);
    void setEdad(int edad);
    void setPaisOrigen(const char* pais);
    void setSeguidores(int seguidores);
    void setPosicionGlobal(int posicion);
    void setAlbumes(Album** albumes, int cantidad);

    // métodos funcionales
    void agregarAlbum(Album* album);
    void mostrarInformacion() const;
    Cancion* buscarCancionPorId(int idCancion) const;

    // operador
    Artista& operator=(const Artista& otro);
};

#endif
