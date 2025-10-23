#include "Credito.h"
#include <iostream>

// Constructor por defecto
Credito::Credito() : nombre(""), apellido(""), tipo(""), codigoAfiliacion("") {}

// Constructor parametrizado
Credito::Credito(const string& nombre, const string& apellido,
                 const string& tipo, const string& codigo)
    : nombre(nombre), apellido(apellido), tipo(tipo), codigoAfiliacion(codigo) {}

// Getters
string Credito::getNombre() const { return nombre; }
string Credito::getApellido() const { return apellido; }
string Credito::getTipo() const { return tipo; }
string Credito::getCodigoAfiliacion() const { return codigoAfiliacion; }

// Setters
void Credito::setNombre(const string& nombre) { this->nombre = nombre; }
void Credito::setApellido(const string& apellido) { this->apellido = apellido; }
void Credito::setTipo(const string& tipo) { this->tipo = tipo; }
void Credito::setCodigoAfiliacion(const string& codigo) { this->codigoAfiliacion = codigo; }

// Mostrar informacion del credito
void Credito::mostrarCredito() const {
    cout << tipo << ": " << nombre << " " << apellido
         << " (Código: " << codigoAfiliacion << ")" << endl;
}
