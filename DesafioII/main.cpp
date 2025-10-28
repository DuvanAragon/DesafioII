#include <iostream>
#include <chrono>
#include <windows.h>
#include "plataforma.h"
#include "MedidorRecursos.h"

using namespace std;

// Funciones de reproducción
void reproducirCancionesAleatorias(Plataforma& plataforma, SistemaReproduccion& reproductor, int& ultimoID, int cantidad = 5);
void reproducirListaFavoritos(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuario);

// Funciones de gestión de listas de favoritos
void gestionarListaFavoritos(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuario);

// Funciones de menú
int menuPrincipalUsuarioPremium();
int menuPrincipalUsuarioEstandar();

// Flujos de usuario
void flujoUsuarioEstandar(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuarioLogueado);
void flujoUsuarioPremium(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuarioLogueado);

// Función de carga de datos
void cargarTodosLosDatos(Plataforma& plataforma);

// IMPLEMENTACIÓN DE FUNCIONES

/**
 * Reproduce una secuencia de canciones aleatorias
 */
void reproducirCancionesAleatorias(Plataforma& plataforma, SistemaReproduccion& reproductor, int& ultimoID, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        Cancion* c = plataforma.seleccionarCancionAleatoria(ultimoID);

        if (c == nullptr) {
            cout << "\n No hay canciones disponibles.\n";
            break;
        }

        // Verificar que la canción sea válida
        if (c->getIdCancion() <= 0) {
            delete c;
            continue;
        }

        reproductor.reproducir(c);
        ultimoID = c->getIdCancion();

        // Simular tiempo de reproducción
        auto inicio = std::chrono::steady_clock::now();
        while (std::chrono::steady_clock::now() - inicio < std::chrono::seconds(3));
    }
}

/**
 * Gestiona la lista de favoritos de un usuario premium
 */
void gestionarListaFavoritos(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuario) {
    ListaFavoritos* lista = usuario->getListaFavoritos();
    if (!lista) {
        cout << "Error: No se pudo acceder a la lista de favoritos." << endl;
        return;
    }

    int opcion = -1;
    bool enMenu = true;

    while (enMenu) {
        cout << "\n===============================================================" << endl;
        cout << "=                   MI LISTA DE FAVORITOS                    =" << endl;
        cout << "===============================================================" << endl;
        cout << "1. Ver mis canciones favoritas" << endl;
        cout << "2. Agregar cancion a favoritos" << endl;
        cout << "3. Eliminar cancion de favoritos" << endl;
        cout << "4. Seguir lista de otro usuario" << endl;
        cout << "5. Reproducir lista de favoritos" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "\nSelecciona una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            cout << "\nTus canciones favoritas:" << endl;
            lista->mostrarCanciones();
            break;
        }
        case 2: {
            cout << "\nIngresa el ID de la cancion a agregar: ";
            int idCancion;
            cin >> idCancion;
            cin.ignore();

            Cancion* cancion = plataforma.cargarCancion(idCancion);
            if (cancion) {
                lista->agregarCancion(cancion);
                cout << "Cancion agregada a favoritos: " << cancion->getNombre() << endl;
            } else {
                cout << "No se encontro la cancion con ID: " << idCancion << endl;
            }
            break;
        }
        case 3: {
            cout << "\nIngresa el ID de la cancion a eliminar: ";
            int idCancion;
            cin >> idCancion;
            cin.ignore();

            // Verificar si la canción existe antes de eliminar
            if (lista->existeCancion(idCancion)) {
                lista->eliminarCancion(idCancion);
                cout << "Cancion eliminada de favoritos." << endl;
            } else {
                cout << "La canción con ID " << idCancion << " no esta en tu lista de favoritos." << endl;
            }
            break;
        }
        case 4: {
            cout << "\nIngresa el nickname del usuario a seguir: ";
            string nickname;
            getline(cin, nickname);

            Usuario* usuarioASeguir = plataforma.buscarUsuario(nickname);
            if (usuarioASeguir && usuarioASeguir->Premium()) {
                usuario->seguirLista(usuarioASeguir);
                cout << "Ahora sigues la lista de: " << nickname << endl;
            } else {
                cout << "Usuario no encontrado o no es premium: " << nickname << endl;
            }
            break;
        }
        case 5: {
            reproducirListaFavoritos(plataforma, reproductor, usuario);
            break;
        }
        case 6: {
            enMenu = false;
            cout << "Volviendo al menu principal..." << endl;
            break;
        }
        default: {
            cout << "Opcion no valida." << endl;
            break;
        }
        }
    }
}

