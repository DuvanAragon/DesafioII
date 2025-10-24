#ifndef ALBUM_H
#define ALBUM_H

#include "Cancion.h"

/*
 * Clase Album: Representa un álbum musical
 * Gestiona canciones, géneros y metadatos del álbum
 */
class Album {
private:
    int idAlbum;
    char* nombre;
    char* selloDisquero;
    char* fechaLanzamiento;
    float duracionTotal; // en segundos
    char* portadaRuta; // ruta a imagen PNG
    char** generos; // Arreglo de char* para maximo 4 generos
    float puntuacion; // 1 a 10

    Cancion** canciones; // Arreglo dinamico de canciones
    int cantidadCanciones;
    int capacidadCanciones;
    int cantidadGeneros;
    static const int MAX_GENEROS = 4;

public:
    // Constructores
    Album();
    Album(int id, const char* nombre, const char* sello,
          const char* fecha, const char* ruta);
    Album(const Album& otro); // Constructor de copia
    ~Album(); // Destructor

    // Getters
    int getIdAlbum() const;
    const char* getNombre() const;
    const char* getSelloDisquero() const;
    const char* getFechaLanzamiento() const;
    float getDuracionTotal() const;
    const char* getPortadaRuta() const;
    char** getGeneros() const;
    int getCantidadGeneros() const;
    float getPuntuacion() const;
    Cancion** getCanciones() const;
    int getCantidadCanciones() const;

    // Setters
    void setIdAlbum(int id);
    void setNombre(const char* nombre);
    void setSelloDisquero(const char* sello);
    void setFechaLanzamiento(const char* fecha);
    void setDuracionTotal(float duracion);
    void setPortadaRuta(const char* ruta);
    void setPuntuacion(float puntuacion);
    void setCanciones(Cancion** canciones, int cantidad);

    // Metodos funcionales
    void agregarCancion(Cancion* cancion);
    bool agregarGenero(const char* genero);
    void calcularDuracion();
    void mostrarPortada() const;

    // Sobrecarga de operador
    Album& operator=(const Album& otro);

private:
    void expandirCapacidadCanciones();
    void copiarCanciones(Cancion** origen, int cantidad);
    void liberarCanciones();
    void copiarGeneros(char** origen, int cantidad);
    void liberarGeneros();

    // Funciones auxiliares para manejo de cadenas
    char* copiarCadena(const char* origen);
    void liberarCadena(char*& cadena);
    int longitudCadena(const char* cadena) const;
    bool compararCadenas(const char* cad1, const char* cad2) const;
};

#endif
