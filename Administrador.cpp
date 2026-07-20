#include "Administrador.h"

#include <sstream>

Administrador::Administrador(int id, const std::string& nombre, const std::string& password)
    : Usuario(id, nombre, -1.0, password) {
}

std::string Administrador::mostrarInformacion() const {
    std::ostringstream salida;
    salida << "Tipo: " << getTipo() << "\n";
    salida << "ID: " << id << "\n";
    salida << "Nombre: " << nombre << "\n";
    salida << "Cuota disponible: ilimitada\n";
    salida << "Numero de ficheros: " << misFicheros.size();
    return salida.str();
}

std::string Administrador::getTipo() const {
    return "Admin";
}