#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "Artista.h"
#include "SistemaReproduccion.h"
#include <string>

// Forward declarations
class Usuario;
class Anuncio;
class MedidorRecursos;

/*
 * Clase Plataforma: Clase central que coordina todo el sistema
 * Gestiona usuarios, artistas, anuncios y reproduccion
 */
class Plataforma {
private:
    Usuario** usuarios;
    Artista** artistas;
    Anuncio** anuncios;
    SistemaReproduccion* sistemaReproduccion;
    MedidorRecursos* medidor;

    int cantidadUsuarios;
    int capacidadUsuarios;
    int cantidadArtistas;
    int capacidadArtistas;
    int cantidadAnuncios;
    int capacidadAnuncios;

    Usuario* usuarioActual; // Usuario con sesion iniciada

public:
    // Constructores
    Plataforma();
    ~Plataforma();

    // Getters
    Usuario** getUsuarios() const;
    Artista** getArtistas() const;
    Anuncio** getAnuncios() const;
    SistemaReproduccion* getSistemaReproduccion() const;
    MedidorRecursos* getMedidor() const;
    int getCantidadUsuarios() const;
    int getCantidadArtistas() const;
    int getCantidadAnuncios() const;
    Usuario* getUsuarioActual() const;

    // Setters
    void setUsuarios(Usuario** usuarios, int cantidad);
    void setArtistas(Artista** artistas, int cantidad);
    void setAnuncios(Anuncio** anuncios, int cantidad);

    // Gestion de datos
    void cargarDatos();
    void guardarDatos();

    // Funcionalidades principales
    Usuario* login(const string& nickname);
    void reproducirAleatorio();
    void medirRecursos(const string& funcionalidad);

    // Busquedas
    Usuario* encontrarUsuario(const string& nickname) const;
    Cancion* encontrarCancion(int id) const;
    Cancion** obtenerTodasLasCanciones(int& totalCanciones) const;

    // Sobrecarga de operador
    bool operator==(const Plataforma& otra) const;

    // Metodos auxiliares
    void agregarUsuario(Usuario* usuario);
    void agregarArtista(Artista* artista);
    void agregarAnuncio(Anuncio* anuncio);

private:
    void expandirCapacidadUsuarios();
    void expandirCapacidadArtistas();
    void expandirCapacidadAnuncios();

    // Metodos de carga de datos
    void cargarArtistas();
    void cargarUsuarios();
    void cargarAnuncios();
};

#endif
