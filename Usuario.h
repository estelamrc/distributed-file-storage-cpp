#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <map>
#include <string>

class Fichero;

/**
 * @brief Clase base que representa a un usuario genérico del sistema TeleStore.
 *
 * Esta clase almacena la información común de cualquier usuario:
 * identificador, nombre, contraseña, cuota disponible y mapa de ficheros.
 */
class Usuario {
protected:
    int id;                                      ///< Identificador del usuario.
    std::string nombre;                          ///< Nombre del usuario.
    double cuotaDisponible;                      ///< Cuota disponible en GB.
    std::map<std::string, Fichero*> misFicheros; ///< Mapa de ficheros del usuario.

private:
    std::string password;                        ///< Contraseña del usuario.

public:
    /**
     * @brief Constructor por defecto.
     */
    Usuario();

    /**
     * @brief Constructor con parámetros.
     * @param id Identificador del usuario.
     * @param nombre Nombre del usuario.
     * @param cuotaDisponible Cuota disponible en GB.
     * @param password Contraseña del usuario.
     */
    Usuario(int id, const std::string& nombre, double cuotaDisponible, const std::string& password);

    /**
     * @brief Destructor virtual de la clase Usuario.
     *
     * Libera todos los ficheros almacenados en el mapa del usuario.
     */
    virtual ~Usuario();

    /**
     * @brief Devuelve la información del usuario en formato texto.
     * @return Cadena con la información del usuario.
     */
    virtual std::string mostrarInformacion() const;

    /**
     * @brief Devuelve el tipo del usuario.
     * @return "Generico" por defecto.
     */
    virtual std::string getTipo() const;

    /**
     * @brief Cambia la contraseña del usuario si el solicitante tiene permiso.
     * @param nuevaPass Nueva contraseña.
     * @param solicitante Usuario que solicita el cambio.
     * @return true si el cambio se realiza, false si no se permite.
     */
    bool setPassword(const std::string& nuevaPass, Usuario* solicitante);

    /**
     * @brief Cambia la cuota disponible del usuario.
     * @param nuevaCuota Nueva cuota disponible.
     */
    void setCuotaDisponible(double nuevaCuota);

    /**
     * @brief Cambia el nombre del usuario.
     * @param nuevoNombre Nuevo nombre.
     */
    void setNombre(const std::string& nuevoNombre);

    /**
     * @brief Devuelve el identificador del usuario.
     * @return ID del usuario.
     */
    int getId() const;

    /**
     * @brief Devuelve el nombre del usuario.
     * @return Nombre del usuario.
     */
    std::string getNombre() const;

    /**
     * @brief Devuelve la contraseña del usuario.
     * @return Contraseña del usuario.
     */
    std::string getPassword() const;

    /**
     * @brief Devuelve la cuota disponible del usuario.
     * @return Cuota disponible.
     */
    double getCuotaDisponible() const;

    /**
     * @brief Añade un fichero al usuario.
     *
     * @param nombreBase Nombre base del fichero, sin extensión.
     * @param contenido Contenido del fichero.
     * @param tipo Tipo de fichero: 1 para texto, 2 para imagen.
     * @return true si se añade correctamente, false si falla.
     */
    bool addFichero(const std::string& nombreBase, const std::string& contenido, int tipo);

    /**
     * @brief Elimina un fichero del usuario.
     * @param nombreCompleto Nombre completo del fichero.
     * @return true si se borra, false si no existe.
     */
    bool borrarFichero(const std::string& nombreCompleto);

    /**
     * @brief Obtiene la previsualización de un fichero.
     * @param nombreCompleto Nombre completo del fichero.
     * @param salida Cadena donde se guarda la salida.
     * @return true si el fichero existe, false en caso contrario.
     */
    bool obtenerPrevisualizacion(const std::string& nombreCompleto, std::string& salida) const;

    /**
     * @brief Devuelve el mapa de ficheros del usuario.
     * @return Referencia constante al mapa de ficheros.
     */
    const std::map<std::string, Fichero*>& getMisFicheros() const;

    /**
     * @brief Inserta un fichero ya existente en el mapa del usuario.
     * @param fichero Puntero al fichero.
     */
    void addFicheroExistente(Fichero* fichero);

    /**
     * @brief Operador de salida para mostrar un usuario.
     * @param os Flujo de salida.
     * @param u Usuario a mostrar.
     * @return Referencia al flujo.
     */
    friend std::ostream& operator<<(std::ostream& os, const Usuario& u);
};

#endif