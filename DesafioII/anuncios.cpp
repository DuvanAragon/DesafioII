#include "Anuncios.h"
#include <random>
#include <iostream>

// constructores
Anuncio::Anuncio() {
    texto = "Sin texto";
    categoria = "C";
    prioridad = 1;
    mostrado = false;
}

Anuncio::Anuncio(string _texto, string _categoria) {
    texto = _texto;
    categoria = _categoria;
    asignarPrioridad();
    mostrado = false;
}

// getters
string Anuncio::getTexto() const { return texto; }
string Anuncio::getCategoria() const { return categoria; }
int Anuncio::getPrioridad() const { return prioridad; }
bool Anuncio::getMostrado() const { return mostrado; }

// setters
void Anuncio::setTexto(string nuevoTexto) { texto = nuevoTexto; }
void Anuncio::setCategoria(string nuevaCategoria) {
    categoria = nuevaCategoria;
    asignarPrioridad();
}
void Anuncio::setMostrado(bool estado) { mostrado = estado; }

// métodos funcionales
void Anuncio::asignarPrioridad() {
    if (categoria == "AAA") prioridad = 3;
    else if (categoria == "B") prioridad = 2;
    else if (categoria == "C") prioridad = 1;
}

void Anuncio::mostrar() {
    cout << texto << endl;
    cout << "Categoria - " << categoria << endl << endl;
    mostrado = true;
}

int Anuncio::seleccionarAleatorio(Anuncio* listaAnuncios[], int cantidadAnuncios, int ultimoAnuncio) {
    if (cantidadAnuncios <= 0) return -1;

    static random_device rd;
    static mt19937 gen(rd());

    int suma = 0;
    for (int i = 0; i < cantidadAnuncios; i++) {
        if (i != ultimoAnuncio)
            suma += listaAnuncios[i]->getPrioridad();
    }

    if (suma == 0) return -1;

    uniform_int_distribution<> dist(1, suma);
    int valor = dist(gen);

    int acumulado = 0;
    for (int i = 0; i < cantidadAnuncios; i++) {
        if (i == ultimoAnuncio) continue;
        acumulado += listaAnuncios[i]->getPrioridad();
        if (valor <= acumulado)
            return i;
    }

    return 0;
}
