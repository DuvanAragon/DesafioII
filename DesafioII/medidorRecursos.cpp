#include "MedidorRecursos.h"
#include <iostream>

MedidorRecursos::MedidorRecursos() {
    capacidad = 6;
    totalRegistros = 0;
    contadorIteraciones = 0;
    memoriaKB = 0;

    nombres = new string[capacidad];
    conteos = new int[capacidad];
    for (int i = 0; i < capacidad; i++) conteos[i] = 0;
}

MedidorRecursos::~MedidorRecursos() {
    delete[] nombres;
    delete[] conteos;
}

void MedidorRecursos::iniciarTiempo() {
    tiempoInicio = high_resolution_clock::now();
}

void MedidorRecursos::detenerTiempo() {
    tiempoFin = high_resolution_clock::now();
}

void MedidorRecursos::registrarMemoria(size_t bytes) {
    memoriaKB = static_cast<double>(bytes) / 1024.0;
}

void MedidorRecursos::incrementarIteracion() {
    contadorIteraciones++;
}

int MedidorRecursos::buscarIndiceEtiqueta(const string& etiqueta) const {
    for (int i = 0; i < totalRegistros; i++) {
        if (nombres[i] == etiqueta) return i;
    }
    return -1;
}

void MedidorRecursos::registrarLlamada(const string& etiqueta) {
    int indice = buscarIndiceEtiqueta(etiqueta);
    if (indice != -1) {
        conteos[indice]++;
        return;
    }

    if (totalRegistros >= capacidad)
        ampliarCapacidad();

    nombres[totalRegistros] = etiqueta;
    conteos[totalRegistros] = 1;
    totalRegistros++;
}

void MedidorRecursos::ampliarCapacidad() {
    int nuevaCapacidad = capacidad * 2;

    string* nuevosNombres = new string[nuevaCapacidad];
    int* nuevosConteos = new int[nuevaCapacidad];

    for (int i = 0; i < totalRegistros; i++) {
        nuevosNombres[i] = nombres[i];
        nuevosConteos[i] = conteos[i];
    }

    delete[] nombres;
    delete[] conteos;

    nombres = nuevosNombres;
    conteos = nuevosConteos;
    capacidad = nuevaCapacidad;
}

void MedidorRecursos::reiniciar() {
    for (int i = 0; i < totalRegistros; i++) conteos[i] = 0;
    totalRegistros = 0;
    contadorIteraciones = 0;
    memoriaKB = 0;
}

void MedidorRecursos::mostrarResumen(const string& titulo) const {
    auto duracion = duration_cast<nanoseconds>(tiempoFin - tiempoInicio);
    double tiempoSegundos = duracion.count() / 1'000'000'000.0;

    cout << "\n " << titulo << "\n";
    cout << "-----------------------------\n";
    cout << " Tiempo total: " << duracion.count() << " ns (" << tiempoSegundos << " s)\n";
    cout << " Iteraciones: " << contadorIteraciones << "\n";
    cout << " Memoria usada: " << memoriaKB << " KB\n";
    cout << "-----------------------------\n";
}

void MedidorRecursos::mostrarConteoLlamadas() const {
    cout << "\n INVOCACIONES REGISTRADAS\n-----------------------------\n";
    for (int i = 0; i < totalRegistros; i++) {
        cout << nombres[i] << ": " << conteos[i] << " llamadas\n";
    }
    cout << "-----------------------------\n";
}

int MedidorRecursos::getTotalRegistros() const {
    return totalRegistros;
}

int MedidorRecursos::getContadorIteraciones() const {
    return contadorIteraciones;
}

double MedidorRecursos::getMemoriaKB() const {
    return memoriaKB;
}

int MedidorRecursos::getConteoEtiqueta(const string& etiqueta) const {
    int indice = buscarIndiceEtiqueta(etiqueta);
    if (indice != -1) {
        return conteos[indice];
    } else {
        return 0;
    }
}

void MedidorRecursos::setMemoriaKB(double nuevaMemoria) {
    memoriaKB = nuevaMemoria;
}

void MedidorRecursos::setContadorIteraciones(int nuevoContador) {
    contadorIteraciones = nuevoContador;
}
