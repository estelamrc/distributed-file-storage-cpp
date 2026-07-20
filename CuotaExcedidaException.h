#ifndef CUOTAEXCEDIDAEXCEPTION_H
#define CUOTAEXCEDIDAEXCEPTION_H

#include <exception>
#include <string>

/**
 * @brief Excepción lanzada cuando un usuario no tiene cuota suficiente.
 *
 * Esta excepción se utiliza al intentar crear un fichero cuyo tamaño lógico
 * supera la cuota disponible del usuario.
 */
class CuotaExcedidaException : public std::exception {
private:
    std::string mensaje; ///< Mensaje descriptivo de la excepción.

public:
    /**
     * @brief Constructor de la excepción.
     * @param mensaje Texto descriptivo del error.
     */
    explicit CuotaExcedidaException(const std::string& mensaje)
        : mensaje(mensaje) {
    }

    /**
     * @brief Devuelve el mensaje asociado a la excepción.
     * @return Cadena C con el mensaje de error.
     */
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};

#endif