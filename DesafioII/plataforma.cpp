#include "Plataforma.h"
using namespace std;

Plataforma::Plataforma() {
    // ==== CANCIONES ====
    capacidadCanciones = 50;
    cantidadCanciones = 0;
    idsCanciones = new int[capacidadCanciones];
    lineasCanciones = new string[capacidadCanciones];

    // ==== CREDITOS ====
    capacidadCreditos = 100;
    cantidadCreditos = 0;
    idCancionesCred = new int[capacidadCreditos];
    lineasCreditos = new string[capacidadCreditos];

    // ==== ALBUMES ====
    capacidadAlbumes = 50;
    cantidadAlbumes = 0;
    idArtistas = new int[capacidadAlbumes];
    idAlbumes = new int[capacidadAlbumes];
    lineasAlbumes = new string[capacidadAlbumes];

    // ==== ARTISTAS ====
    capacidadArtistas = 50;
    cantidadArtistas = 0;
    artistas = new Artista*[capacidadArtistas];

    // ==== USUARIOS ====
    capacidadUsuarios = 100;
    cantidadUsuarios = 0;
    usuarios = new Usuario*[capacidadUsuarios];

    // ==== ANUNCIOS ====
    capacidadAnuncios = 50;
    cantidadAnuncios = 0;
    anuncios = new Anuncio*[capacidadAnuncios];

}

Plataforma::~Plataforma() {
    delete[] idsCanciones;
    delete[] lineasCanciones;
    delete[] idCancionesCred;
    delete[] lineasCreditos;
    delete[] idArtistas;
    delete[] idAlbumes;
    delete[] lineasAlbumes;

    // Liberar artistas
    for (int i = 0; i < cantidadArtistas; i++)
        delete artistas[i];
    delete[] artistas;

    // Liberar usuarios
    for (int i = 0; i < cantidadUsuarios; i++)
        delete usuarios[i];
    delete[] usuarios;

    // Liberar anuncios
    for (int i = 0; i < cantidadAnuncios; i++)
        delete anuncios[i];
    delete[] anuncios;
}

/* ============================================================
   ================== CANCIONES ===============================
   ============================================================ */

void Plataforma::indexarCanciones(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de canciones: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#')
            continue;

        int id = 0;
        int i = 0;
        while (i < (int)linea.size() && linea[i] != '|') {
            if (linea[i] >= '0' && linea[i] <= '9')
                id = id * 10 + (linea[i] - '0');
            i++;
        }

        if (cantidadCanciones >= capacidadCanciones) {
            int nuevaCap = capacidadCanciones * 2;
            int* nuevoIds = new int[nuevaCap];
            string* nuevasLineas = new string[nuevaCap];

            for (int j = 0; j < cantidadCanciones; j++) {
                nuevoIds[j] = idsCanciones[j];
                nuevasLineas[j] = lineasCanciones[j];
            }

            delete[] idsCanciones;
            delete[] lineasCanciones;
            idsCanciones = nuevoIds;
            lineasCanciones = nuevasLineas;
            capacidadCanciones = nuevaCap;
        }

        idsCanciones[cantidadCanciones] = id;
        lineasCanciones[cantidadCanciones] = linea;
        cantidadCanciones++;
    }

    archivo.close();
}

Cancion* Plataforma::cargarCancion(int id) {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (idsCanciones[i] == id) {
            return parsearCancion(lineasCanciones[i]);
        }
    }
    return nullptr;
}

Cancion* Plataforma::parsearCancion(const string& linea) {
    if (linea.empty())
        return nullptr;

    string partes[6];
    int indice = 0;
    string actual = "";

    for (int i = 0; i < (int)linea.size(); i++) {
        char c = linea[i];
        if (c == '|') {
            partes[indice++] = actual;
            actual = "";
            if (indice >= 6) break;
        } else actual += c;
    }
    partes[indice] = actual;

    try {
        int id = stoi(partes[0]);
        float duracion = stof(partes[2]);
        int reproducciones = stoi(partes[5]);

        Cancion* nueva = new Cancion(id, partes[1], duracion, partes[3], partes[4]);
        nueva->setReproducciones(reproducciones);
        return nueva;
    } catch (...) {
        cout << "Error al parsear cancion" << endl;
        return nullptr;
    }
}

