#include "Fichero.h"

Fichero::Fichero(const std::string& nombre, double tamano, int idPropietario)
    : nombre(nombre), tamano(tamano), idPropietario(idPropietario) {
}

Fichero::~Fichero() {
}

std::string Fichero::getNombre() const {
    return nombre;
}

double Fichero::getTamano() const {
    return tamano;
}

int Fichero::getIdPropietario() const {
    return idPropietario;
}