/**
 * Muestra el menú principal para usuarios premium
 */
int menuPrincipalUsuarioPremium() {
    int opcion = -1;
    while (true) {
        cout << "===============================================================" << endl;
        cout << "=                     MENU USUARIO PREMIUM                    =" << endl;
        cout << "===============================================================" << endl << endl;
        cout << "1. Reproduccion aleatoria" << endl;
        cout << "2. Mi lista de favoritas" << endl;
        cout << "3. Cerrar sesion" << endl;

        cout << endl << "Selecciona la opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion >= 1 && opcion <= 3) {
            return opcion;
        } else {
            cout << "Selecciona una opcion valida (1 a 3)." << endl << endl;
        }
    }
}

/**
 * Muestra el menú principal para usuarios estándar
 */
int menuPrincipalUsuarioEstandar() {
    int opcion = -1;
    while (true) {
        cout << "===============================================================" << endl;
        cout << "=                   MENU USUARIO ESTANDAR                     =" << endl;
        cout << "===============================================================" << endl << endl;
        cout << "1. Reproduccion aleatoria." << endl;
        cout << "2. Cerrar sesion." << endl;

        cout << endl << "Selecciona la opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion >= 1 && opcion <= 2) {
            return opcion;
        } else {
            cout << "Selecciona una opcion valida (1 a 2)." << endl << endl;
        }
    }
}

/**
 * Maneja el flujo de un usuario estándar
 */
void flujoUsuarioEstandar(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuarioLogueado) {
    int ultimoID = -1;
    bool sesionActiva = true;

    while (sesionActiva) {
        int opcion = menuPrincipalUsuarioEstandar();

        switch (opcion) {
        case 1: {
            reproducirCancionesAleatorias(plataforma, reproductor, ultimoID, 5);
            break;
        }
        case 2: {
            cout << "\nCerrando sesion para usuario: " << usuarioLogueado->getNickname() << endl;

            // Guardar todos los datos antes de cerrar
            cout << "Guardando datos en almacenamiento permanente..." << endl;
            plataforma.guardarUsuarios("DatasetDesarrollo/usuarios.txt");
            plataforma.guardarCanciones("DatasetDesarrollo/canciones.txt");
            plataforma.guardarAlbumes("DatasetDesarrollo/albumes.txt");
            plataforma.guardarArtistas("DatasetDesarrollo/artistas.txt");
            plataforma.guardarListasFavoritosEnArchivo("DatasetDesarrollo/listaFavoritos.txt");
            plataforma.guardarAnuncios("DatasetDesarrollo/anuncios.txt");

            usuarioLogueado = nullptr;
            sesionActiva = false;
            break;
        }
        }
    }
}

/**
 * Maneja el flujo de un usuario premium
 */