/* ============================================================
   ================== ARTISTAS ================================
   ============================================================ */

void Plataforma::cargarArtistas(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de artistas: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#')
            continue;

        string partes[6];
        int indice = 0;
        string actual = "";

        for (int i = 0; i < (int)linea.size(); i++) {
            char c = linea[i];
            if (c == '|') {
                partes[indice++] = actual;
                actual = "";
                if (indice >= 6) break;
            } else actual += c;
        }
        partes[indice] = actual;

        try {
            int idArtista = stoi(partes[0]);
            int edad = stoi(partes[2]);
            int seguidores = stoi(partes[4]);
            int posicionGlobal = stoi(partes[5]);

            Artista* nuevo = new Artista(idArtista, partes[1].c_str(), edad, partes[3].c_str(), seguidores, posicionGlobal);

            if (cantidadArtistas >= capacidadArtistas) {
                int nuevaCap = capacidadArtistas * 2;
                Artista** nuevoArr = new Artista*[nuevaCap];

                for (int j = 0; j < cantidadArtistas; j++)
                    nuevoArr[j] = artistas[j];

                delete[] artistas;
                artistas = nuevoArr;
                capacidadArtistas = nuevaCap;
            }

            artistas[cantidadArtistas++] = nuevo;
        } catch (...) {
            cout << "Error al procesar linea de artistas: " << linea << endl;
        }
    }

    archivo.close();
}

Artista* Plataforma::buscarArtista(int idArtista) {
    for (int i = 0; i < cantidadArtistas; i++) {
        if (artistas[i]->getIdArtista() == idArtista)
            return artistas[i];
    }
    return nullptr;
}

/* ============================================================
   ================== USUARIOS ================================
   ============================================================ */

void Plataforma::cargarUsuarios(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de usuarios: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#')
            continue;

        string partes[5];
        int indice = 0;
        string actual = "";

        for (int i = 0; i < (int)linea.size(); i++) {
            char c = linea[i];
            if (c == '|') {
                partes[indice++] = actual;
                actual = "";
                if (indice >= 5) break;
            } else actual += c;
        }
        partes[indice] = actual;

        try {
            Usuario* nuevo = new Usuario(partes[0], partes[1], partes[2],
                                         partes[3], partes[4]);

            if (cantidadUsuarios >= capacidadUsuarios) {
                int nuevaCap = capacidadUsuarios * 2;
                Usuario** nuevoArr = new Usuario*[nuevaCap];

                for (int j = 0; j < cantidadUsuarios; j++)
                    nuevoArr[j] = usuarios[j];

                delete[] usuarios;
                usuarios = nuevoArr;
                capacidadUsuarios = nuevaCap;
            }

            usuarios[cantidadUsuarios++] = nuevo;
        } catch (...) {
            cout << "Error al procesar linea de usuarios: " << linea << endl;
        }
    }

    archivo.close();
}

Usuario* Plataforma::buscarUsuario(const string& nickname) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname)
            return usuarios[i];
    }
    return nullptr;
}

/* ============================================================
   ================== ANUNCIOS ================================
   ============================================================ */

void Plataforma::cargarAnuncios(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de anuncios: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#')
            continue;

        string texto = "";
        string categoria = "";
        bool enCategoria = false;

        for (int i = 0; i < (int)linea.size(); i++) {
            if (linea[i] == ';') {
                enCategoria = true;
            } else {
                if (enCategoria)
                    categoria += linea[i];
                else
                    texto += linea[i];
            }
        }

        try {
            Anuncio* nuevo = new Anuncio(texto, categoria);

            if (cantidadAnuncios >= capacidadAnuncios) {
                int nuevaCap = capacidadAnuncios * 2;
                Anuncio** nuevoArr = new Anuncio*[nuevaCap];

                for (int j = 0; j < cantidadAnuncios; j++)
                    nuevoArr[j] = anuncios[j];

                delete[] anuncios;
                anuncios = nuevoArr;
                capacidadAnuncios = nuevaCap;
            }

            anuncios[cantidadAnuncios++] = nuevo;
        } catch (...) {
            cout << "Error al procesar linea de anuncios: " << linea << endl;
        }
    }

    archivo.close();
}

