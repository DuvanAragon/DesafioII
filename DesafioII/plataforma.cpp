#include "Plataforma.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

// Constructor
Plataforma::Plataforma()
    : cantidadUsuarios(0), capacidadUsuarios(50),
    cantidadArtistas(0), capacidadArtistas(100),
    cantidadAnuncios(0), capacidadAnuncios(50),
    usuarioActual(nullptr) {

    usuarios = new Usuario*[capacidadUsuarios];
    artistas = new Artista*[capacidadArtistas];
    anuncios = new Anuncio*[capacidadAnuncios];
    sistemaReproduccion = new SistemaReproduccion();
    medidor = nullptr;

    srand(time(0));
}

// Destructor
Plataforma::~Plataforma() {
    // Liberar usuarios
    for (int i = 0; i < cantidadUsuarios; i++) {
        delete usuarios[i];
    }
    delete[] usuarios;

    // Liberar artistas
    for (int i = 0; i < cantidadArtistas; i++) {
        delete artistas[i];
    }
    delete[] artistas;

    // Liberar anuncios
    for (int i = 0; i < cantidadAnuncios; i++) {
        delete anuncios[i];
    }
    delete[] anuncios;

    delete sistemaReproduccion;

}

// Getters
Usuario** Plataforma::getUsuarios() const { return usuarios; }
Artista** Plataforma::getArtistas() const { return artistas; }
Anuncio** Plataforma::getAnuncios() const { return anuncios; }
SistemaReproduccion* Plataforma::getSistemaReproduccion() const { return sistemaReproduccion; }
MedidorRecursos* Plataforma::getMedidor() const { return medidor; }
int Plataforma::getCantidadUsuarios() const { return cantidadUsuarios; }
int Plataforma::getCantidadArtistas() const { return cantidadArtistas; }
int Plataforma::getCantidadAnuncios() const { return cantidadAnuncios; }
Usuario* Plataforma::getUsuarioActual() const { return usuarioActual; }

// Setters
void Plataforma::setUsuarios(Usuario** usuarios, int cantidad) {
    this->usuarios = usuarios;
    this->cantidadUsuarios = cantidad;
}

void Plataforma::setArtistas(Artista** artistas, int cantidad) {
    this->artistas = artistas;
    this->cantidadArtistas = cantidad;
}

void Plataforma::setAnuncios(Anuncio** anuncios, int cantidad) {
    this->anuncios = anuncios;
    this->cantidadAnuncios = cantidad;
}

// Login de usuario
Usuario* Plataforma::login(const string& nickname) {
    usuarioActual = encontrarUsuario(nickname);

    if (usuarioActual != nullptr) {
        cout << "\n¡Bienvenido a UdeATunes, " << nickname << "!" << endl;
        sistemaReproduccion->setUsuarioActivo(usuarioActual);
        return usuarioActual;
    } else {
        cout << "\nUsuario no encontrado" << endl;
        return nullptr;
    }
}

// Encontrar usuario por nicknamee
Usuario* Plataforma::encontrarUsuario(const string& nickname) const {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}

// Encontrar cancion por ID
Cancion* Plataforma::encontrarCancion(int id) const {
    for (int i = 0; i < cantidadArtistas; i++) {
        Cancion* cancion = artistas[i]->buscarCancionPorId(id);
        if (cancion != nullptr) {
            return cancion;
        }
    }
    return nullptr;
}

// Obtener todas las canciones de la plataforma
Cancion** Plataforma::obtenerTodasLasCanciones(int& totalCanciones) const {
    // Primero contar el total
    totalCanciones = 0;
    for (int i = 0; i < cantidadArtistas; i++) {
        Album** albumes = artistas[i]->getAlbumes();
        int cantAlbumes = artistas[i]->getCantidadAlbumes();

        for (int j = 0; j < cantAlbumes; j++) {
            totalCanciones += albumes[j]->getCantidadCanciones();
        }
    }

    // Crear arreglo y llenarlo
    Cancion** todasCanciones = new Cancion*[totalCanciones];
    int indice = 0;

    for (int i = 0; i < cantidadArtistas; i++) {
        Album** albumes = artistas[i]->getAlbumes();
        int cantAlbumes = artistas[i]->getCantidadAlbumes();

        for (int j = 0; j < cantAlbumes; j++) {
            Cancion** canciones = albumes[j]->getCanciones();
            int cantCanciones = albumes[j]->getCantidadCanciones();

            for (int k = 0; k < cantCanciones; k++) {
                todasCanciones[indice++] = canciones[k];
            }
        }
    }

    return todasCanciones;
}

