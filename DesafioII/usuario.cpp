#include "Usuario.h"
#include "ListaFavoritos.h"
#include "Cancion.h"
#include "SistemaReproduccion.h"
#include <iostream>

using namespace std;

// Constructores y destructor
Usuario::Usuario() {
    nickname = "";
    tipoMembresia = "estandar";
    ciudad = "";
    pais = "";
    fechaRegistro = "";
    listaFavoritos = new ListaFavoritos(this);
}

Usuario::Usuario(string _nickname, string _tipo, string _ciudad, string _pais, string _fecha) {
    nickname = _nickname;
    tipoMembresia = _tipo;
    ciudad = _ciudad;
    pais = _pais;
    fechaRegistro = _fecha;
    listaFavoritos = new ListaFavoritos(this);
}

Usuario::~Usuario() {
    delete listaFavoritos;
}

// Getters
string Usuario::getNickname() { return nickname; }
string Usuario::getTipoMembresia() { return tipoMembresia; }
string Usuario::getCiudad() { return ciudad; }
string Usuario::getPais() { return pais; }
string Usuario::getFechaRegistro() { return fechaRegistro; }
ListaFavoritos* Usuario::getListaFavoritos() { return listaFavoritos; }

// Setters
void Usuario::setNickname(string _nickname) { nickname = _nickname; }
void Usuario::setTipoMembresia(string _tipo) { tipoMembresia = _tipo; }
void Usuario::setCiudad(string _ciudad) { ciudad = _ciudad; }
void Usuario::setPais(string _pais) { pais = _pais; }
void Usuario::setFechaRegistro(string _fecha) { fechaRegistro = _fecha; }
void Usuario::setListaFavoritos(ListaFavoritos* _lista) { listaFavoritos = _lista; }

// Métodos funcionales
bool Usuario::Premium() {
    return tipoMembresia == "premium";
}

void Usuario::seguirLista(Usuario* usuarioASeguir) {
    if (usuarioASeguir == nullptr || !Premium() || !usuarioASeguir->Premium()) {
        cout << "Solo usuarios premium pueden seguir listas." << endl;
        return;
    }
    listaFavoritos->seguirLista(usuarioASeguir->getListaFavoritos());
}

void Usuario::reproducirCancion(Cancion* cancion, SistemaReproduccion* sistema) {
    if (cancion == nullptr || sistema == nullptr) return;
    sistema->setUsuarioActivo(this);
    sistema->reproducir(cancion);
}
