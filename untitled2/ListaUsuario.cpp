#include "ListaUsuario.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void ListaUsuario::agregarUsuario(const Usuario &usuario) {
    usuarios.push_back(usuario);
}

void ListaUsuario::eliminarUsuario(const std::string &userName) {
    usuarios.erase(std::remove_if(usuarios.begin(), usuarios.end(), [&userName](const Usuario &u) {
        return u.getUserName() == userName;
    }), usuarios.end());
}

Usuario *ListaUsuario::buscarUsuarioPorNombre(const std::string &userName) const {
    for (auto &usuario : usuarios) {
        if (usuario.getUserName() == userName) {
            return const_cast<Usuario*>(&usuario);
        }
    }
    return nullptr;
}

const int ListaUsuario::buscarUsuarioPorId(const std::string &id) const {
    for (size_t i = 0; i < usuarios.size(); ++i) {
        if (usuarios[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

const std::vector<Usuario> &ListaUsuario::getUsuarios() const {
    return usuarios;
}

void ListaUsuario::leerUsuariosDesdeArchivo(const std::string &archivo) {
    std::ifstream archivoEntrada(archivo);
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivoEntrada, linea)) {
        std::stringstream ss(linea);
        std::string id, user, userName, description, friendsStr, countFriendStr, lastLogin, firstLogin;

        std::getline(ss, id, ',');
        std::getline(ss, user, ',');
        std::getline(ss, userName, ',');
        std::getline(ss, description, ',');
        std::getline(ss, friendsStr, ',');
        std::getline(ss, countFriendStr, ',');
        std::getline(ss, lastLogin, ',');
        std::getline(ss, firstLogin, ',');

        // Procesar la cadena de amigos
        std::vector<std::string> friends;
        friendsStr = friendsStr.substr(1, friendsStr.size() - 2); // Eliminar corchetes
        std::stringstream friendsStream(friendsStr);
        std::string friendId;
        while (std::getline(friendsStream, friendId, ';')) {
            friends.push_back(friendId);
        }

        int countFriend = std::stoi(countFriendStr);

        // Crear el objeto Usuario y agregarlo a la lista
        Usuario usuario(id, user, userName, description, friends, countFriend, lastLogin, firstLogin);
        usuarios.push_back(usuario);
    }

    archivoEntrada.close();
}