// Reproduccion aleatoria
void Plataforma::reproducirAleatorio() {
    if (usuarioActual == nullptr) {
        cout << "Debe iniciar sesión primero" << endl;
        return;
    }

    int totalCanciones;
    Cancion** todasCanciones = obtenerTodasLasCanciones(totalCanciones);

    if (totalCanciones == 0) {
        cout << "No hay canciones disponibles" << endl;
        delete[] todasCanciones;
        return;
    }

    cout << "\n Iniciando reproducción aleatoria..." << endl;
    cout << "Total de canciones disponibles: " << totalCanciones << endl;

    // Reproducir canciones (limitado a 5 para testing)
    const int MAX_CANCIONES = 5;
    for (int i = 0; i < MAX_CANCIONES; i++) {
        Cancion* cancionAleatoria = sistemaReproduccion->siguiente(todasCanciones, totalCanciones);

        if (cancionAleatoria != nullptr) {
            cout << "\n[" << (i+1) << "/" << MAX_CANCIONES << "]" << endl;
            sistemaReproduccion->reproducir(cancionAleatoria);

            // Simular reproducción de 3 segundos
            cout << "\n Reproduciendo... (simulando 3 segundos)" << endl;
            // En implementacion real: usar std::this_thread::sleep_for
        }

        // Mostrar publicidad cada 2 canciones para usuarios estandar
        if ((i + 1) % 2 == 0 && !usuarioActual->Premium()) {
            cout << "\n PUBLICIDAD " << endl;
            Anuncio* anuncio = sistemaReproduccion->mostrarPublicidad(anuncios, cantidadAnuncios);
            if (anuncio != nullptr) {
                // anuncio->mostrarAnuncio();
            }
        }
    }

    sistemaReproduccion->detener();
    delete[] todasCanciones;
}

// Medicion de recursos
void Plataforma::medirRecursos(const string& funcionalidad) {
    if (medidor != nullptr) {
        // medidor->mostrarMetricas(funcionalidad); // Implementado por compañero
        cout << "\n📊 Métricas de " << funcionalidad << " se mostrarían aquí" << endl;
    }
}

// Sobrecarga operador ==
bool Plataforma::operator==(const Plataforma& otra) const {
    return this->cantidadUsuarios == otra.cantidadUsuarios &&
           this->cantidadArtistas == otra.cantidadArtistas;
}

// Agregar usuario
void Plataforma::agregarUsuario(Usuario* usuario) {
    if (cantidadUsuarios >= capacidadUsuarios) {
        expandirCapacidadUsuarios();
    }
    usuarios[cantidadUsuarios++] = usuario;
}

// Agregar artista
void Plataforma::agregarArtista(Artista* artista) {
    if (cantidadArtistas >= capacidadArtistas) {
        expandirCapacidadArtistas();
    }
    artistas[cantidadArtistas++] = artista;
}

// Agregar anuncio
void Plataforma::agregarAnuncio(Anuncio* anuncio) {
    if (cantidadAnuncios >= capacidadAnuncios) {
        expandirCapacidadAnuncios();
    }
    anuncios[cantidadAnuncios++] = anuncio;
}

// Expansion de capacidades
void Plataforma::expandirCapacidadUsuarios() {
    int nuevaCapacidad = capacidadUsuarios * 2;
    Usuario** nuevoArreglo = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; i++) {
        nuevoArreglo[i] = usuarios[i];
    }

    delete[] usuarios;
    usuarios = nuevoArreglo;
    capacidadUsuarios = nuevaCapacidad;
}

void Plataforma::expandirCapacidadArtistas() {
    int nuevaCapacidad = capacidadArtistas * 2;
    Artista** nuevoArreglo = new Artista*[nuevaCapacidad];

    for (int i = 0; i < cantidadArtistas; i++) {
        nuevoArreglo[i] = artistas[i];
    }

    delete[] artistas;
    artistas = nuevoArreglo;
    capacidadArtistas = nuevaCapacidad;
}

void Plataforma::expandirCapacidadAnuncios() {
    int nuevaCapacidad = capacidadAnuncios * 2;
    Anuncio** nuevoArreglo = new Anuncio*[nuevaCapacidad];

    for (int i = 0; i < cantidadAnuncios; i++) {
        nuevoArreglo[i] = anuncios[i];
    }

    delete[] anuncios;
    anuncios = nuevoArreglo;
    capacidadAnuncios = nuevaCapacidad;
}
