#include "SistemaImpl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <queue>
#include <unordered_map>
#include <chrono>

using namespace std;

// Definición de la matriz de adyacencia como miembro privado de la clase SistemaImpl
std::vector<std::vector<int>> SistemaImpl::matrizAdyacencia;
std::vector<std::vector<int>> SistemaImpl::matrizAdyacenciaB;
// Constructor de la clase SistemaImpl
SistemaImpl::SistemaImpl(const std::string &archivo) : archivoUsuarios(archivo) {
    cargarUsuarios(archivo);
    // Inicializar matrizAdyacencia aquí si es necesario
    matrizAdyacencia = {
            {0, 1, 1, 1, 1, 1, 0, 0, 0}, // A
            {1, 0, 0, 1, 1, 1, 1, 1, 1}, // B
            {1, 0, 0, 0, 0, 0, 0, 0, 0}, // C
            {1, 1, 0, 0, 1, 0, 0, 0, 0}, // D
            {1, 1, 0, 1, 0, 0, 0, 0, 1}, // F
            {1, 1, 0, 0, 0, 0, 1, 0, 0}, // G
            {0, 1, 0, 0, 0, 1, 0, 0, 0}, // J
            {0, 1, 0, 0, 0, 0, 0, 0, 0}, // P
            {0, 1, 0, 0, 1, 0, 0, 0, 0}  // S
    };
    matrizAdyacenciaB= {{0,1,1}, //k
                        {1,0,1}, //R
                        {1,1,0} //I
    };
}

//menu
void SistemaImpl::mostrarMenu() {
    int opcion;
    do {
        std::cout << "1. Nuevo usuario" << std::endl;
        std::cout << "2. Eliminar usuario" << std::endl;
        std::cout << "3. Verificar relación entre usuarios" << std::endl;
        std::cout << "4. Mostrar conjunto de personas que conecta a dos usuarios" << std::endl; // [E]
        std::cout << "5. Mostrar conjunto de personas que no poseen conexión con un usuario" << std::endl; // [F]
        std::cout << "6. Visualizar grafo" << std::endl; // [G]
        std::cout << "7. Guardar usuarios" << std::endl;
        std::cout << "8. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                nuevoUsuario();
                break;
            case 2:
                eliminarUsuario();
                break;
            case 3: {
                std::string userName1, userName2;
                std::cout << "Ingrese el primer nombre de usuario: ";
                std::cin >> userName1;
                std::cout << "Ingrese el segundo nombre de usuario: ";
                std::cin >> userName2;
                verificarRelacionEntreUsuarios(userName1, userName2);
                break;
            }
            case 4: {
                std::string userId1, userId2;
                std::cout << "Ingrese el ID del primer usuario: ";
                std::cin >> userId1;
                std::cout << "Ingrese el ID del segundo usuario: ";
                std::cin >> userId2;
                mostrarConjuntoConexiones(userId1, userId2);
                break;
            }
            case 5: {
                std::string userId;
                std::cout << "Ingrese el ID del usuario: ";
                std::cin >> userId;
                mostrarPersonasSinConexion(userId);
                break;
            }
            case 6:
                visualizarGrafo();
                break;
            case 7:
                guardarUsuarios();
                break;
            case 8:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida, por favor intente nuevamente." << std::endl;
        }
    } while (opcion != 8);
}


// Opción [A] Nuevo Usuario
void SistemaImpl::nuevoUsuario() {
    std::string user, userName, description;
    std::cout << "Ingrese el nombre del usuario: ";
    std::cin >> user;
    std::cout << "Ingrese el nombre de usuario: ";
    std::cin >> userName;
    std::cout << "Ingrese una descripción: ";
    std::cin.ignore();
    std::getline(std::cin, description);

    std::string id = generarIdUsuario();
    Usuario nuevoUsuario(id, user, userName, description, {}, 0, "01/01/1970", "01/01/1970");
    listaUsuario.agregarUsuario(nuevoUsuario);
    matrizAdyacencia.resize(listaUsuario.getUsuarios().size(), std::vector<int>(listaUsuario.getUsuarios().size(), 0));
}

// Opción [B] Eliminar Usuario
void SistemaImpl::eliminarUsuario() {
    std::string userName;
    std::cout << "Ingrese el nombre de usuario a eliminar: ";
    std::cin >> userName;
    listaUsuario.eliminarUsuario(userName);
    // Redimensionar la matriz de adyacencia
    matrizAdyacencia.resize(listaUsuario.getUsuarios().size(), std::vector<int>(listaUsuario.getUsuarios().size(), 0));

}

