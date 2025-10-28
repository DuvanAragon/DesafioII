#include "SistemaReproduccion.h"
#include "plataforma.h"
#include "usuario.h"

using namespace std;

// constructor y destructor
SistemaReproduccion::SistemaReproduccion()
    : plataforma(nullptr), cancionActual(nullptr), usuarioActivo(nullptr),
    estaRepitiendo(false), contadorCanciones(0),
    cantidadHistorial(0), capacidadHistorial(MAX_HISTORIAL),
    listaAnuncios(nullptr), totalAnuncios(0), ultimoAnuncio(-1) {
    historial = new Cancion*[capacidadHistorial];
}

SistemaReproduccion::~SistemaReproduccion() {
    delete[] historial;
}

// setters
void SistemaReproduccion::setPlataforma(Plataforma* p) { plataforma = p; }
void SistemaReproduccion::setUsuarioActivo(Usuario* usuario) { usuarioActivo = usuario; }
void SistemaReproduccion::setListaAnuncios(Anuncio** anuncios, int cantidad) {
    listaAnuncios = anuncios;
    totalAnuncios = cantidad;
}
void SistemaReproduccion::setCancionActual(Cancion* cancion) { cancionActual = cancion; }
void SistemaReproduccion::setEstaRepitiendo(bool repitiendo) { estaRepitiendo = repitiendo; }

// getters
Cancion* SistemaReproduccion::getCancionActual() const { return cancionActual; }
Usuario* SistemaReproduccion::getUsuarioActivo() const { return usuarioActivo; }
bool SistemaReproduccion::getEstaRepitiendo() const { return estaRepitiendo; }
int SistemaReproduccion::getContadorCanciones() const { return contadorCanciones; }
int SistemaReproduccion::getCantidadHistorial() const { return cantidadHistorial; }

// métodos principales de reproducción
void SistemaReproduccion::reproducir(Cancion* cancion) {
    if (cancion == nullptr) {
        cout << "error: no hay cancion para reproducir" << endl;
        return;
    }

    cancionActual = cancion;

    if (!estaRepitiendo) {
        cancion->incrementarReproduccion();

        bool mostrarAnuncio = false;

        agregarAlHistorial(cancion);
        contadorCanciones++;

        if (usuarioActivo &&
            !usuarioActivo->Premium() &&
            listaAnuncios &&
            totalAnuncios > 0 &&
            contadorCanciones % 2 == 0) {
            mostrarAnuncio = true;
        }

        cout << "\n==========================================================" << endl;
        cout << "=                    reproduciendo                        =" << endl;
        cout << "==========================================================" << endl << endl;

        if (mostrarAnuncio) mostrarPublicidad();
    }
    else {
        cout << "\n==========================================================" << endl;
        cout << "=                 reproduciendo (repetir)                 =" << endl;
        cout << "==========================================================" << endl << endl;
    }

    mostrarInterfaz();
}

void SistemaReproduccion::pausar() {
    cout << "\n️ Reproducción pausada" << endl;
}

void SistemaReproduccion::detener() {
    cout << "\n reproduccion detenida" << endl;
    cancionActual = nullptr;
    estaRepitiendo = false;

    if (listaReproduccionActual) {
        delete[] listaReproduccionActual;
        listaReproduccionActual = nullptr;
    }
    cantidadListaActual = 0;
    indiceListaActual = 0;
}

void SistemaReproduccion::siguienteCancion() {
    if (!plataforma) {
        cout << "Error: No hay plataforma asociada al sistema de reproduccion." << endl;
        return;
    }

    int ultimoID = (cancionActual) ? cancionActual->getIdCancion() : -1;
    Cancion* siguiente = plataforma->seleccionarCancionAleatoria(ultimoID);

    if (siguiente != nullptr) {
        reproducir(siguiente);
    } else {
        cout << "No hay mas canciones disponibles." << endl;
    }
}

Cancion* SistemaReproduccion::anterior() {
    if (cantidadHistorial < 2) {
        cout << "no hay cancion anterior." << endl;
        return nullptr;
    }

    return historial[cantidadHistorial - 2];
}

// historial
void SistemaReproduccion::agregarAlHistorial(Cancion* cancion) {
    if (cancion == nullptr) return;

    if (cantidadHistorial >= MAX_HISTORIAL) {
        for (int i = 0; i < cantidadHistorial - 1; i++) {
            historial[i] = historial[i + 1];
        }
        cantidadHistorial--;
    }

    if (cantidadHistorial >= capacidadHistorial) {
        expandirCapacidadHistorial();
    }

    historial[cantidadHistorial++] = cancion;
}

void SistemaReproduccion::limpiarHistorial() {
    for (int i = 0; i < cantidadHistorial; i++) {
        historial[i] = nullptr;
    }
    cantidadHistorial = 0;
    contadorCanciones = 0;

    if (listaReproduccionActual) {
        delete[] listaReproduccionActual;
        listaReproduccionActual = nullptr;
    }
    cantidadListaActual = 0;
    indiceListaActual = 0;
    reproduccionAleatoria = false;
}

