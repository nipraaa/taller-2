

#ifndef UNTITLED2_LISTAUSUARIO_H
#define UNTITLED2_LISTAUSUARIO_H
#include "Usuario.h"
#include <vector>
#include <string>

class ListaUsuario {
public:
    void agregarUsuario(const Usuario &usuario);
    void eliminarUsuario(const std::string &userName);
    Usuario *buscarUsuarioPorNombre(const std::string &userName) const;
    const int buscarUsuarioPorId(const std::string &id) const;
    const std::vector<Usuario> &getUsuarios() const;
    void leerUsuariosDesdeArchivo(const std::string &archivo);

private:
    std::vector<Usuario> usuarios;
};


#endif //UNTITLED2_LISTAUSUARIO_H
