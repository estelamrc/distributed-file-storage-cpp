#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include "Usuario.h"

/**
 * @brief Clase derivada que representa a un administrador.
 *
 * El administrador tiene cuota ilimitada y puede gestionar usuarios
 * además de consultar sus propios datos y ficheros.
 */
class Administrador : public Usuario {
public:
    /**
     * @brief Constructor de la clase Administrador.
     * @param id Identificador del administrador.
     * @param nombre Nombre del administrador.
     * @param password Contraseña del administrador.
     */
    Administrador(int id, const std::string& nombre, const std::string& password);

    /**
     * @brief Devuelve la información del administrador.
     * @return Cadena con la información del administrador.
     */
    std::string mostrarInformacion() const override;

    /**
     * @brief Devuelve el tipo del usuario.
     * @return Cadena "Admin".
     */
    std::string getTipo() const override;
};

#endif