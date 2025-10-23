#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>
using namespace std;

class Anuncio {
private:
    string texto;
    string categoria;
    int prioridad;
    bool mostrado;

public:
    Anuncio();
    Anuncio(string texto, string categoria);

    string getTexto() const;
    string getCategoria() const;
    int getPrioridad() const;
    bool getMostrado() const;

    void setTexto(string nuevoTexto);
    void setCategoria(string nuevaCategoria);
    void setMostrado(bool estado);

    void mostrar();
    void asignarPrioridad();
    static int seleccionarAleatorio(Anuncio* listaAnuncios[], int cantidadAnuncios, int ultimoAnuncio);
};

#endif
