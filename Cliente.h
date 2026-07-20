#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"

/**
 * @brief Clase derivada que representa a un cliente.
 *
 * El cliente dispone de una cuota inicial por defecto y puede operar
 * únicamente sobre sus propios ficheros.
 */
class Cliente : public Usuario {
public:
    /**
     * @brief Constructor de la clase Cliente.
     * @param id Identificador del cliente.
     * @param nombre Nombre del cliente.
     * @param password Contraseña del cliente.
     */
    Cliente(int id, const std::string& nombre, const std::string& password);

    /**
     * @brief Devuelve la información del cliente.
     * @return Cadena con la información del cliente.
     */
    std::string mostrarInformacion() const override;

    /**
     * @brief Devuelve el tipo del usuario.
     * @return Cadena "Cliente".
     */
    std::string getTipo() const override;
};

#endif