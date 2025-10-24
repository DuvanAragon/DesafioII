#ifndef ARTISTA_H
#define ARTISTA_H

#include "Album.h"

/*
 * Clase Artista: Representa un artista musical
 * Gestiona su catálogo de albumes y datos personales
 */
class Artista {
private:
    int idArtista; // 5 digitos
    char* nombre;
    int edad;
    char* paisOrigen;
    int seguidores;
    int posicionGlobal;

    Album** albumes; // Arreglo dinamico de albumes
    int cantidadAlbumes;
    int capacidadAlbumes;

public:
    // Constructores
    Artista();
    Artista(int id, const char* nombre, int edad, const char* pais,
            int seguidores, int posicion);
    Artista(const Artista& otro); // Constructor de copia
    ~Artista(); // Destructor

    // Getters
    int getIdArtista() const;
    const char* getNombre() const;
    int getEdad() const;
    const char* getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionGlobal() const;
    Album** getAlbumes() const;
    int getCantidadAlbumes() const;

    // Setters
    void setIdArtista(int id);
    void setNombre(const char* nombre);
    void setEdad(int edad);
    void setPaisOrigen(const char* pais);
    void setSeguidores(int seguidores);
    void setPosicionGlobal(int posicion);
    void setAlbumes(Album** albumes, int cantidad);

    // Metodos funcionales
    void agregarAlbum(Album* album);
    void mostrarInformacion() const;
    Cancion* buscarCancionPorId(int idCancion) const;

    // Sobrecarga de operador
    Artista& operator=(const Artista& otro);

private:
    void expandirCapacidadAlbumes();
    void copiarAlbumes(Album** origen, int cantidad);
    void liberarAlbumes();

    // Funciones auxiliares para manejo de cadenas
    char* copiarCadena(const char* origen);
    void liberarCadena(char*& cadena);
    int longitudCadena(const char* cadena) const;
};

#endif
