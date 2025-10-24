#include "Album.h"
#include <iostream>
using namespace std;

// Constructor por defecto
Album::Album()
    : idAlbum(0), nombre(nullptr), selloDisquero(nullptr), fechaLanzamiento(nullptr),
    duracionTotal(0.0f), portadaRuta(nullptr), puntuacion(0.0f),
    cantidadCanciones(0), capacidadCanciones(10), cantidadGeneros(0) {
    canciones = new Cancion*[capacidadCanciones];
    generos = new char*[MAX_GENEROS];
    for (int i = 0; i < MAX_GENEROS; i++) {
        generos[i] = nullptr;
    }
}

// Constructor parametrizado
Album::Album(int id, const char* nombre, const char* sello,
             const char* fecha, const char* ruta)
    : idAlbum(id), duracionTotal(0.0f), puntuacion(0.0f),
    cantidadCanciones(0), capacidadCanciones(10), cantidadGeneros(0) {
    this->nombre = copiarCadena(nombre);
    this->selloDisquero = copiarCadena(sello);
    this->fechaLanzamiento = copiarCadena(fecha);
    this->portadaRuta = copiarCadena(ruta);

    canciones = new Cancion*[capacidadCanciones];
    generos = new char*[MAX_GENEROS];
    for (int i = 0; i < MAX_GENEROS; i++) {
        generos[i] = nullptr;
    }
}

// Constructor de copia
Album::Album(const Album& otro)
    : idAlbum(otro.idAlbum), duracionTotal(otro.duracionTotal),
    puntuacion(otro.puntuacion), cantidadCanciones(otro.cantidadCanciones),
    capacidadCanciones(otro.capacidadCanciones), cantidadGeneros(otro.cantidadGeneros) {

    nombre = copiarCadena(otro.nombre);
    selloDisquero = copiarCadena(otro.selloDisquero);
    fechaLanzamiento = copiarCadena(otro.fechaLanzamiento);
    portadaRuta = copiarCadena(otro.portadaRuta);

    canciones = new Cancion*[capacidadCanciones];
    copiarCanciones(otro.canciones, otro.cantidadCanciones);

    generos = new char*[MAX_GENEROS];
    for (int i = 0; i < MAX_GENEROS; i++) {
        generos[i] = nullptr;
    }
    copiarGeneros(otro.generos, otro.cantidadGeneros);
}

// Destructor
Album::~Album() {
    liberarCadena(nombre);
    liberarCadena(selloDisquero);
    liberarCadena(fechaLanzamiento);
    liberarCadena(portadaRuta);
    liberarCanciones();
    liberarGeneros();
}

// Getters
int Album::getIdAlbum() const { return idAlbum; }
const char* Album::getNombre() const { return nombre; }
const char* Album::getSelloDisquero() const { return selloDisquero; }
const char* Album::getFechaLanzamiento() const { return fechaLanzamiento; }
float Album::getDuracionTotal() const { return duracionTotal; }
const char* Album::getPortadaRuta() const { return portadaRuta; }
char** Album::getGeneros() const { return generos; }
int Album::getCantidadGeneros() const { return cantidadGeneros; }
float Album::getPuntuacion() const { return puntuacion; }
Cancion** Album::getCanciones() const { return canciones; }
int Album::getCantidadCanciones() const { return cantidadCanciones; }

// Setters
void Album::setIdAlbum(int id) { this->idAlbum = id; }

void Album::setNombre(const char* nombre) {
    liberarCadena(this->nombre);
    this->nombre = copiarCadena(nombre);
}

void Album::setSelloDisquero(const char* sello) {
    liberarCadena(this->selloDisquero);
    this->selloDisquero = copiarCadena(sello);
}

void Album::setFechaLanzamiento(const char* fecha) {
    liberarCadena(this->fechaLanzamiento);
    this->fechaLanzamiento = copiarCadena(fecha);
}

void Album::setDuracionTotal(float duracion) { this->duracionTotal = duracion; }

void Album::setPortadaRuta(const char* ruta) {
    liberarCadena(this->portadaRuta);
    this->portadaRuta = copiarCadena(ruta);
}

void Album::setPuntuacion(float puntuacion) { this->puntuacion = puntuacion; }

void Album::setCanciones(Cancion** canciones, int cantidad) {
    liberarCanciones();
    this->cantidadCanciones = cantidad;
    this->capacidadCanciones = cantidad > 10 ? cantidad * 2 : 10;
    this->canciones = new Cancion*[capacidadCanciones];
    copiarCanciones(canciones, cantidad);
}

