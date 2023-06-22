#include <../include/message.h>

Message::Message(const std::string& content, const std::chrono::system_clock::time_point& timestamp)
    : content(content), timestamp(timestamp) {}

std::string Message::getContent() const {
    return content;
}

std::chrono::system_clock::time_point Message::getTimestamp() const {
    return timestamp;
}

Message::Message() : content(""), timestamp(std::chrono::system_clock::now()) {}
