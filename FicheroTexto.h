#ifndef FICHEROTEXTO_H
#define FICHEROTEXTO_H

#include "Fichero.h"

/**
 * @brief Clase derivada que representa un fichero de texto.
 *
 * El fichero se almacena físicamente con extensión .txt.
 */
class FicheroTexto : public Fichero {
public:
    /**
     * @brief Constructor de la clase FicheroTexto.
     * @param nombre Nombre del fichero.
     * @param tamano Tamaño lógico en GB.
     * @param idPropietario ID del propietario.
     */
    FicheroTexto(const std::string& nombre, double tamano, int idPropietario);

    /**
     * @brief Escribe un fichero de texto real en disco.
     * @param nombreBase Nombre base del fichero, sin extensión.
     * @param contenido Contenido del fichero.
     * @param cuotaDisponible Cuota disponible del usuario.
     * @return Nueva cuota disponible.
     */
    double escribir(const std::string& nombreBase,
                    const std::string& contenido,
                    double cuotaDisponible) override;

    /**
     * @brief Devuelve la previsualización textual del fichero.
     * @return Texto con cabecera y contenido del fichero.
     */
    std::string previsualizar() const override;
};

#endif