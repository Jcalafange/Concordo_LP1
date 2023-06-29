#include <../include/message.h>

Message::Message(const std::string& content, const std::chrono::system_clock::time_point& timestamp, const std::string& senderName)
    : content(content), timestamp(timestamp), senderName(senderName) {}

std::string Message::getContent() const {
    return content;
}

std::chrono::system_clock::time_point Message::getTimestamp() const {
    return timestamp;
}

int Message::getUserId() const {
    return userId;
}

std::string Message::getSenderName() const {
    return senderName;
}

Message::Message() : content(""), timestamp(std::chrono::system_clock::now()) {}
