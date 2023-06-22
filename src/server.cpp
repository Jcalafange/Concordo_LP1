#include "../include/server.h"

Server::Server(int ownerUserId, const std::string& name, const std::string& description, const std::string& inviteCode)
    : ownerUserId(ownerUserId), name(name), description(description), inviteCode(inviteCode) {}

int Server::getOwnerUserId() const {
    return ownerUserId;
}

std::string Server::getName() const {
    return name;
}

std::string Server::getDescription() const {
    return description;
}

std::string Server::getInviteCode() const {
    return inviteCode;
}

void Server::addChannel(Channel* channel) {
    channels.push_back(channel);
}

std::vector<Channel*> Server::getChannels() const {
    return channels;
}

void Server::addParticipant(int userId) {
    participantIDs.push_back(userId);
}

std::vector<int> Server::getParticipantIDs() const {
    return participantIDs;
}

void Server::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Server::setInviteCode(const std::string& newInviteCode) {
    inviteCode = newInviteCode;
}

bool Server::isParticipant(int userId) const {
    for (int participantId : participantIDs) {
        if (participantId == userId) {
            return true;
        }
    }
    return false;
}
