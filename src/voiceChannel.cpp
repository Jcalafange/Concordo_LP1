#include "../include/voiceChannel.h"

VoiceChannel::VoiceChannel(const std::string& name) : Channel(name), lastMessage() {}

void VoiceChannel::addMessage(const Message& message) {
    lastMessage = message;
}

Message VoiceChannel::getLastMessage() const {
    return lastMessage;
}