#include "sistemareproduccion.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor
SistemaReproduccion::SistemaReproduccion()
    : cancionActual(nullptr), usuarioActivo(nullptr), estaRepitiendo(false),
    contadorCanciones(0), cantidadHistorial(0), capacidadHistorial(100) {
    historial = new Cancion*[capacidadHistorial];
    srand(time(0)); // Inicializar semilla aleatoria
}

// Destructor
SistemaReproduccion::~SistemaReproduccion() {
    delete[] historial;
}

// Getters
Cancion* SistemaReproduccion::getCancionActual() const { return cancionActual; }
Usuario* SistemaReproduccion::getUsuarioActivo() const { return usuarioActivo; }
bool SistemaReproduccion::getEstaRepitiendo() const { return estaRepitiendo; }
int SistemaReproduccion::getContadorCanciones() const { return contadorCanciones; }

// Setters
void SistemaReproduccion::setCancionActual(Cancion* cancion) {
    this->cancionActual = cancion;
}

void SistemaReproduccion::setUsuarioActivo(Usuario* usuario) {
    this->usuarioActivo = usuario;
}

void SistemaReproduccion::setEstaRepitiendo(bool repitiendo) {
    this->estaRepitiendo = repitiendo;
}

// Reproducir canción
void SistemaReproduccion::reproducir(Cancion* cancion) {
    if (cancion == nullptr) {
        cout << "Error: No hay cancion para reproducir" << endl;
        return;
    }

    cancionActual = cancion;
    cancion->incrementarReproduccion();

    // Agregar al historial solo si no está en modo repetir
    if (!estaRepitiendo) {
        agregarAlHistorial(cancion);
        contadorCanciones++;
    }

    mostrarInterfaz();
}

// Pausar reproduccion
void SistemaReproduccion::pausar() {
    cout << "\n Reproduccion pausada" << endl;
}

// Detener reproduccion
void SistemaReproduccion::detener() {
    cout << "\n Reproduccion detenida" << endl;
    cancionActual = nullptr;
    estaRepitiendo = false;
}

// Siguiente cancion aleatoria
Cancion* SistemaReproduccion::siguiente(Cancion** canciones, int total) {
    if (canciones == nullptr || total <= 0) {
        return nullptr;
    }

    int indiceAleatorio = rand() % total;
    return canciones[indiceAleatorio];
}

// Cancion anterior
Cancion* SistemaReproduccion::anterior() {
    if (cantidadHistorial < 2) {
        cout << "No hay canción anterior" << endl;
        return nullptr;
    }

    // Retornar la penultima cancion (la ultima es la actual)
    return historial[cantidadHistorial - 2];
}

// Verificar si puede retroceder
bool SistemaReproduccion::puedeRetroceder(int maxRetroceso) const {
    return cantidadHistorial > 1 && (cantidadHistorial - 1) <= maxRetroceso;
}

// Agregar cancion al historial
void SistemaReproduccion::agregarAlHistorial(Cancion* cancion) {
    if (cantidadHistorial >= capacidadHistorial) {
        expandirCapacidadHistorial();
    }
    historial[cantidadHistorial++] = cancion;
}

// Limpiar historial
void SistemaReproduccion::limpiarHistorial() {
    cantidadHistorial = 0;
    contadorCanciones = 0;
}

// Expandir capacidad del historial
void SistemaReproduccion::expandirCapacidadHistorial() {
    int nuevaCapacidad = capacidadHistorial * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadHistorial; i++) {
        nuevoArreglo[i] = historial[i];
    }

    delete[] historial;
    historial = nuevoArreglo;
    capacidadHistorial = nuevaCapacidad;
}

// Mostrar publicidad (implementacion basica, se completa con clase Anuncio)
Anuncio* SistemaReproduccion::mostrarPublicidad(Anuncio** anuncios, int total) {
    if (anuncios == nullptr || total <= 0) {
        return nullptr;
    }

    // Seleccion aleatoria simple (se mejorara con prioridades)
    int indice = rand() % total;
    return anuncios[indice];
}

// Mostrar interfaz de reproduccion
void SistemaReproduccion::mostrarInterfaz() const {
    if (cancionActual == nullptr) {
        cout << "\nNo hay cancion reproduciendose" << endl;
        return;
    }

    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║       REPRODUCIENDO AHORA           ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "Cancion: " << cancionActual->getNombre() << endl;
    cout << "Duracion: " << cancionActual->getDuracion() << "s" << endl;

    if (estaRepitiendo) {
        cout << " Modo repetir: ACTIVADO" << endl;
    }

    cout << "\n Archivos:" << endl;
    cancionActual->mostrarRutas();
    cout << "════════════════════════════════════════" << endl;
}