// Opción [C] Revisar todas las relaciones de un usuario
void SistemaImpl::verificarRelacionEntreUsuarios(const std::string &userName1, const std::string &userName2) const {
    // Obtener los índices de los usuarios en la matriz de adyacencia
    int indiceUsuario1 = listaUsuario.buscarUsuarioPorNombre(userName1) - listaUsuario.getUsuarios().data();
    int indiceUsuario2 = listaUsuario.buscarUsuarioPorNombre(userName2) - listaUsuario.getUsuarios().data();

    // Verificar si los usuarios existen
    if (indiceUsuario1 == -1 || indiceUsuario2 == -1) {
        std::cout << "Uno o ambos usuarios no existen." << std::endl;
        return;
    }

    // Verificar si son amigos en la matriz de adyacencia
    if (matrizAdyacencia[indiceUsuario1][indiceUsuario2] == 1) {
        std::cout << "Los usuarios son amigos." << std::endl;
    } else {
        std::cout << "Los usuarios no son amigos." << std::endl;
    }
}

void SistemaImpl::cargarUsuarios(const std::string &archivo) {
    listaUsuario.leerUsuariosDesdeArchivo(archivo);
    int cantidadUsuarios = listaUsuario.getUsuarios().size();
    matrizAdyacencia.resize(cantidadUsuarios, std::vector<int>(cantidadUsuarios, 0));

    const std::vector<Usuario> &usuarios = listaUsuario.getUsuarios();
    for (size_t i = 0; i < usuarios.size(); ++i) {
        for (const std::string &friendId : usuarios[i].getFriends()) {
            int friendIndex = buscarUsuarioPorId(friendId);
            if (friendIndex != -1) {
                matrizAdyacencia[i][friendIndex] = 1;
                matrizAdyacencia[friendIndex][i] = 1;
            }
        }
    }
}


void SistemaImpl::guardarUsuarios() {
    std::ofstream archivoSalida(archivoUsuarios);
    if (!archivoSalida.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar: " << archivoUsuarios << std::endl;
        return;
    }

    const std::vector<Usuario> &usuarios = listaUsuario.getUsuarios();
    for (const auto &usuario : usuarios) {
        archivoSalida << usuario.getId() << ","
                      << usuario.getUser() << ","
                      << usuario.getUserName() << ","
                      << usuario.getDescription() << ","
                      << usuario.getFriendsStr() << ","
                      << usuario.getCountFriend() << ","
                      << usuario.getLastLogin() << ","
                      << usuario.getFirstLogin() << "\n";
    }

    archivoSalida.close();
}

bool SistemaImpl::encontrarCaminoMasCorto(int inicio, int fin, std::vector<std::string> &camino) const {
    // Creamos una cola para BFS
    std::queue<int> cola;
    // Creamos un mapa para almacenar los padres de cada nodo visitado durante el BFS
    std::unordered_map<int, int> padres;
    // Creamos un vector para marcar los nodos visitados
    std::vector<bool> visitado(listaUsuario.getUsuarios().size(), false);

    // Empezamos BFS desde el nodo de inicio
    cola.push(inicio);
    visitado[inicio] = true;

    // Realizamos BFS
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        // Si llegamos al nodo de destino, construimos el camino retrocediendo a través de los padres
        if (actual == fin) {
            int nodo = fin;
            while (nodo != inicio) {
                camino.push_back(listaUsuario.getUsuarios()[nodo].getId());
                nodo = padres[nodo];
            }
            camino.push_back(listaUsuario.getUsuarios()[inicio].getId());
            std::reverse(camino.begin(), camino.end()); // Invertimos el camino para que vaya del inicio al fin
            return true; // Se encontró un camino
        }

        // Exploramos los nodos adyacentes al actual
        for (size_t i = 0; i < matrizAdyacencia[actual].size(); ++i) {
            if (matrizAdyacencia[actual][i] == 1 && !visitado[i]) {
                cola.push(i);
                visitado[i] = true;
                padres[i] = actual;
            }
        }
    }

    // Si llegamos aquí, no se encontró un camino entre inicio y fin
    return false;
}
// Opción [E] Mostrar el conjunto de personas que conecta a dos usuarios
void SistemaImpl::mostrarConjuntoConexiones(const std::string &userId1, const std::string &userId2) const {
    int indiceUsuario1 = reinterpret_cast<int>(listaUsuario.buscarUsuarioPorId(userId1));
    int indiceUsuario2 = reinterpret_cast<int>(listaUsuario.buscarUsuarioPorId(userId2));

    if (indiceUsuario1 == -1 || indiceUsuario2 == -1) {
        std::cout << "Uno o ambos usuarios no existen." << std::endl;
        return;
    }

    std::vector<std::string> camino;
    if (encontrarCaminoMasCorto(indiceUsuario1, indiceUsuario2, camino)) {
        std::cout << "[Amigos en conexión]: " << std::endl;
        for (const auto &id : camino) {
            const Usuario *usuario = reinterpret_cast<const Usuario *>(listaUsuario.buscarUsuarioPorId(id));
            if (usuario) {
                std::cout << usuario->getUserName() << ": " << usuario->getUser() << std::endl;
            }
        }
    } else {
        std::cout << "Estas personas no están conectadas :(" << std::endl;
    }
}



