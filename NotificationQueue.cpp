#include "NotificationQueue.h"

void NotificationQueue::push(const Notification& n) {
    std::lock_guard<std::mutex> lock(mtx);

    if (queue.size() >= 100) {
        queue.pop();
    }

    queue.push(n);
    cv.notify_one();
}

Notification NotificationQueue::pop() {
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [this]() {
        return !queue.empty();
    });

    Notification n = queue.front();
    queue.pop();

    return n;
}