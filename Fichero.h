#ifndef FICHERO_H
#define FICHERO_H

#include <string>

/**
 * @brief Clase abstracta que representa un fichero del sistema TeleStore.
 *
 * Esta clase encapsula la información básica de cualquier fichero:
 * su nombre, su tamaño lógico y el identificador del propietario.
 *
 * Las clases derivadas deberán implementar la escritura real en disco
 * y la previsualización del contenido.
 */
class Fichero {
protected:
    std::string nombre;   ///< Nombre completo del fichero.
    double tamano;        ///< Tamaño lógico del fichero en GB.
    int idPropietario;    ///< ID del usuario propietario.

public:
    /**
     * @brief Constructor de la clase Fichero.
     * @param nombre Nombre del fichero.
     * @param tamano Tamaño lógico del fichero en GB.
     * @param idPropietario ID del propietario.
     */
    Fichero(const std::string& nombre, double tamano, int idPropietario);

    /**
     * @brief Destructor virtual de la clase Fichero.
     */
    virtual ~Fichero();

    /**
     * @brief Devuelve el nombre completo del fichero.
     * @return Nombre del fichero.
     */
    std::string getNombre() const;

    /**
     * @brief Devuelve el tamaño lógico del fichero.
     * @return Tamaño en GB.
     */
    double getTamano() const;

    /**
     * @brief Devuelve el ID del propietario del fichero.
     * @return ID del propietario.
     */
    int getIdPropietario() const;

    /**
     * @brief Escribe físicamente el fichero en disco.
     *
     * La implementación concreta depende del tipo de fichero.
     *
     * @param nombreBase Nombre base del fichero, sin extensión.
     * @param contenido Contenido que se escribirá en el fichero.
     * @param cuotaDisponible Cuota disponible del usuario.
     * @return Nueva cuota disponible tras la escritura.
     */
    virtual double escribir(const std::string& nombreBase,
                            const std::string& contenido,
                            double cuotaDisponible) = 0;

    /**
     * @brief Devuelve una previsualización textual del fichero.
     *
     * En esta práctica la previsualización se transmite como texto
     * a través de la conexión TCP.
     *
     * @return Cadena con el contenido previsualizado.
     */
    virtual std::string previsualizar() const = 0;
};

#endif