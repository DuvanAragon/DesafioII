#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "Credito.h"
using namespace std;

/*
 * Clase Cancion: Representa una cancion en la plataforma
 * Gestiona rutas de audio, creditos y reproducciones
 */
class Cancion {
private:
    int idCancion; // 9 digitos: 5(artista) + 2(album) + 2(cancion)
    string nombre;
    float duracion; // en segundos
    string ruta128; // ruta al archivo 128 kbps
    string ruta320; // ruta al archivo 320 kbps
    int reproducciones;

    Credito** creditos; // Arreglo dinamico de créditos
    int cantidadCreditos;
    int capacidadCreditos;

public:
    // Constructores
    Cancion();
    Cancion(int id, const string& nombre, float duracion,
            const string& r128, const string& r320);
    Cancion(const Cancion& otra); // Constructor de copia
    ~Cancion(); // Destructor

    // Getters
    int getIdCancion() const;
    string getNombre() const;
    float getDuracion() const;
    string getRuta128() const;
    string getRuta320() const;
    int getReproducciones() const;
    Credito** getCreditos() const;
    int getCantidadCreditos() const;

    // Setters
    void setIdCancion(int id);
    void setNombre(const string& nombre);
    void setDuracion(float duracion);
    void setRuta128(const string& ruta);
    void setRuta320(const string& ruta);
    void setReproducciones(int reproducciones);
    void setCreditos(Credito** creditos, int cantidad);

    // Metodos funcionales
    bool validarID() const; // Valida formato del ID
    void reproducir(const string& calidad); // Muestra ruta segun calidad
    void mostrarRutas() const; // Muestra ambas rutas
    void incrementarReproduccion();
    void agregarCredito(Credito* credito);

    // Sobrecarga de operador
    Cancion& operator=(const Cancion& otra);

private:
    void expandirCapacidadCreditos();
    void copiarCreditos(Credito** origen, int cantidad);
    void liberarCreditos();
};

#endif