Anuncio* Plataforma::obtenerAnuncioAleatorio(int ultimoIndice) {
    if (cantidadAnuncios == 0)
        return nullptr;

    int indiceSeleccionado = Anuncio::seleccionarAleatorio(anuncios, cantidadAnuncios, ultimoIndice);

    if (indiceSeleccionado >= 0 && indiceSeleccionado < cantidadAnuncios)
        return anuncios[indiceSeleccionado];

    return nullptr;
}

/* ============================================================
   ================== CREDITOS ================================
   ============================================================ */

void Plataforma::indexarCreditos(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de créditos: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#')
            continue;

        int idCancion = 0;
        int i = 0;
        while (i < (int)linea.size() && linea[i] != '|') {
            if (linea[i] >= '0' && linea[i] <= '9')
                idCancion = idCancion * 10 + (linea[i] - '0');
            i++;
        }

        if (cantidadCreditos >= capacidadCreditos) {
            int nuevaCap = capacidadCreditos * 2;
            int* nuevoIds = new int[nuevaCap];
            string* nuevasLineas = new string[nuevaCap];

            for (int j = 0; j < cantidadCreditos; j++) {
                nuevoIds[j] = idCancionesCred[j];
                nuevasLineas[j] = lineasCreditos[j];
            }

            delete[] idCancionesCred;
            delete[] lineasCreditos;
            idCancionesCred = nuevoIds;
            lineasCreditos = nuevasLineas;
            capacidadCreditos = nuevaCap;
        }

        idCancionesCred[cantidadCreditos] = idCancion;
        lineasCreditos[cantidadCreditos] = linea;
        cantidadCreditos++;
    }

    archivo.close();
}

Credito* Plataforma::cargarCredito(int idCancion) {
    for (int i = 0; i < cantidadCreditos; i++) {
        if (idCancionesCred[i] == idCancion) {
            return parsearCredito(lineasCreditos[i]);
        }
    }
    return nullptr;
}

Credito* Plataforma::parsearCredito(const string& linea) {
    if (linea.empty())
        return nullptr;

    string partes[5];
    int indice = 0;
    string actual = "";

    for (int i = 0; i < (int)linea.size(); i++) {
        char c = linea[i];
        if (c == '|') {
            partes[indice++] = actual;
            actual = "";
            if (indice >= 5) break;
        } else actual += c;
    }
    partes[indice] = actual;

    try {
        int idCancion = stoi(partes[0]);
        Credito* nuevo = new Credito(partes[1], partes[2], partes[3], partes[4]);
        nuevo->setIdCancion(idCancion);
        return nuevo;
    } catch (...) {
        cout << "Error al parsear credito" << endl;
        return nullptr;
    }
}

/* ============================================================
   ================== ALBUMES =================================
   ============================================================ */

