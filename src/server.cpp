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

void Server::createChannel(const std::string& name, const std::string& type) {
    // Verificar se já existe um canal com o mesmo nome e tipo
    for (Channel* channel : channels) {
        if (channel->getName() == name && channel->getType() == type) {
            std::cout << "Um canal com o mesmo nome e tipo já existe no servidor." << std::endl;
            return;
        }
    }

    // Criar o canal correspondente ao tipo informado
    if (type == "texto") {
        TextChannel* channel = new TextChannel(name);
        addChannel(channel);
        std::cout << "Canal de texto '" << name << "' criado." << std::endl;
    } else if (type == "voz") {
        VoiceChannel* channel = new VoiceChannel(name);
        addChannel(channel);
        std::cout << "Canal de voz '" << name << "' criado." << std::endl;
    } else {
        std::cout << "Tipo de canal inválido. O tipo deve ser 'texto' ou 'voz'." << std::endl;
    }
}

void Server::listChannels() const {
    std::cout << "# Canais de texto:" << std::endl;
    for (Channel* channel : channels) {
        if (channel->getType() == "texto") {
            std::cout << channel->getName() << std::endl;
        }
    }

    std::cout << "# Canais de áudio:" << std::endl;
    for (Channel* channel : channels) {
        if (channel->getType() == "voz") {
            std::cout << channel->getName() << std::endl;
        }
    }
}


std::vector<Channel*> Server::getChannels() const {
    return channels;
}

void Server::setParticipantIDs(const std::vector<int>& participantIDs) {
    this->participantIDs = participantIDs;
}

void Server::setChannels(const std::vector<Channel*>& channels) {
    this->channels = channels;
}

void Server::addParticipant(int userId) {
    participantIDs.push_back(userId);
}

void Server::removeParticipant(int userId) {
    // Procura o ID do usuário na lista de participantes
    auto it = std::find(participantIDs.begin(), participantIDs.end(), userId);
    
    // Remove o participante se encontrado
    if (it != participantIDs.end()) {
        participantIDs.erase(it);
    }
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

bool Server::isInviteOnly() const {
    return inviteCode.empty();
}