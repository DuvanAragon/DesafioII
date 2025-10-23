#include "Album.h"
#include <iostream>

// Constructor por defecto
Album::Album()
    : idAlbum(0), nombre(""), selloDisquero(""), fechaLanzamiento(""),
    duracionTotal(0.0f), portadaRuta(""), puntuacion(0.0f),
    cantidadCanciones(0), capacidadCanciones(10), cantidadGeneros(0) {
    canciones = new Cancion*[capacidadCanciones];
    generos = new string[MAX_GENEROS];
}

// Constructor parametrizado
Album::Album(int id, const string& nombre, const string& sello,
             const string& fecha, const string& ruta)
    : idAlbum(id), nombre(nombre), selloDisquero(sello),
    fechaLanzamiento(fecha), duracionTotal(0.0f), portadaRuta(ruta),
    puntuacion(0.0f), cantidadCanciones(0), capacidadCanciones(10),
    cantidadGeneros(0) {
    canciones = new Cancion*[capacidadCanciones];
    generos = new string[MAX_GENEROS];
}

// Constructor de copia
Album::Album(const Album& otro)
    : idAlbum(otro.idAlbum), nombre(otro.nombre), selloDisquero(otro.selloDisquero),
    fechaLanzamiento(otro.fechaLanzamiento), duracionTotal(otro.duracionTotal),
    portadaRuta(otro.portadaRuta), puntuacion(otro.puntuacion),
    cantidadCanciones(otro.cantidadCanciones),
    capacidadCanciones(otro.capacidadCanciones),
    cantidadGeneros(otro.cantidadGeneros) {
    canciones = new Cancion*[capacidadCanciones];
    copiarCanciones(otro.canciones, otro.cantidadCanciones);

    generos = new string[MAX_GENEROS];
    copiarGeneros(otro.generos, otro.cantidadGeneros);
}

// Destructor
Album::~Album() {
    liberarCanciones();
    delete[] generos;
}

// Getters
int Album::getIdAlbum() const { return idAlbum; }
string Album::getNombre() const { return nombre; }
string Album::getSelloDisquero() const { return selloDisquero; }
string Album::getFechaLanzamiento() const { return fechaLanzamiento; }
float Album::getDuracionTotal() const { return duracionTotal; }
string Album::getPortadaRuta() const { return portadaRuta; }
string* Album::getGeneros() const { return generos; }
int Album::getCantidadGeneros() const { return cantidadGeneros; }
float Album::getPuntuacion() const { return puntuacion; }
Cancion** Album::getCanciones() const { return canciones; }
int Album::getCantidadCanciones() const { return cantidadCanciones; }

// Setters
void Album::setIdAlbum(int id) { this->idAlbum = id; }
void Album::setNombre(const string& nombre) { this->nombre = nombre; }
void Album::setSelloDisquero(const string& sello) { this->selloDisquero = sello; }
void Album::setFechaLanzamiento(const string& fecha) { this->fechaLanzamiento = fecha; }
void Album::setDuracionTotal(float duracion) { this->duracionTotal = duracion; }
void Album::setPortadaRuta(const string& ruta) { this->portadaRuta = ruta; }
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
bool Album::agregarGenero(const string& genero) {
    if (cantidadGeneros >= MAX_GENEROS) {
        return false;
    }

    // Verificar que no exista el genero
    for (int i = 0; i < cantidadGeneros; i++) {
        if (generos[i] == genero) {
            return false;
        }
    }

    generos[cantidadGeneros++] = genero;
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
        liberarCanciones();
        delete[] generos;

        idAlbum = otro.idAlbum;
        nombre = otro.nombre;
        selloDisquero = otro.selloDisquero;
        fechaLanzamiento = otro.fechaLanzamiento;
        duracionTotal = otro.duracionTotal;
        portadaRuta = otro.portadaRuta;
        puntuacion = otro.puntuacion;
        cantidadCanciones = otro.cantidadCanciones;
        capacidadCanciones = otro.capacidadCanciones;
        cantidadGeneros = otro.cantidadGeneros;

        canciones = new Cancion*[capacidadCanciones];
        copiarCanciones(otro.canciones, otro.cantidadCanciones);

        generos = new string[MAX_GENEROS];
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

void Album::copiarGeneros(const string* origen, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        generos[i] = origen[i];
    }
}
