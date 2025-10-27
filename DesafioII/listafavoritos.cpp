#include "listaFavoritos.h"
#include "Usuario.h"
#include "SistemaReproduccion.h"

ListaFavoritos::ListaFavoritos() {
    capacidadCanciones = 10000;
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

// GETTERS
Cancion** ListaFavoritos::getCanciones() { return canciones; }
int ListaFavoritos::getCantidadCanciones() { return cantidadCanciones; }
ListaFavoritos** ListaFavoritos::getListasSeguidas() { return listasSeguidas; }
Usuario* ListaFavoritos::getUsuarioPropietario() { return usuarioPropietario; }

// FUNCIONALIDAD
bool ListaFavoritos::existeCancion(int _id) {
    for(int i = 0; i < cantidadCanciones; i++)
        if(canciones[i] != nullptr && canciones[i]->getIdCancion() == _id)
            return true;
    return false;
}

void ListaFavoritos::agregarCancion(Cancion* _cancion) {
    if(_cancion == nullptr || existeCancion(_cancion->getIdCancion())) return;
    canciones[cantidadCanciones++] = _cancion;
}

void ListaFavoritos::eliminarCancion(int _id) {
    for(int i = 0; i < cantidadCanciones; i++){
        if(canciones[i]->getIdCancion() == _id){
            for(int j = i; j < cantidadCanciones - 1; j++)
                canciones[j] = canciones[j+1];
            canciones[cantidadCanciones - 1] = nullptr;
            cantidadCanciones--;
            return;
        }
    }
}

void ListaFavoritos::seguirLista(ListaFavoritos* _lista) {
    if(_lista == nullptr || _lista == this) return; // evitar seguirse a sí mismo
    if(cantidadListasSeguidas < capacidadListasSeguidas)
        listasSeguidas[cantidadListasSeguidas++] = _lista;
}

// NUEVO: Mostrar canciones de forma dinámica
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


ListaFavoritos::~ListaFavoritos() {
    delete[] canciones;
    delete[] listasSeguidas;
}
