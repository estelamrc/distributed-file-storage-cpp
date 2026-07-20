#ifndef FICHEROIMAGEN_H
#define FICHEROIMAGEN_H

#include "Fichero.h"

/**
 * @brief Clase derivada que representa un fichero de imagen.
 *
 * En esta práctica la imagen se maneja como un archivo de texto
 * con extensión .img para simplificar la simulación.
 */
class FicheroImagen : public Fichero {
public:
    /**
     * @brief Constructor de la clase FicheroImagen.
     * @param nombre Nombre del fichero.
     * @param tamano Tamaño lógico en GB.
     * @param idPropietario ID del propietario.
     */
    FicheroImagen(const std::string& nombre, double tamano, int idPropietario);

    /**
     * @brief Escribe un fichero de imagen real en disco.
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