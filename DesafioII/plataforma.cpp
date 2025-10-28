#include "Plataforma.h"
using namespace std;

// constructor y destructor
Plataforma::Plataforma() {
    capacidadCanciones = 50;
    cantidadCanciones = 0;
    idsCanciones = new int[capacidadCanciones];
    lineasCanciones = new string[capacidadCanciones];

    capacidadCreditos = 100;
    cantidadCreditos = 0;
    idCancionesCred = new int[capacidadCreditos];
    lineasCreditos = new string[capacidadCreditos];

    capacidadAlbumes = 50;
    cantidadAlbumes = 0;
    idArtistas = new int[capacidadAlbumes];
    idAlbumes = new int[capacidadAlbumes];
    lineasAlbumes = new string[capacidadAlbumes];

    capacidadArtistas = 50;
    cantidadArtistas = 0;
    artistas = new Artista*[capacidadArtistas];

    capacidadUsuarios = 100;
    cantidadUsuarios = 0;
    usuarios = new Usuario*[capacidadUsuarios];

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

    for (int i = 0; i < cantidadArtistas; i++)
        delete artistas[i];
    delete[] artistas;

    for (int i = 0; i < cantidadUsuarios; i++)
        delete usuarios[i];
    delete[] usuarios;

    for (int i = 0; i < cantidadAnuncios; i++)
        delete anuncios[i];
    delete[] anuncios;
}

// ====================== canciones ==========================
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
    ordenarCancionesPorId();
}

void Plataforma::ordenarCancionesPorId() {
    if (cantidadCanciones <= 1) return;
    quickSortCanciones(0, cantidadCanciones - 1);
}

void Plataforma::quickSortCanciones(int izq, int der) {
    if (izq >= der) return;

    int pivote = particionCanciones(izq, der);
    quickSortCanciones(izq, pivote - 1);
    quickSortCanciones(pivote + 1, der);
}

int Plataforma::particionCanciones(int izq, int der) {
    int pivote = idsCanciones[der];
    int i = izq - 1;

    for (int j = izq; j < der; j++) {
        if (idsCanciones[j] <= pivote) {
            i++;

            int tempId = idsCanciones[i];
            idsCanciones[i] = idsCanciones[j];
            idsCanciones[j] = tempId;

            string tempLinea = lineasCanciones[i];
            lineasCanciones[i] = lineasCanciones[j];
            lineasCanciones[j] = tempLinea;
        }
    }

    int tempId = idsCanciones[i + 1];
    idsCanciones[i + 1] = idsCanciones[der];
    idsCanciones[der] = tempId;

    string tempLinea = lineasCanciones[i + 1];
    lineasCanciones[i + 1] = lineasCanciones[der];
    lineasCanciones[der] = tempLinea;

    return i + 1;
}

Cancion* Plataforma::cargarCancion(int id) {
    int izq = 0;
    int der = cantidadCanciones - 1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;

        if (idsCanciones[mid] == id) {
            return parsearCancion(lineasCanciones[mid]);
        }

        if (idsCanciones[mid] < id) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    return nullptr;
}