void SistemaReproduccion::expandirCapacidadHistorial() {
    int nuevaCapacidad = capacidadHistorial * 2;
    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];
    for (int i = 0; i < cantidadHistorial; i++)
        nuevoArreglo[i] = historial[i];

    delete[] historial;
    historial = nuevoArreglo;
    capacidadHistorial = nuevaCapacidad;
}

// publicidad
void SistemaReproduccion::mostrarPublicidad() {
    if (!listaAnuncios || totalAnuncios <= 0) {
        cout << "No hay anuncios disponibles." << endl;
        return;
    }

    int indice = Anuncio::seleccionarAleatorio(listaAnuncios, totalAnuncios, ultimoAnuncio);
    if (indice == -1) return;

    cout << "\n";
    listaAnuncios[indice]->mostrar();

    ultimoAnuncio = indice;
}

// interfaz visual
void SistemaReproduccion::mostrarInterfaz() const {
    if (cancionActual == nullptr) {
        cout << "\nNo hay canción reproduciendose" << endl;
        return;
    }

    if (plataforma != nullptr) {
        int idArtista = cancionActual->getIdArtista();
        int idAlbum = cancionActual->getIdAlbum();

        Album* album = plataforma->cargarAlbum(idArtista, idAlbum);
        if (album != nullptr) {
            Artista* artista = plataforma->buscarArtista(idArtista);
            if (artista != nullptr) {
                cout << "Artista: " << artista->getNombre() << endl;
            }
            cout << "Album: " << album->getNombre() << endl;
            cout << "Portada: " << album->getPortadaRuta() << endl << endl;
            delete album;
        }
    }

    cout << "Cancion: " << cancionActual->getNombre() << endl;
    cout << "Archivos de audio: ";
    if (usuarioActivo) {
        cout << (usuarioActivo->Premium() ? cancionActual->getRuta320() : cancionActual->getRuta128()) << endl;
    }
    cout << "Duracion: " << cancionActual->getDuracion() << " segundos" << endl;
}

// lista de reproducción
void SistemaReproduccion::setListaReproduccion(Cancion** canciones, int cantidad, bool aleatorio) {
    if (listaReproduccionActual != nullptr) {
        listaReproduccionActual = nullptr;
    }

    if (canciones == nullptr || cantidad <= 0) {
        cantidadListaActual = 0;
        reproduccionAleatoria = false;
        indiceListaActual = 0;
        return;
    }

    try {
        listaReproduccionActual = new Cancion*[cantidad];

        for (int i = 0; i < cantidad; i++) {
            listaReproduccionActual[i] = nullptr;
        }

        for (int i = 0; i < cantidad; i++) {
            if (canciones[i] != nullptr) {
                listaReproduccionActual[i] = canciones[i];
            }
        }

        cantidadListaActual = cantidad;
        reproduccionAleatoria = aleatorio;
        indiceListaActual = 0;

        if (aleatorio && cantidadListaActual > 1) {
            mezclarLista();
        }

    } catch (const std::bad_alloc& e) {
        cantidadListaActual = 0;
        listaReproduccionActual = nullptr;
    } catch (const std::exception& e) {
        cantidadListaActual = 0;
        listaReproduccionActual = nullptr;
    }
}

void SistemaReproduccion::mezclarLista() {
    if (!listaReproduccionActual || cantidadListaActual <= 1) {
        return;
    }

    Cancion** listaMezclada = new Cancion*[cantidadListaActual];

    for (int i = 0; i < cantidadListaActual; i++) {
        listaMezclada[i] = listaReproduccionActual[i];
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = cantidadListaActual - 1; i > 0; i--) {
        std::uniform_int_distribution<> dist(0, i);
        int j = dist(gen);

        Cancion* temp = listaMezclada[i];
        listaMezclada[i] = listaMezclada[j];
        listaMezclada[j] = temp;
    }

    for (int i = 0; i < cantidadListaActual; i++) {
        listaReproduccionActual[i] = listaMezclada[i];
    }

    delete[] listaMezclada;
}

void SistemaReproduccion::siguienteCancionLista() {
    if (!listaReproduccionActual || cantidadListaActual == 0) return;

    indiceListaActual++;
    if (indiceListaActual >= cantidadListaActual) {
        indiceListaActual = 0;
    }

    if (listaReproduccionActual[indiceListaActual]) {
        reproducir(listaReproduccionActual[indiceListaActual]);
    }
}

void SistemaReproduccion::cancionAnteriorLista() {
    if (!hayCancionAnterior()) {
        cout << "No hay más canciones anteriores disponibles." << endl;
        return;
    }

    if (indiceListaActual > 0) {
        indiceListaActual--;
    } else {
        indiceListaActual = cantidadListaActual - 1;
    }

    if (listaReproduccionActual[indiceListaActual]) {
        reproducir(listaReproduccionActual[indiceListaActual]);
    }
}

Cancion* SistemaReproduccion::getCancionActualLista() {
    if (!listaReproduccionActual || cantidadListaActual == 0) return nullptr;
    return listaReproduccionActual[indiceListaActual];
}

bool SistemaReproduccion::haySiguienteCancion() const {
    return listaReproduccionActual && cantidadListaActual > 0;
}

bool SistemaReproduccion::hayCancionAnterior() const {
    return listaReproduccionActual && cantidadListaActual > 0;
}
