#include "listaFavoritos.h"
#include "Usuario.h"
#include "Cancion.h"

// constructores y destructor
ListaFavoritos::ListaFavoritos() {
    capacidadCanciones = 10;
    cantidadCanciones = 0;
    canciones = new Cancion*[capacidadCanciones];
    for(int i = 0; i < capacidadCanciones; i++) canciones[i] = nullptr;

    capacidadListasSeguidas = 5;
    cantidadListasSeguidas = 0;
    listasSeguidas = new ListaFavoritos*[capacidadListasSeguidas];
    for(int i = 0; i < capacidadListasSeguidas; i++) listasSeguidas[i] = nullptr;

    usuarioPropietario = nullptr;
}

ListaFavoritos::ListaFavoritos(Usuario* _usuario) : ListaFavoritos() {
    usuarioPropietario = _usuario;
}

ListaFavoritos::~ListaFavoritos() {
    delete[] canciones;
    delete[] listasSeguidas;
}

// getters
Cancion** ListaFavoritos::getCanciones() { return canciones; }
int ListaFavoritos::getCantidadCanciones() { return cantidadCanciones; }
ListaFavoritos** ListaFavoritos::getListasSeguidas() { return listasSeguidas; }
Usuario* ListaFavoritos::getUsuarioPropietario() { return usuarioPropietario; }
int ListaFavoritos::getCantidadListasSeguidas() const { return cantidadListasSeguidas; }

// redimensionamiento
void ListaFavoritos::redimensionarCanciones() {
    int nuevaCapacidad = capacidadCanciones * 2;
    Cancion** nuevo = new Cancion*[nuevaCapacidad];

    for(int i = 0; i < cantidadCanciones; i++)
        nuevo[i] = canciones[i];

    for(int i = cantidadCanciones; i < nuevaCapacidad; i++)
        nuevo[i] = nullptr;

    delete[] canciones;
    canciones = nuevo;
    capacidadCanciones = nuevaCapacidad;
}

void ListaFavoritos::redimensionarListasSeguidas() {
    int nuevaCapacidad = capacidadListasSeguidas * 2;
    ListaFavoritos** nuevo = new ListaFavoritos*[nuevaCapacidad];

    for(int i = 0; i < cantidadListasSeguidas; i++)
        nuevo[i] = listasSeguidas[i];

    for(int i = cantidadListasSeguidas; i < nuevaCapacidad; i++)
        nuevo[i] = nullptr;

    delete[] listasSeguidas;
    listasSeguidas = nuevo;
    capacidadListasSeguidas = nuevaCapacidad;
}

// operaciones con canciones
bool ListaFavoritos::existeCancion(int _id) {
    for(int i = 0; i < cantidadCanciones; i++)
        if(canciones[i] != nullptr && canciones[i]->getIdCancion() == _id)
            return true;
    return false;
}

void ListaFavoritos::agregarCancion(Cancion* _cancion) {
    if(_cancion == nullptr || existeCancion(_cancion->getIdCancion())) return;

    if(cantidadCanciones == capacidadCanciones)
        redimensionarCanciones();

    canciones[cantidadCanciones++] = _cancion;
}

void ListaFavoritos::eliminarCancion(int _id) {
    for(int i = 0; i < cantidadCanciones; i++){
        if(canciones[i] != nullptr && canciones[i]->getIdCancion() == _id){
            for(int j = i; j < cantidadCanciones - 1; j++)
                canciones[j] = canciones[j+1];

            canciones[cantidadCanciones - 1] = nullptr;
            cantidadCanciones--;
            return;
        }
    }
}

Cancion* ListaFavoritos::getCancionEn(int index) {
    if(index < 0 || index >= cantidadCanciones)
        return nullptr;
    return canciones[index];
}

void ListaFavoritos::mostrarCanciones() {
    std::cout << "\n>>> Canciones propias:\n";
    for(int i = 0; i < cantidadCanciones; i++)
        std::cout << " - " << canciones[i]->getNombre() << std::endl;

    for(int k = 0; k < cantidadListasSeguidas; k++) {
        ListaFavoritos* otra = listasSeguidas[k];
        if(otra != nullptr){
            std::cout << "\n>>> Canciones de lista seguida de "
                      << otra->getUsuarioPropietario()->getNickname() << ":\n";
            for(int j = 0; j < otra->cantidadCanciones; j++)
                std::cout << " - " << otra->canciones[j]->getNombre() << std::endl;
        }
    }
}

// operaciones con listas seguidas
void ListaFavoritos::seguirLista(ListaFavoritos* _lista) {
    if(_lista == nullptr || _lista == this) return;

    if(cantidadListasSeguidas == capacidadListasSeguidas)
        redimensionarListasSeguidas();

    listasSeguidas[cantidadListasSeguidas++] = _lista;
}

// operaciones combinadas
Cancion** ListaFavoritos::obtenerTodasLasCanciones(int& cantidadTotal) {
    cantidadTotal = 0;

    for (int i = 0; i < cantidadCanciones; i++) {
        if (canciones[i] != nullptr) {
            cantidadTotal++;
        }
    }

    for (int i = 0; i < cantidadListasSeguidas; i++) {
        if (listasSeguidas[i]) {
            Cancion** cancionesSeguidas = listasSeguidas[i]->getCanciones();
            int cantSeguidas = listasSeguidas[i]->getCantidadCanciones();

            for (int j = 0; j < cantSeguidas; j++) {
                if (cancionesSeguidas[j] != nullptr) {
                    cantidadTotal++;
                }
            }
        }
    }

    if (cantidadTotal == 0) {
        return nullptr;
    }

    Cancion** todasLasCanciones = new Cancion*[cantidadTotal];
    int indice = 0;

    for (int i = 0; i < cantidadCanciones; i++) {
        if (canciones[i] != nullptr) {
            todasLasCanciones[indice++] = canciones[i];
        }
    }

    for (int i = 0; i < cantidadListasSeguidas; i++) {
        if (listasSeguidas[i]) {
            Cancion** cancionesSeguidas = listasSeguidas[i]->getCanciones();
            int cantSeguidas = listasSeguidas[i]->getCantidadCanciones();

            for (int j = 0; j < cantSeguidas; j++) {
                if (cancionesSeguidas[j] != nullptr) {
                    todasLasCanciones[indice++] = cancionesSeguidas[j];
                }
            }
        }
    }

    return todasLasCanciones;
}

int ListaFavoritos::getCantidadTotalCanciones() {
    int total = cantidadCanciones;
    for (int i = 0; i < cantidadListasSeguidas; i++) {
        if (listasSeguidas[i]) {
            total += listasSeguidas[i]->getCantidadCanciones();
        }
    }
    return total;
}