void Plataforma::indexarAlbumes(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de álbumes: " << ruta << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty() || linea[0] == '#')
            continue;

        int idArtista = 0;
        int idAlbum = 0;
        int i = 0;

        while (i < (int)linea.size() && linea[i] != '|') {
            if (linea[i] >= '0' && linea[i] <= '9')
                idArtista = idArtista * 10 + (linea[i] - '0');
            i++;
        }
        i++;

        while (i < (int)linea.size() && linea[i] != '|') {
            if (linea[i] >= '0' && linea[i] <= '9')
                idAlbum = idAlbum * 10 + (linea[i] - '0');
            i++;
        }

        if (cantidadAlbumes >= capacidadAlbumes) {
            int nuevaCap = capacidadAlbumes * 2;
            int* nuevosIdArt = new int[nuevaCap];
            int* nuevosIdAlb = new int[nuevaCap];
            string* nuevasLineas = new string[nuevaCap];

            for (int j = 0; j < cantidadAlbumes; j++) {
                nuevosIdArt[j] = idArtistas[j];
                nuevosIdAlb[j] = idAlbumes[j];
                nuevasLineas[j] = lineasAlbumes[j];
            }

            delete[] idArtistas;
            delete[] idAlbumes;
            delete[] lineasAlbumes;
            idArtistas = nuevosIdArt;
            idAlbumes = nuevosIdAlb;
            lineasAlbumes = nuevasLineas;
            capacidadAlbumes = nuevaCap;
        }

        idArtistas[cantidadAlbumes] = idArtista;
        idAlbumes[cantidadAlbumes] = idAlbum;
        lineasAlbumes[cantidadAlbumes] = linea;
        cantidadAlbumes++;
    }

    archivo.close();
}

Album* Plataforma::cargarAlbum(int idArtista, int idAlbum) {
    for (int i = 0; i < cantidadAlbumes; i++) {
        if (idArtistas[i] == idArtista && idAlbumes[i] == idAlbum) {
            return parsearAlbum(lineasAlbumes[i]);
        }
    }
    return nullptr;
}

Album* Plataforma::parsearAlbum(const string& linea) {
    if (linea.empty())
        return nullptr;

    string partes[8];
    int indice = 0;
    string actual = "";

    for (int i = 0; i < (int)linea.size(); i++) {
        char c = linea[i];
        if (c == '|') {
            partes[indice++] = actual;
            actual = "";
            if (indice >= 8) break;
        } else actual += c;
    }
    partes[indice] = actual;

    try {
        int idAlbum = stoi(partes[1]);
        float puntuacion = stof(partes[6]);

        Album* nuevo = new Album(idAlbum, partes[2].c_str(), partes[3].c_str(),
                                 partes[4].c_str(), partes[5].c_str());
        nuevo->setPuntuacion(puntuacion);

        string generosStr = partes[7];
        string generoActual = "";

        for (int i = 0; i < (int)generosStr.size(); i++) {
            if (generosStr[i] == ',') {
                if (!generoActual.empty()) {
                    nuevo->agregarGenero(generoActual.c_str());
                    generoActual = "";
                }
            } else {
                generoActual += generosStr[i];
            }
        }
        if (!generoActual.empty()) {
            nuevo->agregarGenero(generoActual.c_str());
        }

        return nuevo;
    } catch (...) {
        cout << "Error al parsear álbum" << endl;
        return nullptr;
    }
}

/* ============================================================
   ================== PERSISTENCIA LISTAS =====================
   ============================================================ */

void Plataforma::cargarListasFavoritosDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo de listas de favoritos: " << ruta << endl;
        return;
    }

    string linea;
    Usuario* usuarioActual = nullptr;

    while (getline(archivo, linea)) {
        if (linea.empty())
            continue;

        // ===== CASO 1: usuario o usuario,usuarioSigueA =====
        if (!(linea[0] >= '0' && linea[0] <= '9')) {

            size_t coma = linea.find(',');

            if (coma != string::npos) {
                // hay seguimiento
                string user = linea.substr(0, coma);
                string seguido = linea.substr(coma + 1);

                usuarioActual = buscarUsuario(user);
                Usuario* seguidoUsuario = buscarUsuario(seguido);

                if (usuarioActual == nullptr) {
                    cout << "Usuario no encontrado: " << user << endl;
                    continue;
                }

                if (seguidoUsuario != nullptr) {
                    usuarioActual->getListaFavoritos()->seguirLista(seguidoUsuario->getListaFavoritos());
                }
            }
            else {
                // no hay seguimiento, solo usuario
                usuarioActual = buscarUsuario(linea);
                if (usuarioActual == nullptr) {
                    cout << "Usuario no encontrado: " << linea << endl;
                }
            }

            continue;
        }

        // ===== CASO 2: línea numérica → ID de canción =====
        if (usuarioActual != nullptr) {
            int idCancion = stoi(linea);
            Cancion* c = cargarCancion(idCancion);
            if (c != nullptr)
                usuarioActual->getListaFavoritos()->agregarCancion(c);
        }
    }

    archivo.close();
}

