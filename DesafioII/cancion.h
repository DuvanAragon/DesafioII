#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "Credito.h"

using namespace std;

class Cancion {
private:
    // atributos básicos
    int idCancion;
    string nombre;
    float duracion;
    string ruta128;
    string ruta320;
    int reproducciones;

    // gestión de créditos
    Credito** creditos;
    int cantidadCreditos;
    int capacidadCreditos;

    // métodos auxiliares privados
    void expandirCapacidadCreditos();
    void copiarCreditos(Credito** origen, int cantidad);
    void liberarCreditos();

public:
    // constructores y destructor
    Cancion();
    Cancion(int id, const string& nombre, float duracion, const string& r128, const string& r320);
    Cancion(const Cancion& otra);
    ~Cancion();
    Cancion& operator=(const Cancion& otra);

    // getters
    int getIdCancion() const;
    string getNombre() const;
    float getDuracion() const;
    string getRuta128() const;
    string getRuta320() const;
    int getReproducciones() const;
    Credito** getCreditos() const;
    int getCantidadCreditos() const;

    // setters
    void setIdCancion(int id);
    void setNombre(const string& nombre);
    void setDuracion(float duracion);
    void setRuta128(const string& ruta);
    void setRuta320(const string& ruta);
    void setReproducciones(int reproducciones);
    void setCreditos(Credito** nuevosCreditos, int cantidad);

    // métodos funcionales
    bool validarID() const;
    void reproducir(const string& calidad = "128");
    void incrementarReproduccion();
    void agregarCredito(Credito* credito);

    // métodos de extracción de IDs
    int getIdArtista() const;
    int getIdAlbum() const;
    int getIdCancionIndividual() const;
};

#endif
