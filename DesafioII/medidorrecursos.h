#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

class Cancion;
class Usuario;
class ListaFavoritos;
class Artista;
class Album;

class MedidorRecursos {
private:
    // contadores y registros
    string* nombres;
    int* conteos;
    int totalRegistros;
    int capacidad;

    // medición de tiempo
    high_resolution_clock::time_point tiempoInicio;
    high_resolution_clock::time_point tiempoFin;

    // métricas de recursos
    double memoriaKB;
    long long contadorIteraciones;

public:
    // constructor y destructor
    MedidorRecursos();
    ~MedidorRecursos();

    // gestión de tiempo
    void iniciarTiempo();
    void detenerTiempo();

    // registro de métricas
    void registrarMemoria(size_t bytes);
    void incrementarIteracion();
    void registrarLlamada(const string& etiqueta);

    // visualización de resultados
    void mostrarResumen(const string& titulo) const;
    void mostrarConteoLlamadas() const;

    // gestión de datos
    void reiniciar();
    void ampliarCapacidad();

    // getters
    int getTotalRegistros() const;
    int getContadorIteraciones() const;
    double getMemoriaKB() const;
    int getConteoEtiqueta(const string& etiqueta) const;

    // setters
    void setMemoriaKB(double nuevaMemoria);
    void setContadorIteraciones(int nuevoContador);

private:
    int buscarIndiceEtiqueta(const string& etiqueta) const;
};

#endif