void Plataforma::guardarListasFavoritosEnArchivo(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar: " << ruta << endl;
        return;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {
        Usuario* u = usuarios[i];
        if (!u) continue;

        ListaFavoritos* lista = u->getListaFavoritos();
        if (!lista) continue;

        // Detectar si sigue una lista
        ListaFavoritos** seguidas = lista->getListasSeguidas();
        Usuario* seguido = nullptr;

        if (seguidas[0] != nullptr)
            seguido = seguidas[0]->getUsuarioPropietario();

        // --------- IMPRIMIR CABECERA ---------
        if (seguido != nullptr)
            archivo << u->getNickname() << "," << seguido->getNickname() << "\n";
        else
            archivo << u->getNickname() << "\n";

        // --------- IMPRIMIR CANCIONES ---------
        Cancion** canciones = lista->getCanciones();
        for (int j = 0; canciones[j] != nullptr; j++)
            archivo << canciones[j]->getIdCancion() << "\n";

        archivo << "\n"; // separador ENTRE usuarios
    }

    archivo.close();
}


/* ============================================================
   ================== GUARDAR CANCIONES =======================
   ============================================================ */
void Plataforma::guardarCanciones(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar canciones: " << ruta << endl;
        return;
    }

    // Formato: idCancion|nombre|duracion|ruta128|ruta320|reproducciones

    for (int i = 0; i < cantidadCanciones; i++) {
        Cancion* c = cargarCancion(idsCanciones[i]);
        if (c != nullptr) {
            archivo << c->getIdCancion() << "|"
                    << c->getNombre() << "|"
                    << c->getDuracion() << "|"
                    << c->getRuta128() << "|"
                    << c->getRuta320() << "|"
                    << c->getReproducciones() << "\n";
            delete c;
        }
    }

    archivo.close();
}

/* ============================================================
   ================== GUARDAR CREDITOS ========================
   ============================================================ */
void Plataforma::guardarCreditos(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar créditos: " << ruta << endl;
        return;
    }


    // Formato: idCancion|nombre|apellido|tipo|codigoAfiliacion

    for (int i = 0; i < cantidadCreditos; i++) {
        Credito* cred = parsearCredito(lineasCreditos[i]);
        if (cred != nullptr) {
            archivo << cred->getIdCancion() << "|"
                    << cred->getNombre() << "|"
                    << cred->getApellido() << "|"
                    << cred->getTipo() << "|"
                    << cred->getCodigoAfiliacion() << "\n";
            delete cred;
        }
    }

    archivo.close();
}

/* ============================================================
   ================== GUARDAR ALBUMES =========================
   ============================================================ */
void Plataforma::guardarAlbumes(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar álbumes: " << ruta << endl;
        return;
    }

    // Formato: idArtista|idAlbum|nombre|fechaLanzamiento|selloDisquero|portadaRuta|puntuacion|generos

    for (int i = 0; i < cantidadAlbumes; i++) {
        Album* alb = cargarAlbum(idArtistas[i], idAlbumes[i]);
        if (alb != nullptr) {
            archivo << idArtistas[i] << "|"
                    << alb->getIdAlbum() << "|"
                    << alb->getNombre() << "|"
                    << alb->getFechaLanzamiento() << "|"
                    << alb->getSelloDisquero() << "|"
                    << alb->getPortadaRuta() << "|"
                    << alb->getPuntuacion() << "|";

            // Guardar géneros separados por comas
            int cantGeneros = alb->getCantidadGeneros();
            char** generos = alb->getGeneros();

            if (cantGeneros > 0) {
                archivo << generos[0];
                for (int j = 1; j < cantGeneros; j++) {
                    archivo << "," << generos[j];
                }
            }

            archivo << "\n";
            delete alb;
        }
    }

    archivo.close();
}

