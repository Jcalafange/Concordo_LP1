#include "../include/textChannel.h"

TextChannel::TextChannel(const std::string& name) : Channel(name) {}

void TextChannel::addMessage(const Message& message) {
    messages.push_back(message);
}

std::vector<Message> TextChannel::getMessages() const {
    return messages;
}