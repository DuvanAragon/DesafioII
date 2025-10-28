#ifndef SISTEMAREPRODUCCION_H
#define SISTEMAREPRODUCCION_H

#include <iostream>
#include "cancion.h"
#include "anuncios.h"

class Usuario;
class Plataforma;

class SistemaReproduccion {
private:
    // atributos principales
    Plataforma* plataforma;
    Cancion* cancionActual;
    Usuario* usuarioActivo;
    bool estaRepitiendo;
    int contadorCanciones;

    // historial de reproducción
    Cancion** historial;
    int cantidadHistorial;
    int capacidadHistorial;
    static const int MAX_HISTORIAL = 4;

    // sistema de anuncios
    Anuncio** listaAnuncios;
    int totalAnuncios;
    int ultimoAnuncio;

    // lista de reproducción
    Cancion** listaReproduccionActual;
    int cantidadListaActual;
    int indiceListaActual;
    bool reproduccionAleatoria;

    void expandirCapacidadHistorial();


public:
    // constructor y destructor
    SistemaReproduccion();
    ~SistemaReproduccion();

    // configuración
    void setPlataforma(Plataforma* p);
    void setUsuarioActivo(Usuario* usuario);
    void setListaAnuncios(Anuncio** anuncios, int cantidad);
    void setCancionActual(Cancion* cancion);
    void setEstaRepitiendo(bool repitiendo);

    // getters
    Cancion* getCancionActual() const;
    Usuario* getUsuarioActivo() const;
    bool getEstaRepitiendo() const;
    int getContadorCanciones() const;
    int getCantidadHistorial() const;

    // reproducción básica
    void reproducir(Cancion* cancion);
    void pausar();
    void detener();
    void siguienteCancion();
    Cancion* anterior();

    // historial
    void agregarAlHistorial(Cancion* cancion);
    void limpiarHistorial();

    // publicidad
    void mostrarPublicidad();

    // interfaz visual
    void mostrarInterfaz() const;

    // lista de reproducción
    void setListaReproduccion(Cancion** canciones, int cantidad, bool aleatorio = false);
    void siguienteCancionLista();
    void cancionAnteriorLista();
    Cancion* getCancionActualLista();
    bool haySiguienteCancion() const;
    bool hayCancionAnterior() const;
    void mezclarLista();

};

#endif