/* ============================================================
   ================== GUARDAR ARTISTAS ========================
   ============================================================ */
void Plataforma::guardarArtistas(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar artistas: " << ruta << endl;
        return;
    }

    // Formato: idArtista|nombre|edad|nacionalidad|seguidores|posicionGlobal

    for (int i = 0; i < cantidadArtistas; i++) {
        Artista* art = artistas[i];
        if (art != nullptr) {
            archivo << art->getIdArtista() << "|"
                    << art->getNombre() << "|"
                    << art->getEdad() << "|"
                    << art->getPaisOrigen() << "|"
                    << art->getSeguidores() << "|"
                    << art->getPosicionGlobal() << "\n";
        }
    }

    archivo.close();
}

/* ============================================================
   ================== GUARDAR USUARIOS ========================
   ============================================================ */
void Plataforma::guardarUsuarios(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar usuarios: " << ruta << endl;
        return;
    }

    // Formato: nickname|tipoMembresia|ciudad|pais|fechaRegistro

    for (int i = 0; i < cantidadUsuarios; i++) {
        Usuario* usr = usuarios[i];
        if (usr != nullptr) {
            archivo << usr->getNickname() << "|"
                    << usr->getTipoMembresia() << "|"
                    << usr->getCiudad() << "|"
                    << usr->getPais() << "|"
                    << usr->getFechaRegistro() << "\n";
        }
    }

    archivo.close();
}

/* ============================================================
   ================== GUARDAR ANUNCIOS ========================
   ============================================================ */
void Plataforma::guardarAnuncios(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar anuncios: " << ruta << endl;
        return;
    }

    // Formato: textoAnuncio;categoria

    for (int i = 0; i < cantidadAnuncios; i++) {
        Anuncio* anun = anuncios[i];
        if (anun != nullptr) {
            archivo << anun->getTexto() << ";"
                    << anun->getCategoria() << "\n";
        }
    }

    archivo.close();
}


/* ============================================================
   MÉTODOS AUXILIARES PARA ACTUALIZAR LÍNEAS INDEXADAS
   (Usar cuando se modifiquen canciones, créditos o álbumes)
   ============================================================ */

// Actualizar línea de canción después de modificarla
void Plataforma::actualizarLineaCancion(int idCancion) {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (idsCanciones[i] == idCancion) {
            Cancion* c = cargarCancion(idCancion);
            if (c != nullptr) {
                // Reconstruir la línea con los datos actualizados
                lineasCanciones[i] = to_string(c->getIdCancion()) + "|" +
                                     string(c->getNombre()) + "|" +
                                     to_string(c->getDuracion()) + "|" +
                                     string(c->getRuta128()) + "|" +
                                     string(c->getRuta320()) + "|" +
                                     to_string(c->getReproducciones());
                delete c;
            }
            break;
        }
    }
}

// Actualizar línea de crédito después de modificarlo
void Plataforma::actualizarLineaCredito(int idCancion) {
    for (int i = 0; i < cantidadCreditos; i++) {
        if (idCancionesCred[i] == idCancion) {
            Credito* cred = cargarCredito(idCancion);
            if (cred != nullptr) {
                lineasCreditos[i] = to_string(cred->getIdCancion()) + "|" +
                                    string(cred->getNombre()) + "|" +
                                    string(cred->getApellido()) + "|" +
                                    string(cred->getTipo()) + "|" +
                                    string(cred->getCodigoAfiliacion());
                delete cred;
            }
            break;
        }
    }
}

