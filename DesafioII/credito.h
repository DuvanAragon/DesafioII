#ifndef CREDITO_H
#define CREDITO_H

#include <string>
using namespace std;

/*
 * Clase Credito: Representa los creditos de una cancion
 * Almacena informacion de productores, musicos y compositores
 */

class Credito {
private:
    string nombre;
    string apellido;
    string tipo; // "Productor", "Musico", "Compositor"
    string codigoAfiliacion; // 10 caracteres alfanumericos
    int idCancion;

public:
    // Constructores
    Credito();
    Credito(const string& nombre, const string& apellido,
            const string& tipo, const string& codigo);

    // Getters
    string getNombre() const;
    string getApellido() const;
    string getTipo() const;
    string getCodigoAfiliacion() const;
    int getIdCancion() const;


    // Setters
    void setNombre(const string& nombre);
    void setApellido(const string& apellido);
    void setTipo(const string& tipo);
    void setCodigoAfiliacion(const string& codigo);
    void setIdCancion(int id);

    // Metodo para mostrar informacion del credito
    void mostrarCredito() const;
};

#endif