// Agregar cancionn al album
void Album::agregarCancion(Cancion* cancion) {
    if (cantidadCanciones >= capacidadCanciones) {
        expandirCapacidadCanciones();
    }
    canciones[cantidadCanciones++] = cancion;
    calcularDuracion();
}

// Agregar generoo (maximo 4)
bool Album::agregarGenero(const char* genero) {
    if (cantidadGeneros >= MAX_GENEROS) {
        return false;
    }

    // Verificar que no exista el genero
    for (int i = 0; i < cantidadGeneros; i++) {
        if (compararCadenas(generos[i], genero)) {
            return false;
        }
    }

    generos[cantidadGeneros++] = copiarCadena(genero);
    return true;
}

// Calcular duracion total del album
void Album::calcularDuracion() {
    duracionTotal = 0.0f;
    for (int i = 0; i < cantidadCanciones; i++) {
        duracionTotal += canciones[i]->getDuracion();
    }
}

// Mostrar ruta de la portada
void Album::mostrarPortada() const {
    cout << "Portada: " << portadaRuta << endl;
}

// Sobrecarga operador de asignacion
Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        liberarCadena(nombre);
        liberarCadena(selloDisquero);
        liberarCadena(fechaLanzamiento);
        liberarCadena(portadaRuta);
        liberarCanciones();
        liberarGeneros();

        idAlbum = otro.idAlbum;
        duracionTotal = otro.duracionTotal;
        puntuacion = otro.puntuacion;
        cantidadCanciones = otro.cantidadCanciones;
        capacidadCanciones = otro.capacidadCanciones;
        cantidadGeneros = otro.cantidadGeneros;

        nombre = copiarCadena(otro.nombre);
        selloDisquero = copiarCadena(otro.selloDisquero);
        fechaLanzamiento = copiarCadena(otro.fechaLanzamiento);
        portadaRuta = copiarCadena(otro.portadaRuta);

        canciones = new Cancion*[capacidadCanciones];
        copiarCanciones(otro.canciones, otro.cantidadCanciones);

        generos = new char*[MAX_GENEROS];
        for (int i = 0; i < MAX_GENEROS; i++) {
            generos[i] = nullptr;
        }
        copiarGeneros(otro.generos, otro.cantidadGeneros);
    }
    return *this;
}

// Metodos privados auxiliares
void Album::expandirCapacidadCanciones() {
    int nuevaCapacidad = capacidadCanciones * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadCanciones; i++) {
        nuevoArreglo[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevoArreglo;
    capacidadCanciones = nuevaCapacidad;
}

void Album::copiarCanciones(Cancion** origen, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        canciones[i] = new Cancion(*origen[i]);
    }
}

void Album::liberarCanciones() {
    if (canciones != nullptr) {
        for (int i = 0; i < cantidadCanciones; i++) {
            delete canciones[i];
        }
        delete[] canciones;
        canciones = nullptr;
    }
}

void Album::copiarGeneros(char** origen, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        generos[i] = copiarCadena(origen[i]);
    }
}

void Album::liberarGeneros() {
    if (generos != nullptr) {
        for (int i = 0; i < MAX_GENEROS; i++) {
            liberarCadena(generos[i]);
        }
        delete[] generos;
        generos = nullptr;
    }
}

// Funciones auxiliares para manejo de cadenas
char* Album::copiarCadena(const char* origen) {
    if (origen == nullptr) return nullptr;

    int longitud = longitudCadena(origen);
    char* copia = new char[longitud + 1];

    for (int i = 0; i < longitud; i++) {
        copia[i] = origen[i];
    }
    copia[longitud] = '\0';

    return copia;
}

void Album::liberarCadena(char*& cadena) {
    if (cadena != nullptr) {
        delete[] cadena;
        cadena = nullptr;
    }
}

int Album::longitudCadena(const char* cadena) const {
    if (cadena == nullptr) return 0;

    int longitud = 0;
    while (cadena[longitud] != '\0') {
        longitud++;
    }
    return longitud;
}

bool Album::compararCadenas(const char* cad1, const char* cad2) const {
    if (cad1 == nullptr || cad2 == nullptr) return false;

    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0') {
        if (cad1[i] != cad2[i]) return false;
        i++;
    }

    return cad1[i] == '\0' && cad2[i] == '\0';
}