void flujoUsuarioPremium(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuarioLogueado) {
    int ultimoID = -1;
    bool sesionActiva = true;

    while (sesionActiva) {
        int opcion = menuPrincipalUsuarioPremium();

        switch (opcion) {
        case 1: {
            reproducirCancionesAleatorias(plataforma, reproductor, ultimoID, 5);
            break;
        }
        case 2: {
            gestionarListaFavoritos(plataforma, reproductor, usuarioLogueado);
            break;
        }
        case 3: {
            cout << "\nCerrando sesión para usuario: " << usuarioLogueado->getNickname() << endl;

            // Guardar todos los datos antes de cerrar
            cout << "Guardando datos en almacenamiento permanente..." << endl;
            plataforma.guardarUsuarios("DatasetDesarrollo/usuarios.txt");
            plataforma.guardarCanciones("DatasetDesarrollo/canciones.txt");
            plataforma.guardarAlbumes("DatasetDesarrollo/albumes.txt");
            plataforma.guardarArtistas("DatasetDesarrollo/artistas.txt");
            plataforma.guardarListasFavoritosEnArchivo("DatasetDesarrollo/listaFavoritos.txt");
            plataforma.guardarAnuncios("DatasetDesarrollo/anuncios.txt");

            usuarioLogueado = nullptr;
            sesionActiva = false;
            break;
        }
        }
    }
}

/**
 * Carga todos los datos necesarios para la plataforma
 */
void cargarTodosLosDatos(Plataforma& plataforma) {
    // Cargar usuarios primero (necesarios para el login)
    plataforma.cargarUsuarios("DatasetDesarrollo/usuarios.txt");

    // Cargar el resto de datos
    plataforma.cargarArtistas("DatasetDesarrollo/artistas.txt");
    plataforma.indexarCanciones("DatasetDesarrollo/canciones.txt");
    plataforma.indexarAlbumes("DatasetDesarrollo/albumes.txt");
    plataforma.cargarListasFavoritosDesdeArchivo("DatasetDesarrollo/listaFavoritos.txt");
    plataforma.cargarAnuncios("DatasetDesarrollo/anuncios.txt");
}

/**
 * Reproduce la lista de favoritos del usuario con controles de reproducción
 */
void reproducirListaFavoritos(Plataforma& plataforma, SistemaReproduccion& reproductor, Usuario* usuario) {
    ListaFavoritos* lista = usuario->getListaFavoritos();
    if (!lista) {
        cout << "error: no se pudo acceder a la lista de favoritos." << endl;
        return;
    }

    int cantidadTotal;
    Cancion** todasLasCanciones = lista->obtenerTodasLasCanciones(cantidadTotal);

    if (cantidadTotal == 0 || todasLasCanciones == nullptr) {
        cout << "tu lista de favoritos esta vacia o no hay canciones validas." << endl;
        if (todasLasCanciones) delete[] todasLasCanciones;
        return;
    }

    cout << "\n reproduciendo lista de favoritos..." << endl;
    cout << "canciones en lista: " << cantidadTotal << " (propias: " << lista->getCantidadCanciones()
         << " + seguidas: " << (cantidadTotal - lista->getCantidadCanciones()) << ")" << endl;

    cout << "como quieres reproducir?" << endl;
    cout << "1. en orden original" << endl;
    cout << "2. aleatorio" << endl;
    cout << "selecciona: ";
    int opcionReproduccion;
    cin >> opcionReproduccion;
    cin.ignore();

    bool modoAleatorio = (opcionReproduccion == 2);

    // Configurar lista de reproducción
    reproductor.setListaReproduccion(todasLasCanciones, cantidadTotal, modoAleatorio);

    Cancion* primeraCancion = reproductor.getCancionActualLista();

    if (primeraCancion) {
        reproductor.reproducir(primeraCancion);

        bool reproduciendo = true;
        while (reproduciendo && reproductor.haySiguienteCancion()) {
            cout << "\n--- controles de reproduccion ---" << endl;
            cout << "1. siguiente cancion" << endl;
            cout << "2. cancion anterior" << endl;
            cout << "3. detener reproduccion" << endl;

            if (usuario->Premium()) {
                cout << "4. " << (reproductor.getEstaRepitiendo() ? "desactivar" : "activar") << " repeticion" << endl;
            }

            cout << "selecciona: ";
            int control;
            cin >> control;
            cin.ignore();

            switch (control) {
            case 1:
                if (!reproductor.getEstaRepitiendo()) {
                    reproductor.siguienteCancionLista();
                } else {
                    cout << "modo repeticion activo - manteniendo cancion actual" << endl;
                    if (reproductor.getCancionActual()) {
                        reproductor.reproducir(reproductor.getCancionActual());
                    }
                }
                break;
            case 2:
                if (usuario->Premium()) {
                    if (!reproductor.getEstaRepitiendo()) {
                        if (reproductor.hayCancionAnterior()) {
                            reproductor.cancionAnteriorLista();
                        } else {
                            cout << "No hay más canciones anteriores disponibles." << endl;
                        }
                    } else {
                        cout << "modo repeticion activo - manteniendo cancion actual" << endl;
                        if (reproductor.getCancionActual()) {
                            reproductor.reproducir(reproductor.getCancionActual());
                        }
                    }
                } else {
                    cout << "solo usuarios premium pueden retroceder." << endl;
                }
                break;
            case 3:
                reproduciendo = false;
                reproductor.detener();
                cout << " reproduccion detenida." << endl;
                break;
            case 4:
                if (usuario->Premium()) {
                    bool repitiendo = reproductor.getEstaRepitiendo();
                    reproductor.setEstaRepitiendo(!repitiendo);
                    cout << "modo repeticion: " << (!repitiendo ? "activado" : "desactivado") << endl;

                    if (!repitiendo && reproductor.getCancionActual()) {
                        reproductor.reproducir(reproductor.getCancionActual());
                    }
                } else {
                    cout << "solo usuarios premium pueden usar la funcion de repeticion." << endl;
                }
                break;
            default:
                cout << "opcion no valida." << endl;
            }

        }
    } else {
        cout << "error: no se pudo obtener la primera canción para reproducir." << endl;
    }

    delete[] todasLasCanciones;
}