// Actualizar línea de álbum después de modificarlo
void Plataforma::actualizarLineaAlbum(int idArtista, int idAlbum) {
    for (int i = 0; i < cantidadAlbumes; i++) {
        if (idArtistas[i] == idArtista && idAlbumes[i] == idAlbum) {
            Album* alb = cargarAlbum(idArtista, idAlbum);
            if (alb != nullptr) {
                // Reconstruir línea con datos actualizados
                string lineaNueva = to_string(idArtista) + "|" +
                                    to_string(alb->getIdAlbum()) + "|" +
                                    string(alb->getNombre()) + "|" +
                                    string(alb->getFechaLanzamiento()) + "|" +
                                    string(alb->getSelloDisquero()) + "|" +
                                    string(alb->getPortadaRuta()) + "|" +
                                    to_string(alb->getPuntuacion()) + "|";

                // Agregar géneros
                int cantGeneros = alb->getCantidadGeneros();
                char** generos = alb->getGeneros();
                if (cantGeneros > 0) {
                    lineaNueva += string(generos[0]);
                    for (int j = 1; j < cantGeneros; j++) {
                        lineaNueva += "," + string(generos[j]);
                    }
                }

                lineasAlbumes[i] = lineaNueva;
                delete alb;
            }
            break;
        }
    }
}


/* ============================================================
   MÉTODOS PARA AGREGAR NUEVOS REGISTROS
   ============================================================ */

// Agregar nueva canción al sistema
void Plataforma::agregarCancion(Cancion* cancion) {
    if (cancion == nullptr) return;

    if (cantidadCanciones >= capacidadCanciones) {
        int nuevaCap = capacidadCanciones * 2;
        int* nuevoIds = new int[nuevaCap];
        string* nuevasLineas = new string[nuevaCap];

        for (int j = 0; j < cantidadCanciones; j++) {
            nuevoIds[j] = idsCanciones[j];
            nuevasLineas[j] = lineasCanciones[j];
        }

        delete[] idsCanciones;
        delete[] lineasCanciones;
        idsCanciones = nuevoIds;
        lineasCanciones = nuevasLineas;
        capacidadCanciones = nuevaCap;
    }

    // Crear línea para indexar
    string linea = to_string(cancion->getIdCancion()) + "|" +
                   string(cancion->getNombre()) + "|" +
                   to_string(cancion->getDuracion()) + "|" +
                   string(cancion->getRuta128()) + "|" +
                   string(cancion->getRuta320()) + "|" +
                   to_string(cancion->getReproducciones());

    idsCanciones[cantidadCanciones] = cancion->getIdCancion();
    lineasCanciones[cantidadCanciones] = linea;
    cantidadCanciones++;

    cout << "Canción agregada: " << cancion->getNombre() << endl;
}

// Agregar nuevo álbum al sistema
void Plataforma::agregarAlbum(int idArtista, Album* album) {
    if (album == nullptr) return;

    if (cantidadAlbumes >= capacidadAlbumes) {
        int nuevaCap = capacidadAlbumes * 2;
        int* nuevosIdArt = new int[nuevaCap];
        int* nuevosIdAlb = new int[nuevaCap];
        string* nuevasLineas = new string[nuevaCap];

        for (int j = 0; j < cantidadAlbumes; j++) {
            nuevosIdArt[j] = idArtistas[j];
            nuevosIdAlb[j] = idAlbumes[j];
            nuevasLineas[j] = lineasAlbumes[j];
        }

        delete[] idArtistas;
        delete[] idAlbumes;
        delete[] lineasAlbumes;
        idArtistas = nuevosIdArt;
        idAlbumes = nuevosIdAlb;
        lineasAlbumes = nuevasLineas;
        capacidadAlbumes = nuevaCap;
    }

    // Crear línea para indexar
    string linea = to_string(idArtista) + "|" +
                   to_string(album->getIdAlbum()) + "|" +
                   string(album->getNombre()) + "|" +
                   string(album->getFechaLanzamiento()) + "|" +
                   string(album->getSelloDisquero()) + "|" +
                   string(album->getPortadaRuta()) + "|" +
                   to_string(album->getPuntuacion()) + "|";

    // Agregar géneros
    int cantGeneros = album->getCantidadGeneros();
    char** generos = album->getGeneros();
    if (cantGeneros > 0) {
        linea += string(generos[0]);
        for (int j = 1; j < cantGeneros; j++) {
            linea += "," + string(generos[j]);
        }
    }

    idArtistas[cantidadAlbumes] = idArtista;
    idAlbumes[cantidadAlbumes] = album->getIdAlbum();
    lineasAlbumes[cantidadAlbumes] = linea;
    cantidadAlbumes++;

    cout << "Álbum agregado: " << album->getNombre() << endl;
}