Cancion* Plataforma::cargarCancion(int id, int& iteraciones) {
    iteraciones = 0;
    int izq = 0;
    int der = cantidadCanciones - 1;

    while (izq <= der) {
        iteraciones++;
        int mid = izq + (der - izq) / 2;

        if (idsCanciones[mid] == id) {
            return parsearCancion(lineasCanciones[mid]);
        }

        if (idsCanciones[mid] < id) {
            izq = mid + 1;
        } else {
            der = mid - 1;
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

void Plataforma::guardarCanciones(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar canciones: " << ruta << endl;
        return;
    }

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

// ========================== álbumes =========================
void Plataforma::indexarAlbumes(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de albumes: " << ruta << endl;
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
    ordenarAlbumesPorId();
}

long long Plataforma::combinarIds(int idArtista, int idAlbum) {
    return ((long long)idArtista * 100) + idAlbum;
}

void Plataforma::ordenarAlbumesPorId() {
    if (cantidadAlbumes <= 1) return;
    quickSortAlbumes(0, cantidadAlbumes - 1);
}

void Plataforma::quickSortAlbumes(int izq, int der) {
    if (izq >= der) return;

    int pivote = particionAlbumes(izq, der);
    quickSortAlbumes(izq, pivote - 1);
    quickSortAlbumes(pivote + 1, der);
}

int Plataforma::particionAlbumes(int izq, int der) {
    long long pivote = combinarIds(idArtistas[der], idAlbumes[der]);
    int i = izq - 1;

    for (int j = izq; j < der; j++) {
        long long actual = combinarIds(idArtistas[j], idAlbumes[j]);
        if (actual <= pivote) {
            i++;
            int tempArt = idArtistas[i];
            idArtistas[i] = idArtistas[j];
            idArtistas[j] = tempArt;

            int tempAlb = idAlbumes[i];
            idAlbumes[i] = idAlbumes[j];
            idAlbumes[j] = tempAlb;

            string tempLinea = lineasAlbumes[i];
            lineasAlbumes[i] = lineasAlbumes[j];
            lineasAlbumes[j] = tempLinea;
        }
    }

    int tempArt = idArtistas[i + 1];
    idArtistas[i + 1] = idArtistas[der];
    idArtistas[der] = tempArt;

    int tempAlb = idAlbumes[i + 1];
    idAlbumes[i + 1] = idAlbumes[der];
    idAlbumes[der] = tempAlb;

    string tempLinea = lineasAlbumes[i + 1];
    lineasAlbumes[i + 1] = lineasAlbumes[der];
    lineasAlbumes[der] = tempLinea;

    return i + 1;
}

Album* Plataforma::cargarAlbum(int idArtista, int idAlbum) {
    long long idBuscado = combinarIds(idArtista, idAlbum);

    int izq = 0;
    int der = cantidadAlbumes - 1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        long long idActual = combinarIds(idArtistas[mid], idAlbumes[mid]);

        if (idActual == idBuscado) {
            return parsearAlbum(lineasAlbumes[mid]);
        }

        if (idActual < idBuscado) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    return nullptr;
}

Album* Plataforma::cargarAlbum(int idArtista, int idAlbum, int& iteraciones) {
    iteraciones = 0;
    long long idBuscado = combinarIds(idArtista, idAlbum);

    int izq = 0;
    int der = cantidadAlbumes - 1;

    while (izq <= der) {
        iteraciones++;
        int mid = izq + (der - izq) / 2;
        long long idActual = combinarIds(idArtistas[mid], idAlbumes[mid]);

        if (idActual == idBuscado) {
            return parsearAlbum(lineasAlbumes[mid]);
        }

        if (idActual < idBuscado) {
            izq = mid + 1;
        } else {
            der = mid - 1;
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

void Plataforma::guardarAlbumes(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar albumes: " << ruta << endl;
        return;
    }

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

// ========================== créditos =======================
void Plataforma::indexarCreditos(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir el archivo de creditos: " << ruta << endl;
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
    ordenarCreditosPorId();
}

void Plataforma::ordenarCreditosPorId() {
    if (cantidadCreditos <= 1) return;
    quickSortCreditos(0, cantidadCreditos - 1);
}

void Plataforma::quickSortCreditos(int izq, int der) {
    if (izq >= der) return;

    int pivote = particionCreditos(izq, der);
    quickSortCreditos(izq, pivote - 1);
    quickSortCreditos(pivote + 1, der);
}

int Plataforma::particionCreditos(int izq, int der) {
    int pivote = idCancionesCred[der];
    int i = izq - 1;

    for (int j = izq; j < der; j++) {
        if (idCancionesCred[j] <= pivote) {
            i++;
            int tempId = idCancionesCred[i];
            idCancionesCred[i] = idCancionesCred[j];
            idCancionesCred[j] = tempId;

            string tempLinea = lineasCreditos[i];
            lineasCreditos[i] = lineasCreditos[j];
            lineasCreditos[j] = tempLinea;
        }
    }

    int tempId = idCancionesCred[i + 1];
    idCancionesCred[i + 1] = idCancionesCred[der];
    idCancionesCred[der] = tempId;

    string tempLinea = lineasCreditos[i + 1];
    lineasCreditos[i + 1] = lineasCreditos[der];
    lineasCreditos[der] = tempLinea;

    return i + 1;
}

Credito* Plataforma::cargarCredito(int idCancion) {
    int izq = 0;
    int der = cantidadCreditos - 1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;

        if (idCancionesCred[mid] == idCancion) {
            return parsearCredito(lineasCreditos[mid]);
        }

        if (idCancionesCred[mid] < idCancion) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    return nullptr;
}

Credito* Plataforma::cargarCredito(int idCancion, int& iteraciones) {
    iteraciones = 0;
    int izq = 0;
    int der = cantidadCreditos - 1;

    while (izq <= der) {
        iteraciones++;
        int mid = izq + (der - izq) / 2;

        if (idCancionesCred[mid] == idCancion) {
            return parsearCredito(lineasCreditos[mid]);
        }

        if (idCancionesCred[mid] < idCancion) {
            izq = mid + 1;
        } else {
            der = mid - 1;
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

void Plataforma::guardarCreditos(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar créditos: " << ruta << endl;
        return;
    }

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

// ================== artistas ================================
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

void Plataforma::guardarArtistas(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar artistas: " << ruta << endl;
        return;
    }

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

// ================== usuarios ================================
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

void Plataforma::guardarUsuarios(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar usuarios: " << ruta << endl;
        return;
    }

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

// ================== anuncios ================================
void Plataforma::cargarAnuncios(const string& ruta) {
    ifstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "No se pudo abrir el archivo de anuncios: " << ruta << endl;
        return;
    }

    string linea;
    int lineasProcesadas = 0;

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
            lineasProcesadas++;

        } catch (...) {
            cout << "Error al procesar linea de anuncios: " << linea << endl;
        }
    }

    archivo.close();
}

Anuncio* Plataforma::obtenerAnuncioAleatorio(int ultimoIndice) {
    if (cantidadAnuncios == 0) {
        cout << "No hay anuncios disponibles" << endl;
        return nullptr;
    }

    int indiceSeleccionado = Anuncio::seleccionarAleatorio(anuncios, cantidadAnuncios, ultimoIndice);

    if (indiceSeleccionado >= 0 && indiceSeleccionado < cantidadAnuncios)
        return anuncios[indiceSeleccionado];

    return nullptr;
}

void Plataforma::guardarAnuncios(const string& ruta) {
    ofstream archivo(ruta.c_str());
    if (!archivo) {
        cout << "Error al abrir archivo para guardar anuncios: " << ruta << endl;
        return;
    }

    for (int i = 0; i < cantidadAnuncios; i++) {
        Anuncio* anun = anuncios[i];
        if (anun != nullptr) {
            archivo << anun->getTexto() << ";"
                    << anun->getCategoria() << "\n";
        }
    }

    archivo.close();
}

// ================== persistencia listas =====================
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

        if (!(linea[0] >= '0' && linea[0] <= '9')) {
            size_t coma = linea.find(',');

            if (coma != string::npos) {
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
            } else {
                usuarioActual = buscarUsuario(linea);
                if (usuarioActual == nullptr) {
                    cout << "Usuario no encontrado: " << linea << endl;
                }
            }
            continue;
        }

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

        ListaFavoritos** seguidas = lista->getListasSeguidas();
        Usuario* seguido = nullptr;

        if (seguidas[0] != nullptr)
            seguido = seguidas[0]->getUsuarioPropietario();

        if (seguido != nullptr)
            archivo << u->getNickname() << "," << seguido->getNickname() << "\n";
        else
            archivo << u->getNickname() << "\n";

        Cancion** canciones = lista->getCanciones();
        for (int j = 0; canciones[j] != nullptr; j++)
            archivo << canciones[j]->getIdCancion() << "\n";

        archivo << "\n";
    }

    archivo.close();
}

// ================== actualizar líneas indexadas =============
void Plataforma::actualizarLineaCancion(int idCancion) {
    int izq = 0;
    int der = cantidadCanciones - 1;
    int indice = -1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;

        if (idsCanciones[mid] == idCancion) {
            indice = mid;
            break;
        }

        if (idsCanciones[mid] < idCancion) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    if (indice != -1) {
        Cancion* c = cargarCancion(idCancion);
        if (c != nullptr) {
            lineasCanciones[indice] = to_string(c->getIdCancion()) + "|" +
                                      string(c->getNombre()) + "|" +
                                      to_string(c->getDuracion()) + "|" +
                                      string(c->getRuta128()) + "|" +
                                      string(c->getRuta320()) + "|" +
                                      to_string(c->getReproducciones());
            delete c;
        }
    }
}

void Plataforma::actualizarLineaCredito(int idCancion) {
    int izq = 0;
    int der = cantidadCreditos - 1;
    int indice = -1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;

        if (idCancionesCred[mid] == idCancion) {
            indice = mid;
            break;
        }

        if (idCancionesCred[mid] < idCancion) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    if (indice != -1) {
        Credito* cred = cargarCredito(idCancion);
        if (cred != nullptr) {
            lineasCreditos[indice] = to_string(cred->getIdCancion()) + "|" +
                                     string(cred->getNombre()) + "|" +
                                     string(cred->getApellido()) + "|" +
                                     string(cred->getTipo()) + "|" +
                                     string(cred->getCodigoAfiliacion());
            delete cred;
        }
    }
}

void Plataforma::actualizarLineaAlbum(int idArtista, int idAlbum) {
    long long idBuscado = combinarIds(idArtista, idAlbum);
    int izq = 0;
    int der = cantidadAlbumes - 1;
    int indice = -1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        long long idActual = combinarIds(idArtistas[mid], idAlbumes[mid]);

        if (idActual == idBuscado) {
            indice = mid;
            break;
        }

        if (idActual < idBuscado) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    if (indice != -1) {
        Album* alb = cargarAlbum(idArtista, idAlbum);
        if (alb != nullptr) {
            string lineaNueva = to_string(idArtista) + "|" +
                                to_string(alb->getIdAlbum()) + "|" +
                                string(alb->getNombre()) + "|" +
                                string(alb->getFechaLanzamiento()) + "|" +
                                string(alb->getSelloDisquero()) + "|" +
                                string(alb->getPortadaRuta()) + "|" +
                                to_string(alb->getPuntuacion()) + "|";

            int cantGeneros = alb->getCantidadGeneros();
            char** generos = alb->getGeneros();
            if (cantGeneros > 0) {
                lineaNueva += string(generos[0]);
                for (int j = 1; j < cantGeneros; j++) {
                    lineaNueva += "," + string(generos[j]);
                }
            }

            lineasAlbumes[indice] = lineaNueva;
            delete alb;
        }
    }
}

// ================== agregar nuevos registros ================
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

    string linea = to_string(cancion->getIdCancion()) + "|" +
                   string(cancion->getNombre()) + "|" +
                   to_string(cancion->getDuracion()) + "|" +
                   string(cancion->getRuta128()) + "|" +
                   string(cancion->getRuta320()) + "|" +
                   to_string(cancion->getReproducciones());

    idsCanciones[cantidadCanciones] = cancion->getIdCancion();
    lineasCanciones[cantidadCanciones] = linea;
    cantidadCanciones++;

    ordenarCancionesPorId();
    cout << "Canción agregada: " << cancion->getNombre() << endl;
}

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

    string linea = to_string(idArtista) + "|" +
                   to_string(album->getIdAlbum()) + "|" +
                   string(album->getNombre()) + "|" +
                   string(album->getFechaLanzamiento()) + "|" +
                   string(album->getSelloDisquero()) + "|" +
                   string(album->getPortadaRuta()) + "|" +
                   to_string(album->getPuntuacion()) + "|";

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

    ordenarAlbumesPorId();
    cout << "Álbum agregado: " << album->getNombre() << endl;
}

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

// ================== eliminar registros ======================
bool Plataforma::eliminarCancion(int idCancion) {
    int izq = 0;
    int der = cantidadCanciones - 1;
    int indice = -1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;

        if (idsCanciones[mid] == idCancion) {
            indice = mid;
            break;
        }

        if (idsCanciones[mid] < idCancion) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }

    if (indice == -1) {
        return false;
    }

    for (int j = indice; j < cantidadCanciones - 1; j++) {
        idsCanciones[j] = idsCanciones[j + 1];
        lineasCanciones[j] = lineasCanciones[j + 1];
    }
    cantidadCanciones--;
    cout << "Canción eliminada: ID " << idCancion << endl;
    return true;
}

bool Plataforma::eliminarArtista(int idArtista) {
    for (int i = 0; i < cantidadArtistas; i++) {
        if (artistas[i]->getIdArtista() == idArtista) {
            delete artistas[i];

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

bool Plataforma::eliminarUsuario(const string& nickname) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname) {
            delete usuarios[i];

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

// ================== utilidades ==============================
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
