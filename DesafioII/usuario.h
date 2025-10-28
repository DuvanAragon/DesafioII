#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "ListaFavoritos.h"
#include "Cancion.h"
#include "sistemaReproduccion.h"

using namespace std;

class Usuario {
private:
    string nickname;
    string tipoMembresia;
    string ciudad;
    string pais;
    string fechaRegistro;
    ListaFavoritos* listaFavoritos;

public:
    // Constructores y destructor
    Usuario();
    Usuario(string nickname, string tipo, string ciudad, string pais, string fecha);
    ~Usuario();

    // Getters
    string getNickname();
    string getTipoMembresia();
    string getCiudad();
    string getPais();
    string getFechaRegistro();
    ListaFavoritos* getListaFavoritos();

    // Setters
    void setNickname(string nickname);
    void setTipoMembresia(string tipo);
    void setCiudad(string ciudad);
    void setPais(string pais);
    void setFechaRegistro(string fecha);
    void setListaFavoritos(ListaFavoritos* lista);

    // Métodos funcionales
    bool Premium();
    void seguirLista(Usuario* usuarioASeguir);
    void reproducirCancion(Cancion* cancion, SistemaReproduccion* sistema);
};

#endif
