#ifndef NOTIFICATIONQUEUE_H
#define NOTIFICATIONQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

#include "Notification.h"

/**
 * @brief Cola segura para comunicar el servidor con el consumidor de eventos.
 */
class NotificationQueue {
private:
    std::queue<Notification> queue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    /**
     * @brief Inserta una notificacion en la cola.
     * @param n Notificacion a insertar.
     */
    void push(const Notification& n);

    /**
     * @brief Espera hasta que haya una notificacion y la extrae.
     * @return Primera notificacion disponible.
     */
    Notification pop();
};

#endif