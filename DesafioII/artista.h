#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include "Album.h"
using namespace std;

/*
 * Clase Artista: Representa un artista musical
 * Gestiona su catalogo de albumes y datos personales
 */
class Artista {
private:
    int idArtista; // 5 digitos
    string nombre;
    int edad;
    string paisOrigen;
    int seguidores;
    int posicionGlobal;

    Album** albumes; // Arreglo dinamico de albumes
    int cantidadAlbumes;
    int capacidadAlbumes;

public:
    // Constructores
    Artista();
    Artista(int id, const string& nombre, int edad, const string& pais,
            int seguidores, int posicion);
    Artista(const Artista& otro); // Constructor de copia
    ~Artista(); // Destructor

    // Getters
    int getIdArtista() const;
    string getNombre() const;
    int getEdad() const;
    string getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionGlobal() const;
    Album** getAlbumes() const;
    int getCantidadAlbumes() const;

    // Setters
    void setIdArtista(int id);
    void setNombre(const string& nombre);
    void setEdad(int edad);
    void setPaisOrigen(const string& pais);
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
};

#endif
