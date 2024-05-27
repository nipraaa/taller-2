//
// Created by nicol on 26-05-2024.
//

#ifndef UNTITLED2_SISTEMAIMPL_H
#define UNTITLED2_SISTEMAIMPL_H

#include "Usuario.h"
#include "ListaUsuario.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <string>

class SistemaImpl {
private:
    static std::vector<std::vector<int>> matrizAdyacencia;
    static std::vector<std::vector<int>> matrizAdyacenciaB;
    ListaUsuario listaUsuario;
    std::string archivoUsuarios;

public:
    SistemaImpl(const std::string &archivo);

    void mostrarMenu();

    void nuevoUsuario();

    void eliminarUsuario();

    void verificarRelacionEntreUsuarios(const std::string &userName1, const std::string &userName2) const;

    void mostrarConjuntoConexiones(const std::string &userId1, const std::string &userId2) const;

    void mostrarPersonasSinConexion(const std::string &userId) const;

    void visualizarGrafo() const;

    void cargarUsuarios(const std::string &archivo);

    void guardarUsuarios();

    bool validarFecha(const std::string &fecha);

    bool encontrarCaminoMasCorto(int inicio, int fin, std::vector<std::string> &camino) const;

    Usuario *buscarUsuarioPorNombre(const std::string &userName) const;

    const int buscarUsuarioPorId(const std::string &id) const;

    bool sonAmigos(int indiceUsuario1, int indiceUsuario2) const;

    std::string generarIdUsuario();

    bool hayConexion(int indiceUsuario1, int indiceUsuario2) const;

    bool hayConexionB(int indiceUsuario1, int indiceUsuario2) const;

};
#endif //UNTITLED2_SISTEMAIMPL_H
