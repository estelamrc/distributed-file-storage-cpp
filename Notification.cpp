#include "Notification.h"

Notification::Notification(const std::string& type_,
                           const std::string& user_,
                           const std::string& detail_)
    : time(std::time(nullptr)),
      type(type_),
      user(user_),
      detail(detail_) {
}

std::string Notification::getTime() const {
    std::string t = std::ctime(&time);

    if (!t.empty() && t.back() == '\n') {
        t.pop_back();
    }

    return t;
}

std::string Notification::display() const {
    return this->getTime() + "\t" + type + "\t" + user + "\t" + detail;
}