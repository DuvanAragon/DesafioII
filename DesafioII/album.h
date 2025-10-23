#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Cancion.h"
using namespace std;

/*
 * Clase Album: Representa un album musical
 * Gestiona canciones, generos y metadatos del album
 */
class Album {
private:
    int idAlbum;
    string nombre;
    string selloDisquero;
    string fechaLanzamiento;
    float duracionTotal; // en segundos
    string portadaRuta; // ruta a imagen PNG
    string* generos; // Maximo 4 generos
    float puntuacion; // 1 a 10

    Cancion** canciones; // Arreglo dinamico de canciones
    int cantidadCanciones;
    int capacidadCanciones;
    int cantidadGeneros;
    static const int MAX_GENEROS = 4;

public:
    // Constructores
    Album();
    Album(int id, const string& nombre, const string& sello,
          const string& fecha, const string& ruta);
    Album(const Album& otro); // Constructor de copia
    ~Album(); // Destructor

    // Getters
    int getIdAlbum() const;
    string getNombre() const;
    string getSelloDisquero() const;
    string getFechaLanzamiento() const;
    float getDuracionTotal() const;
    string getPortadaRuta() const;
    string* getGeneros() const;
    int getCantidadGeneros() const;
    float getPuntuacion() const;
    Cancion** getCanciones() const;
    int getCantidadCanciones() const;

    // Setters
    void setIdAlbum(int id);
    void setNombre(const string& nombre);
    void setSelloDisquero(const string& sello);
    void setFechaLanzamiento(const string& fecha);
    void setDuracionTotal(float duracion);
    void setPortadaRuta(const string& ruta);
    void setPuntuacion(float puntuacion);
    void setCanciones(Cancion** canciones, int cantidad);

    // Metodos funcionales
    void agregarCancion(Cancion* cancion);
    bool agregarGenero(const string& genero);
    void calcularDuracion();
    void mostrarPortada() const;

    // Sobrecarga de operador
    Album& operator=(const Album& otro);

private:
    void expandirCapacidadCanciones();
    void copiarCanciones(Cancion** origen, int cantidad);
    void liberarCanciones();
    void copiarGeneros(const string* origen, int cantidad);
};

#endif
