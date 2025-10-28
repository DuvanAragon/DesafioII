#ifndef ALBUM_H
#define ALBUM_H

#include "Cancion.h"

class Album {
private:
    // datos básicos del álbum
    int idAlbum;
    char* nombre;
    char* selloDisquero;
    char* fechaLanzamiento;
    float duracionTotal;
    char* portadaRuta;
    float puntuacion;

    // gestión de géneros
    char** generos;
    int cantidadGeneros;
    static const int MAX_GENEROS = 4;

    // gestión de canciones
    Cancion** canciones;
    int cantidadCanciones;
    int capacidadCanciones;

public:
    // constructores y destructor
    Album();
    Album(int id, const char* nombre, const char* sello,
          const char* fecha, const char* ruta);
    Album(const Album& otro);
    ~Album();

    // getters
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

    // setters
    void setIdAlbum(int id);
    void setNombre(const char* nombre);
    void setSelloDisquero(const char* sello);
    void setFechaLanzamiento(const char* fecha);
    void setDuracionTotal(float duracion);
    void setPortadaRuta(const char* ruta);
    void setPuntuacion(float puntuacion);
    void setCanciones(Cancion** canciones, int cantidad);

    // métodos funcionales
    void agregarCancion(Cancion* cancion);
    bool agregarGenero(const char* genero);
    void calcularDuracion();
    void mostrarPortada() const;

    // operador
    Album& operator=(const Album& otro);

private:
    // gestión de canciones
    void expandirCapacidadCanciones();
    void copiarCanciones(Cancion** origen, int cantidad);
    void liberarCanciones();

    // gestión de géneros
    void copiarGeneros(char** origen, int cantidad);
    void liberarGeneros();

    // gestión de cadenas
    char* copiarCadena(const char* origen);
    void liberarCadena(char*& cadena);
    int longitudCadena(const char* cadena) const;
    bool compararCadenas(const char* cad1, const char* cad2) const;
};

#endif
