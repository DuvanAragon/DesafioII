#ifndef ANUNCIOS_H
#define ANUNCIOS_H

#include <string>
using namespace std;

class Anuncio {
private:
    string texto;
    string categoria;
    int prioridad;
    bool mostrado;

public:
    // constructores
    Anuncio();
    Anuncio(string texto, string categoria);

    // getters
    string getTexto() const;
    string getCategoria() const;
    int getPrioridad() const;
    bool getMostrado() const;

    // setters
    void setTexto(string nuevoTexto);
    void setCategoria(string nuevaCategoria);
    void setMostrado(bool estado);

    // métodos funcionales
    void mostrar();
    void asignarPrioridad();
    static int seleccionarAleatorio(Anuncio* listaAnuncios[], int cantidadAnuncios, int ultimoAnuncio);
};

#endif
