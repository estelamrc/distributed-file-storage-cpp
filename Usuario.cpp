#include "Usuario.h"
#include "Administrador.h"
#include "CuotaExcedidaException.h"
#include "Fichero.h"
#include "FicheroImagen.h"
#include "FicheroTexto.h"

#include <cstdio>
#include <sstream>

Usuario::Usuario() : id(0), nombre(""), cuotaDisponible(0.0), password("") {
}

Usuario::Usuario(int id, const std::string& nombre, double cuotaDisponible, const std::string& password)
    : id(id), nombre(nombre), cuotaDisponible(cuotaDisponible), password(password) {
}

Usuario::~Usuario() {
    for (std::map<std::string, Fichero*>::iterator it = misFicheros.begin();
         it != misFicheros.end(); ++it) {
        delete it->second;
    }
    misFicheros.clear();
}

std::string Usuario::mostrarInformacion() const {
    std::ostringstream salida;
    salida << "Tipo: " << getTipo() << "\n";
    salida << "ID: " << id << "\n";
    salida << "Nombre: " << nombre << "\n";
    salida << "Cuota disponible: " << cuotaDisponible << "\n";
    salida << "Numero de ficheros: " << misFicheros.size();
    return salida.str();
}

std::string Usuario::getTipo() const {
    return "Generico";
}

bool Usuario::setPassword(const std::string& nuevaPass, Usuario* solicitante) {
    if (solicitante == NULL) {
        return false;
    }

    if (solicitante == this || solicitante->getTipo() == "Admin") {
        password = nuevaPass;
        return true;
    }

    return false;
}

void Usuario::setCuotaDisponible(double nuevaCuota) {
    cuotaDisponible = nuevaCuota;
}

void Usuario::setNombre(const std::string& nuevoNombre) {
    nombre = nuevoNombre;
}

int Usuario::getId() const {
    return id;
}

std::string Usuario::getNombre() const {
    return nombre;
}

std::string Usuario::getPassword() const {
    return password;
}

double Usuario::getCuotaDisponible() const {
    return cuotaDisponible;
}

bool Usuario::addFichero(const std::string& nombreBase, const std::string& contenido, int tipo) {
    Fichero* fichero = NULL;

    if (tipo == 1) {
        fichero = new FicheroTexto(nombreBase + ".txt", 0.0, id);
    } else if (tipo == 2) {
        fichero = new FicheroImagen(nombreBase + ".img", 0.0, id);
    } else {
        return false;
    }

    try {
        cuotaDisponible = fichero->escribir(nombreBase, contenido, cuotaDisponible);
        misFicheros[fichero->getNombre()] = fichero;
        return true;
    } catch (...) {
        delete fichero;
        throw;
    }
}

bool Usuario::borrarFichero(const std::string& nombreCompleto) {
    std::map<std::string, Fichero*>::iterator it = misFicheros.find(nombreCompleto);
    if (it == misFicheros.end()) {
        return false;
    }

    if (cuotaDisponible >= 0) {
        cuotaDisponible += it->second->getTamano();
    }

    std::remove(nombreCompleto.c_str());
    delete it->second;
    misFicheros.erase(it);
    return true;
}

bool Usuario::obtenerPrevisualizacion(const std::string& nombreCompleto, std::string& salida) const {
    std::map<std::string, Fichero*>::const_iterator it = misFicheros.find(nombreCompleto);
    if (it == misFicheros.end()) {
        return false;
    }

    salida = it->second->previsualizar();
    return true;
}

const std::map<std::string, Fichero*>& Usuario::getMisFicheros() const {
    return misFicheros;
}

void Usuario::addFicheroExistente(Fichero* fichero) {
    if (fichero != NULL) {
        misFicheros[fichero->getNombre()] = fichero;
    }
}

std::ostream& operator<<(std::ostream& os, const Usuario& u) {
    os << u.mostrarInformacion();
    return os;
}