#include <iostream>
#include <chrono>
#include <windows.h>  // <- importante
#include "plataforma.h"
#include "SistemaReproduccion.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Plataforma plataforma;
    SistemaReproduccion reproductor;
    string nickName;

    // ------------- Cargar Datos ---------------
    plataforma.cargarUsuarios("DatasetDesarrollo/usuarios.txt");
    plataforma.cargarArtistas("DatasetDesarrollo/artistas.txt");
    plataforma.indexarCanciones("DatasetDesarrollo/canciones.txt");
    plataforma.cargarListasFavoritosDesdeArchivo("DatasetDesarrollo/listaFavoritos.txt");
    plataforma.cargarAnuncios("DatasetDesarrollo/anuncios.txt");

    cout << "=================================================================" << endl;
    cout << "====================  BIENVENIDO A UDEATUNES  ===================" << endl;
    cout << "=================================================================" << endl;

    Usuario* usuarioLogueado = nullptr;

    // ------------- Login ---------------
    while (true) {
        cout << "\nIngrese su nickname: ";
        getline(cin, nickName);

        usuarioLogueado = plataforma.login(nickName);

        if (usuarioLogueado != nullptr) {
            cout << "\nBienvenido, " << usuarioLogueado->getNickname()
            << "\n";
            break;
        } else {
            cout << "Usuario no encontrado, intente de nuevo.\n";
        }
    }

    reproductor.setUsuarioActivo(usuarioLogueado);

    cout << "\n=== REPRODUCCIÓN ALEATORIA AUTOMÁTICA (5 canciones) ===\n" << endl;

    int ultimoID = -1;

    for (int i = 0; i < 5; i++) {   // Reproducir 5 canciones
        Cancion* c = plataforma.seleccionarCancionAleatoria(ultimoID);

        if (c == nullptr) {
            cout << "\nNo hay canciones disponibles.\n";
            break;
        }

        reproductor.reproducir(c);
        ultimoID = c->getIdCancion();

        // Temporizador de 3 segundos usando solo chrono (sin <thread>)
        auto inicio = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - inicio < std::chrono::seconds(3)) {
            // Esperando...
        }
    }

    cout << "\n--- Fin de la reproducción automática ---\n";

    return 0;
}

