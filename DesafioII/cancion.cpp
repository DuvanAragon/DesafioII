#include "Cancion.h"
#include <iostream>

// constructores y destructor
Cancion::Cancion()
    : idCancion(0), nombre(""), duracion(0.0f), ruta128(""), ruta320(""),
    reproducciones(0), cantidadCreditos(0), capacidadCreditos(5)
{
    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; i++)
        creditos[i] = nullptr;
}

Cancion::Cancion(int id, const string& nombre, float duracion,
                 const string& r128, const string& r320)
    : idCancion(id), nombre(nombre), duracion(duracion),
    ruta128(r128), ruta320(r320), reproducciones(0),
    cantidadCreditos(0), capacidadCreditos(5)
{
    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; i++)
        creditos[i] = nullptr;
}

Cancion::Cancion(const Cancion& otra)
    : idCancion(otra.idCancion), nombre(otra.nombre), duracion(otra.duracion),
    ruta128(otra.ruta128), ruta320(otra.ruta320),
    reproducciones(otra.reproducciones), cantidadCreditos(otra.cantidadCreditos),
    capacidadCreditos(otra.capacidadCreditos)
{
    creditos = new Credito*[capacidadCreditos];
    for (int i = 0; i < capacidadCreditos; i++)
        creditos[i] = nullptr;

    copiarCreditos(otra.creditos, otra.cantidadCreditos);
}

Cancion::~Cancion() {
    liberarCreditos();
}

// getters
int Cancion::getIdCancion() const { return idCancion; }
string Cancion::getNombre() const { return nombre; }
float Cancion::getDuracion() const { return duracion; }
string Cancion::getRuta128() const { return ruta128; }
string Cancion::getRuta320() const { return ruta320; }
int Cancion::getReproducciones() const { return reproducciones; }
Credito** Cancion::getCreditos() const { return creditos; }
int Cancion::getCantidadCreditos() const { return cantidadCreditos; }

// setters
void Cancion::setIdCancion(int id) { idCancion = id; }
void Cancion::setNombre(const string& nombre) { this->nombre = nombre; }
void Cancion::setDuracion(float duracion) { this->duracion = duracion; }
void Cancion::setRuta128(const string& ruta) { ruta128 = ruta; }
void Cancion::setRuta320(const string& ruta) { ruta320 = ruta; }
void Cancion::setReproducciones(int reproducciones) { this->reproducciones = reproducciones; }

void Cancion::setCreditos(Credito** nuevosCreditos, int cantidad) {
    liberarCreditos();
    cantidadCreditos = cantidad;
    capacidadCreditos = (cantidad > 5 ? cantidad * 2 : 5);
    creditos = new Credito*[capacidadCreditos];

    for (int i = 0; i < capacidadCreditos; i++)
        creditos[i] = nullptr;

    copiarCreditos(nuevosCreditos, cantidad);
}

// métodos funcionales
bool Cancion::validarID() const {
    return idCancion >= 100000000 && idCancion <= 999999999;
}

void Cancion::reproducir(const string& calidad) {
    std::cout << "\n=== REPRODUCIENDO ===" << std::endl;
    std::cout << "Canción: " << nombre << std::endl;
    std::cout << "Duración: " << duracion << " segundos" << std::endl;
    std::cout << "Archivo: " << (calidad == "320" ? ruta320 : ruta128) << std::endl;
}

void Cancion::incrementarReproduccion() {
    reproducciones++;
}

void Cancion::agregarCredito(Credito* credito) {
    if (cantidadCreditos >= capacidadCreditos)
        expandirCapacidadCreditos();

    creditos[cantidadCreditos++] = credito;
}

// operador de asignación
Cancion& Cancion::operator=(const Cancion& otra) {
    if (this != &otra) {
        liberarCreditos();

        idCancion = otra.idCancion;
        nombre = otra.nombre;
        duracion = otra.duracion;
        ruta128 = otra.ruta128;
        ruta320 = otra.ruta320;
        reproducciones = otra.reproducciones;
        cantidadCreditos = otra.cantidadCreditos;
        capacidadCreditos = otra.capacidadCreditos;

        creditos = new Credito*[capacidadCreditos];
        for (int i = 0; i < capacidadCreditos; i++)
            creditos[i] = nullptr;

        copiarCreditos(otra.creditos, otra.cantidadCreditos);
    }
    return *this;
}

// métodos de extracción de IDs
int Cancion::getIdArtista() const {
    return idCancion / 10000;
}

int Cancion::getIdAlbum() const {
    return (idCancion % 10000) / 100;
}

int Cancion::getIdCancionIndividual() const {
    return idCancion % 100;
}

// métodos auxiliares
void Cancion::expandirCapacidadCreditos() {
    int nuevaCapacidad = capacidadCreditos * 2;
    Credito** nuevoArreglo = new Credito*[nuevaCapacidad];

    for (int i = 0; i < nuevaCapacidad; i++)
        nuevoArreglo[i] = (i < cantidadCreditos ? creditos[i] : nullptr);

    delete[] creditos;
    creditos = nuevoArreglo;
    capacidadCreditos = nuevaCapacidad;
}

void Cancion::copiarCreditos(Credito** origen, int cantidad) {
    for (int i = 0; i < cantidad; i++)
        creditos[i] = new Credito(*origen[i]);
}

void Cancion::liberarCreditos() {
    for (int i = 0; i < cantidadCreditos; i++)
        delete creditos[i];

    delete[] creditos;
    creditos = nullptr;
}
