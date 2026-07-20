#include "Cliente.h"

#include <sstream>

Cliente::Cliente(int id, const std::string& nombre, const std::string& password)
    : Usuario(id, nombre, 10.0, password) {
}

std::string Cliente::mostrarInformacion() const {
    std::ostringstream salida;
    salida << "Tipo: " << getTipo() << "\n";
    salida << "ID: " << id << "\n";
    salida << "Nombre: " << nombre << "\n";
    salida << "Cuota disponible: " << cuotaDisponible << "\n";
    salida << "Numero de ficheros: " << misFicheros.size();
    return salida.str();
}

std::string Cliente::getTipo() const {
    return "Cliente";
}