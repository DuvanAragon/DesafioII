#ifndef SISTEMA_REPRODUCCION_H
#define SISTEMA_REPRODUCCION_H

#include "Cancion.h"

// Forward declarations para evitar dependencias circulares
class Usuario;
class Anuncio;

/*
 * Clase SistemaReproduccion: Gestiona la reproducción de canciones
 * Controla historial, repetición y publicidad
 */
class SistemaReproduccion {
private:
    Cancion* cancionActual;
    Cancion** historial; // Historial de canciones reproducidas
    Usuario* usuarioActivo;
    bool estaRepitiendo;
    int contadorCanciones; // Contador para publicidad
    int cantidadHistorial;
    int capacidadHistorial;

public:
    // Constructores
    SistemaReproduccion();
    ~SistemaReproduccion();

    // Getters
    Cancion* getCancionActual() const;
    Usuario* getUsuarioActivo() const;
    bool getEstaRepitiendo() const;
    int getContadorCanciones() const;
    int getCantidadHistorial() const;

    // Setters
    void setCancionActual(Cancion* cancion);
    void setUsuarioActivo(Usuario* usuario);
    void setEstaRepitiendo(bool repitiendo);

    // Metodos de control de reproduccion
    void reproducir(Cancion* cancion);
    void pausar();
    void detener();
    Cancion* siguiente(Cancion** canciones, int total);
    Cancion* anterior();
    bool puedeRetroceder(int maxRetroceso) const;

    // Gestion de historial
    void agregarAlHistorial(Cancion* cancion);
    void limpiarHistorial();

    // Publicidad
    Anuncio* mostrarPublicidad(Anuncio** anuncios, int total);

    // Interfaz
    void mostrarInterfaz() const;

private:
    void expandirCapacidadHistorial();
};

#endif
