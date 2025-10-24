#include "Artista.h"
#include <iostream>
using namespace std;

// Constructor por defecto
Artista::Artista()
    : idArtista(0), nombre(nullptr), edad(0), paisOrigen(nullptr),
    seguidores(0), posicionGlobal(0), cantidadAlbumes(0), capacidadAlbumes(5) {
    albumes = new Album*[capacidadAlbumes];
}

// Constructor parametrizado
Artista::Artista(int id, const char* nombre, int edad, const char* pais,
                 int seguidores, int posicion)
    : idArtista(id), edad(edad), seguidores(seguidores),
    posicionGlobal(posicion), cantidadAlbumes(0), capacidadAlbumes(5) {
    this->nombre = copiarCadena(nombre);
    this->paisOrigen = copiarCadena(pais);
    albumes = new Album*[capacidadAlbumes];
}

// Constructor de copia
Artista::Artista(const Artista& otro)
    : idArtista(otro.idArtista), edad(otro.edad), seguidores(otro.seguidores),
    posicionGlobal(otro.posicionGlobal), cantidadAlbumes(otro.cantidadAlbumes),
    capacidadAlbumes(otro.capacidadAlbumes) {
    nombre = copiarCadena(otro.nombre);
    paisOrigen = copiarCadena(otro.paisOrigen);
    albumes = new Album*[capacidadAlbumes];
    copiarAlbumes(otro.albumes, otro.cantidadAlbumes);
}

// Destructor
Artista::~Artista() {
    liberarCadena(nombre);
    liberarCadena(paisOrigen);
    liberarAlbumes();
}

// Getters
int Artista::getIdArtista() const { return idArtista; }
const char* Artista::getNombre() const { return nombre; }
int Artista::getEdad() const { return edad; }
const char* Artista::getPaisOrigen() const { return paisOrigen; }
int Artista::getSeguidores() const { return seguidores; }
int Artista::getPosicionGlobal() const { return posicionGlobal; }
Album** Artista::getAlbumes() const { return albumes; }
int Artista::getCantidadAlbumes() const { return cantidadAlbumes; }

// Setters
void Artista::setIdArtista(int id) { this->idArtista = id; }

void Artista::setNombre(const char* nombre) {
    liberarCadena(this->nombre);
    this->nombre = copiarCadena(nombre);
}

void Artista::setEdad(int edad) { this->edad = edad; }

void Artista::setPaisOrigen(const char* pais) {
    liberarCadena(this->paisOrigen);
    this->paisOrigen = copiarCadena(pais);
}

void Artista::setSeguidores(int seguidores) { this->seguidores = seguidores; }

void Artista::setPosicionGlobal(int posicion) { this->posicionGlobal = posicion; }

void Artista::setAlbumes(Album** albumes, int cantidad) {
    liberarAlbumes();
    this->cantidadAlbumes = cantidad;
    this->capacidadAlbumes = cantidad > 5 ? cantidad * 2 : 5;
    this->albumes = new Album*[capacidadAlbumes];
    copiarAlbumes(albumes, cantidad);
}

// Agregar albumm al catalogo
void Artista::agregarAlbum(Album* album) {
    if (cantidadAlbumes >= capacidadAlbumes) {
        expandirCapacidadAlbumes();
    }
    albumes[cantidadAlbumes++] = album;
}

// Mostrar informacion del artista
void Artista::mostrarInformacion() const {
    cout << "\n=== INFORMACIÓN DEL ARTISTA ===" << endl;
    cout << "ID: " << idArtista << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << " años" << endl;
    cout << "País: " << paisOrigen << endl;
    cout << "Seguidores: " << seguidores << endl;
    cout << "Posición Global: #" << posicionGlobal << endl;
    cout << "Cantidad de Álbumes: " << cantidadAlbumes << endl;
}

// Buscar cancion por ID en todos los albumes
Cancion* Artista::buscarCancionPorId(int idCancion) const {
    for (int i = 0; i < cantidadAlbumes; i++) {
        Cancion** canciones = albumes[i]->getCanciones();
        int total = albumes[i]->getCantidadCanciones();

        for (int j = 0; j < total; j++) {
            if (canciones[j]->getIdCancion() == idCancion) {
                return canciones[j];
            }
        }
    }
    return nullptr;
}

// Sobrecarga operador de asignacion
Artista& Artista::operator=(const Artista& otro) {
    if (this != &otro) {
        liberarCadena(nombre);
        liberarCadena(paisOrigen);
        liberarAlbumes();

        idArtista = otro.idArtista;
        edad = otro.edad;
        seguidores = otro.seguidores;
        posicionGlobal = otro.posicionGlobal;
        cantidadAlbumes = otro.cantidadAlbumes;
        capacidadAlbumes = otro.capacidadAlbumes;

        nombre = copiarCadena(otro.nombre);
        paisOrigen = copiarCadena(otro.paisOrigen);

        albumes = new Album*[capacidadAlbumes];
        copiarAlbumes(otro.albumes, otro.cantidadAlbumes);
    }
    return *this;
}

// Metodos privados auxiliares
void Artista::expandirCapacidadAlbumes() {
    int nuevaCapacidad = capacidadAlbumes * 2;
    Album** nuevoArreglo = new Album*[nuevaCapacidad];

    for (int i = 0; i < cantidadAlbumes; i++) {
        nuevoArreglo[i] = albumes[i];
    }

    delete[] albumes;
    albumes = nuevoArreglo;
    capacidadAlbumes = nuevaCapacidad;
}

void Artista::copiarAlbumes(Album** origen, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        albumes[i] = new Album(*origen[i]);
    }
}

void Artista::liberarAlbumes() {
    if (albumes != nullptr) {
        for (int i = 0; i < cantidadAlbumes; i++) {
            delete albumes[i];
        }
        delete[] albumes;
        albumes = nullptr;
    }
}

// Funciones auxiliares para manejo de cadenas
char* Artista::copiarCadena(const char* origen) {
    if (origen == nullptr) return nullptr;

    int longitud = longitudCadena(origen);
    char* copia = new char[longitud + 1];

    for (int i = 0; i < longitud; i++) {
        copia[i] = origen[i];
    }
    copia[longitud] = '\0';

    return copia;
}

void Artista::liberarCadena(char*& cadena) {
    if (cadena != nullptr) {
        delete[] cadena;
        cadena = nullptr;
    }
}

int Artista::longitudCadena(const char* cadena) const {
    if (cadena == nullptr) return 0;

    int longitud = 0;
    while (cadena[longitud] != '\0') {
        longitud++;
    }
    return longitud;
}
