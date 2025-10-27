#ifndef USUARIO_H
#define USUARIO_H

#include <string>

#include "ListaFavoritos.h"
#include "Cancion.h"
#include "SistemaReproduccion.h"

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
    // Constructores
    Usuario();
    Usuario(string nickname, string tipo, string ciudad, string pais, string fecha);

    // Getters y Setters
    void setNickname(string nickname);
    string getNickname();

    void setTipoMembresia(string tipo);
    string getTipoMembresia();

    void setCiudad(string ciudad);
    string getCiudad();

    void setPais(string pais);
    string getPais();

    void setFechaRegistro(string fecha);
    string getFechaRegistro();

    void setListaFavoritos(ListaFavoritos* lista);
    ListaFavoritos* getListaFavoritos();

    // Métodos funcionales
    bool Premium();  // ← CAMBIAR AQUÍ de Premium() a esPremium()
    bool operator==(Usuario& otro);

    void seguirLista(Usuario* usuarioASeguir);
    void reproducirCancion(Cancion* cancion, SistemaReproduccion* sistema);

    // Destructor
    ~Usuario();
};

#endif