/**
 * Función principal del programa
 */
int main() {
    // Configurar consola para soportar UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "=================================================================" << endl;
    cout << "=                    BIENVENIDO A UdeATUNES                     =" << endl;
    cout << "=================================================================" << endl;

    Plataforma plataforma;
    SistemaReproduccion reproductor;
    reproductor.setPlataforma(&plataforma);

    string nickName;
    Usuario* usuarioLogueado = nullptr;

    // Cargar usuarios para el login
    plataforma.cargarUsuarios("DatasetDesarrollo/usuarios.txt");

    // Proceso de login
    while (true) {
        cout << "\nIngrese su nickname para iniciar sesion: ";
        getline(cin, nickName);

        usuarioLogueado = plataforma.login(nickName);

        if (usuarioLogueado != nullptr) {
            cout << "\nBienvenido, " << usuarioLogueado->getNickname() << "!" << endl;
            cout << "Tipo de membresia: " << usuarioLogueado->getTipoMembresia() << endl;
            break;
        } else {
            cout << "Usuario no encontrado, intente de nuevo.\n";
        }
    }

    // Cargar el resto de datos
    plataforma.cargarArtistas("DatasetDesarrollo/artistas.txt");
    plataforma.indexarCanciones("DatasetDesarrollo/canciones.txt");
    plataforma.cargarListasFavoritosDesdeArchivo("DatasetDesarrollo/listaFavoritos.txt");
    plataforma.cargarAnuncios("DatasetDesarrollo/anuncios.txt");
    plataforma.indexarAlbumes("DatasetDesarrollo/albumes.txt");

    // Configurar reproductor
    reproductor.setUsuarioActivo(usuarioLogueado);
    reproductor.setListaAnuncios(plataforma.getListaAnuncios(), plataforma.getTotalAnuncios());

    // Ejecutar flujo según tipo de usuario
    if (usuarioLogueado->Premium()) {
        flujoUsuarioPremium(plataforma, reproductor, usuarioLogueado);
    } else {
        flujoUsuarioEstandar(plataforma, reproductor, usuarioLogueado);
    }

    cout << "\n¡Hasta pronto! Gracias por usar UdeATunes." << endl;
    return 0;
}
