#include "Cancion.h"
#include <iostream>

// Constructor por defecto
Cancion::Cancion()
    : idCancion(0), nombre(""), duracion(0.0f), ruta128(""), ruta320(""),
    reproducciones(0), creditos(nullptr), cantidadCreditos(0), capacidadCreditos(5) {
    creditos = new Credito*[capacidadCreditos];
}

// Constructor parametrizado
Cancion::Cancion(int id, const string& nombre, float duracion,
                 const string& r128, const string& r320)
    : idCancion(id), nombre(nombre), duracion(duracion), ruta128(r128),
    ruta320(r320), reproducciones(0), cantidadCreditos(0), capacidadCreditos(5) {
    creditos = new Credito*[capacidadCreditos];
}

// Constructor de copia
Cancion::Cancion(const Cancion& otra)
    : idCancion(otra.idCancion), nombre(otra.nombre), duracion(otra.duracion),
    ruta128(otra.ruta128), ruta320(otra.ruta320),
    reproducciones(otra.reproducciones), cantidadCreditos(otra.cantidadCreditos),
    capacidadCreditos(otra.capacidadCreditos) {
    creditos = new Credito*[capacidadCreditos];
    copiarCreditos(otra.creditos, otra.cantidadCreditos);
}

// Destructor
Cancion::~Cancion() {
    liberarCreditos();
}

// Getters
int Cancion::getIdCancion() const { return idCancion; }
string Cancion::getNombre() const { return nombre; }
float Cancion::getDuracion() const { return duracion; }
string Cancion::getRuta128() const { return ruta128; }
string Cancion::getRuta320() const { return ruta320; }
int Cancion::getReproducciones() const { return reproducciones; }
Credito** Cancion::getCreditos() const { return creditos; }
int Cancion::getCantidadCreditos() const { return cantidadCreditos; }

// Setters
void Cancion::setIdCancion(int id) { this->idCancion = id; }
void Cancion::setNombre(const string& nombre) { this->nombre = nombre; }
void Cancion::setDuracion(float duracion) { this->duracion = duracion; }
void Cancion::setRuta128(const string& ruta) { this->ruta128 = ruta; }
void Cancion::setRuta320(const string& ruta) { this->ruta320 = ruta; }
void Cancion::setReproducciones(int reproducciones) { this->reproducciones = reproducciones; }

void Cancion::setCreditos(Credito** creditos, int cantidad) {
    liberarCreditos();
    this->cantidadCreditos = cantidad;
    this->capacidadCreditos = cantidad > 5 ? cantidad * 2 : 5;
    this->creditos = new Credito*[capacidadCreditos];
    copiarCreditos(creditos, cantidad);
}

// Validar ID de 9 digitos
bool Cancion::validarID() const {
    return idCancion >= 100000000 && idCancion <= 999999999;
}

// Reproducir cancion segun calidadd
void Cancion::reproducir(const string& calidad) {
    cout << "\n=== REPRODUCIENDO ===" << endl;
    cout << "Canción: " << nombre << endl;
    cout << "Duración: " << duracion << " segundos" << endl;

    if (calidad == "320") {
        cout << "Archivo: " << ruta320 << endl;
    } else {
        cout << "Archivo: " << ruta128 << endl;
    }
}

// Mostrar ambas rutas
void Cancion::mostrarRutas() const {
    cout << "Ruta 128 kbps: " << ruta128 << endl;
    cout << "Ruta 320 kbps: " << ruta320 << endl;
}

// Incrementar contador de reproducciones
void Cancion::incrementarReproduccion() {
    reproducciones++;
}

// Agregar creditoo a la cancion
void Cancion::agregarCredito(Credito* credito) {
    if (cantidadCreditos >= capacidadCreditos) {
        expandirCapacidadCreditos();
    }
    creditos[cantidadCreditos++] = credito;
}

// Sobrecarga operador de asignacion
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
        copiarCreditos(otra.creditos, otra.cantidadCreditos);
    }
    return *this;
}

// Metodos privados auxiliares
void Cancion::expandirCapacidadCreditos() {
    int nuevaCapacidad = capacidadCreditos * 2;
    Credito** nuevoArreglo = new Credito*[nuevaCapacidad];

    for (int i = 0; i < cantidadCreditos; i++) {
        nuevoArreglo[i] = creditos[i];
    }

    delete[] creditos;
    creditos = nuevoArreglo;
    capacidadCreditos = nuevaCapacidad;
}

void Cancion::copiarCreditos(Credito** origen, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        creditos[i] = new Credito(*origen[i]);
    }
}

void Cancion::liberarCreditos() {
    if (creditos != nullptr) {
        for (int i = 0; i < cantidadCreditos; i++) {
            delete creditos[i];
        }
        delete[] creditos;
        creditos = nullptr;
    }
}
