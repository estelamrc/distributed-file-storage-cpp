#include "FicheroTexto.h"
#include "CuotaExcedidaException.h"

#include <fstream>
#include <sstream>

FicheroTexto::FicheroTexto(const std::string& nombre, double tamano, int idPropietario)
    : Fichero(nombre, tamano, idPropietario) {
}

double FicheroTexto::escribir(const std::string& nombreBase,
                              const std::string& contenido,
                              double cuotaDisponible) {
    std::string nombreReal = nombreBase + ".txt";
    double tamNuevo = static_cast<double>(contenido.size()) / 1000000000.0;

    if (cuotaDisponible >= 0 && tamNuevo > cuotaDisponible) {
        throw CuotaExcedidaException("Cuota excedida al crear fichero de texto");
    }

    std::ofstream fout(nombreReal.c_str());
    fout << contenido;
    fout.close();

    nombre = nombreReal;
    tamano = tamNuevo;

    if (cuotaDisponible < 0) {
        return cuotaDisponible;
    }

    return cuotaDisponible - tamNuevo;
}

std::string FicheroTexto::previsualizar() const {
    std::ifstream fin(nombre.c_str());
    if (!fin) {
        return "No se pudo abrir el fichero";
    }

    std::ostringstream salida;
    salida << "[FICHERO TEXTO] " << nombre << "\n";

    std::string linea;
    while (std::getline(fin, linea)) {
        salida << linea << "\n";
    }

    return salida.str();
}