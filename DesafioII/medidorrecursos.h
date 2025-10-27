#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

class MedidorRecursos {
private:
    string* nombres;
    int* conteos;
    int totalRegistros;
    int capacidad;

    high_resolution_clock::time_point tiempoInicio;
    high_resolution_clock::time_point tiempoFin;

    double memoriaKB;
    long long contadorIteraciones;

public:
    MedidorRecursos();
    ~MedidorRecursos();

    void iniciarTiempo();
    void detenerTiempo();

    void registrarMemoria(size_t bytes);
    void incrementarIteracion();
    void registrarLlamada(const string& etiqueta);

    void mostrarResumen(const string& titulo) const;
    void mostrarConteoLlamadas() const;

    void reiniciar();
    void ampliarCapacidad();

    int getTotalRegistros() const;
    int getContadorIteraciones() const;
    double getMemoriaKB() const;
    int getConteoEtiqueta(const string& etiqueta) const;

    void setMemoriaKB(double nuevaMemoria);
    void setContadorIteraciones(int nuevoContador);

private:
    int buscarIndiceEtiqueta(const string& etiqueta) const;
};

#endif
