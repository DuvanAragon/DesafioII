#ifndef CREDITO_H
#define CREDITO_H

#include <string>
using namespace std;

class Credito {
private:
    string nombre;
    string apellido;
    string tipo; // "Productor", "Musico", "Compositor"
    string codigoAfiliacion; // 10 caracteres alfanumericos
    int idCancion;

public:
    // constructores
    Credito();
    Credito(const string& nombre, const string& apellido,
            const string& tipo, const string& codigo);

    // getters
    string getNombre() const;
    string getApellido() const;
    string getTipo() const;
    string getCodigoAfiliacion() const;
    int getIdCancion() const;

    // setters
    void setNombre(const string& nombre);
    void setApellido(const string& apellido);
    void setTipo(const string& tipo);
    void setCodigoAfiliacion(const string& codigo);
    void setIdCancion(int id);

    // métodos de visualización
    void mostrarCredito() const;
};

#endif
