#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <ctime>
#include <string>

/**
 * @brief Representa una notificacion o evento generado por el servidor.
 */
class Notification {
private:
    std::time_t time;
    std::string type;
    std::string user;
    std::string detail;

public:
    /**
     * @brief Constructor de la notificacion.
     * @param type_ Tipo de evento.
     * @param user_ Usuario asociado al evento.
     * @param detail_ Informacion adicional del evento.
     */
    Notification(const std::string& type_,
                 const std::string& user_,
                 const std::string& detail_);

    /**
     * @brief Devuelve la hora del evento en formato texto.
     * @return Hora del sistema sin salto de linea final.
     */
    std::string getTime() const;

    /**
     * @brief Devuelve la notificacion formateada para el log.
     * @return Linea completa lista para escribir en eventos.log.
     */
    std::string display() const;
};

#endif