// Opción [F] Mostrar el conjunto de personas que no poseen conexión con un usuario
void SistemaImpl::mostrarPersonasSinConexion(const std::string &userId) const {
    int indiceUsuario = listaUsuario.buscarUsuarioPorId(userId);
    if (indiceUsuario == -1) {
        std::cout << "El usuario no existe." << std::endl;
        return;
    }

    std::vector<std::string> personasSinConexion;
    for (size_t i = 0; i < matrizAdyacenciaB.size(); ++i) {
        if (i != indiceUsuario && !hayConexionB(indiceUsuario, i)) {
            const Usuario *usuario = reinterpret_cast<const Usuario *>(listaUsuario.buscarUsuarioPorId(
                    listaUsuario.getUsuarios()[i].getId()));
            if (usuario) {
                personasSinConexion.push_back(usuario->getUserName() + ": " + usuario->getDescription());
            }
        }
    }

    if (personasSinConexion.empty()) {
        std::cout << "Todas las personas están conectadas con este usuario." << std::endl;
    } else {
        std::cout << "Personas encontradas sin conexión:" << std::endl;
        for (const auto &persona : personasSinConexion) {
            std::cout << persona << std::endl;
        }
    }
}

bool SistemaImpl::hayConexionB(int indiceUsuario1, int indiceUsuario2) const {
    // Verificar si hay una conexión entre los usuarios en la matriz de adyacencia B
    return matrizAdyacenciaB[indiceUsuario1][indiceUsuario2] == 1;
}



// Opción [G] Visualizar grafo
void SistemaImpl::visualizarGrafo() const {
    std::cout << "----- > Visualizar grafo <------" << std::endl;
    const std::vector<Usuario> &usuarios = listaUsuario.getUsuarios();
    for (const auto &usuario : usuarios) {
        std::cout << "[ID]: " << usuario.getId() << " [Nombre]: " << usuario.getUser()
                  << ", [Username]: " << usuario.getUserName() << " [Descripcion]: " << usuario.getDescription() << std::endl;
    }

    std::cout << "Matriz de adyacencia:" << std::endl;
    for (const auto &fila : matrizAdyacencia) {
        for (int val : fila) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

bool SistemaImpl::hayConexion(int indiceUsuario1, int indiceUsuario2) const {
    // Creamos una cola para BFS
    std::queue<int> cola;
    // Creamos un vector para marcar los nodos visitados
    std::vector<bool> visitado(listaUsuario.getUsuarios().size(), false);

    // Empezamos BFS desde el nodo de indiceUsuario1
    cola.push(indiceUsuario1);
    visitado[indiceUsuario1] = true;

    // Realizamos BFS
    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();

        // Si encontramos el nodo indiceUsuario2, hay conexión
        if (actual == indiceUsuario2) {
            return true;
        }

        // Exploramos los nodos adyacentes al actual
        for (size_t i = 0; i < matrizAdyacencia[actual].size(); ++i) {
            if (matrizAdyacencia[actual][i] == 1 && !visitado[i]) {
                cola.push(i);
                visitado[i] = true;
            }
        }
    }

    // Si llegamos aquí, no hay conexión entre indiceUsuario1 e indiceUsuario2
    return false;
}


std::string SistemaImpl::generarIdUsuario() {
    // Obtiene la marca de tiempo actual en milisegundos
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

    // Agrega algún otro componente único, como un contador incremental o un identificador único generado aleatoriamente
    // Aquí, por simplicidad, podrías usar un contador incremental si tienes acceso a un miembro de datos de la clase para mantenerlo.

    // Combina los componentes para formar el ID único
    std::ostringstream idStream;
    idStream << "user_" << ms; // Formato sugerido: "user_timestamp"
    return idStream.str();
}

bool SistemaImpl::validarFecha(const std::string &fecha) {
    // Implementación de la lógica para validar una fecha en el formato dd/mm/yyyy.
    std::regex formatoFecha("\\d{2}/\\d{2}/\\d{4}");
    return std::regex_match(fecha, formatoFecha);
}



Usuario* SistemaImpl::buscarUsuarioPorNombre(const std::string &userName) const {
    // Buscar el usuario por su nombre en la lista de usuarios
    for (const Usuario &usuario : listaUsuario.getUsuarios()) {
        if (usuario.getUserName() == userName) {
            // Se encontró el usuario, devolver un puntero al usuario encontrado
            return const_cast<Usuario*>(&usuario); // Retornamos un puntero no constante ya que es una función constante
        }
    }

    // Si no se encuentra el usuario, devolver nullptr
    return nullptr;
}


const int SistemaImpl::buscarUsuarioPorId(const std::string &id) const {
    // Buscar el usuario por su ID en la lista de usuarios
    for (size_t i = 0; i < listaUsuario.getUsuarios().size(); ++i) {
        if (listaUsuario.getUsuarios()[i].getId() == id) {
            // Se encontró el usuario, devolver su índice
            return i;
        }
    }

    // Si no se encuentra el usuario, devolver -1
    return -1;
}

bool SistemaImpl::sonAmigos(int indiceUsuario1, int indiceUsuario2) const {
    // Verificar si hay una conexión entre los usuarios en la matriz de adyacencia
    return matrizAdyacencia[indiceUsuario1][indiceUsuario2] == 1;
}