// Agregar nuevo artista al sistema
void Plataforma::agregarArtista(Artista* artista) {
    if (artista == nullptr) return;

    if (cantidadArtistas >= capacidadArtistas) {
        int nuevaCap = capacidadArtistas * 2;
        Artista** nuevoArr = new Artista*[nuevaCap];

        for (int j = 0; j < cantidadArtistas; j++)
            nuevoArr[j] = artistas[j];

        delete[] artistas;
        artistas = nuevoArr;
        capacidadArtistas = nuevaCap;
    }

    artistas[cantidadArtistas++] = artista;
    cout << "Artista agregado: " << artista->getNombre() << endl;
}

// Agregar nuevo usuario al sistema
void Plataforma::agregarUsuario(Usuario* usuario) {
    if (usuario == nullptr) return;

    if (cantidadUsuarios >= capacidadUsuarios) {
        int nuevaCap = capacidadUsuarios * 2;
        Usuario** nuevoArr = new Usuario*[nuevaCap];

        for (int j = 0; j < cantidadUsuarios; j++)
            nuevoArr[j] = usuarios[j];

        delete[] usuarios;
        usuarios = nuevoArr;
        capacidadUsuarios = nuevaCap;
    }

    usuarios[cantidadUsuarios++] = usuario;
    cout << "Usuario agregado: " << usuario->getNickname() << endl;
}

/* ============================================================
   MÉTODOS PARA ELIMINAR REGISTROS
   ============================================================ */

// Eliminar canción por ID
bool Plataforma::eliminarCancion(int idCancion) {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (idsCanciones[i] == idCancion) {
            // Mover todos los elementos una posición atrás
            for (int j = i; j < cantidadCanciones - 1; j++) {
                idsCanciones[j] = idsCanciones[j + 1];
                lineasCanciones[j] = lineasCanciones[j + 1];
            }
            cantidadCanciones--;
            cout << "Canción eliminada: ID " << idCancion << endl;
            return true;
        }
    }
    return false;
}

// Eliminar artista por ID
bool Plataforma::eliminarArtista(int idArtista) {
    for (int i = 0; i < cantidadArtistas; i++) {
        if (artistas[i]->getIdArtista() == idArtista) {
            delete artistas[i];

            // Mover todos los elementos una posición atrás
            for (int j = i; j < cantidadArtistas - 1; j++) {
                artistas[j] = artistas[j + 1];
            }
            cantidadArtistas--;
            cout << "Artista eliminado: ID " << idArtista << endl;
            return true;
        }
    }
    return false;
}

// Eliminar usuario por nickname
bool Plataforma::eliminarUsuario(const string& nickname) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname) {
            delete usuarios[i];

            // Mover todos los elementos una posición atrás
            for (int j = i; j < cantidadUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            cantidadUsuarios--;
            cout << "Usuario eliminado: " << nickname << endl;
            return true;
        }
    }
    return false;
}

// Login

Usuario* Plataforma::login(const string& nickname) {
    Usuario* usuario = buscarUsuario(nickname);
    if (usuario != nullptr) {
        return usuario;
    }
        return nullptr;
}


Cancion* Plataforma::seleccionarCancionAleatoria(int ultimoID) {
    if (cantidadCanciones == 0)
        return nullptr;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, cantidadCanciones - 1);

    int indice;
    int idSeleccionado;

    do {
        indice = dist(gen);
        idSeleccionado = idsCanciones[indice];
    } while (cantidadCanciones > 1 && idSeleccionado == ultimoID);

    return cargarCancion(idSeleccionado);
}

