#include "../include/sistema.h"

Sistema::Sistema() : currentUser(nullptr), currentServer(nullptr), currentChannel(nullptr) {}

void Sistema::addUser(const User& user) {

    users.push_back(user);
}

bool Sistema::isLoggedIn() const {
    return (currentUser != nullptr);
}


User* Sistema::getUserById(int userId) const{
    for (auto& user : users ) {
        if (user.getId() == userId) {
            return const_cast<User*>(&user);
        }
    }
    return nullptr;
}

void Sistema::addServer(const Server& server) {

    servers.push_back(server);
}

Server* Sistema::getServerByName(const std::string& serverName) {
    for (auto& server : servers ) {
            if (server.getName() == serverName) {
                return &server;
            }
        }
    return nullptr;
}

User* Sistema::getCurrentUser() const { return currentUser; }

void Sistema::setCurrentUser(User* user) { currentUser = user;}

Channel* Sistema::getCurrentChannel() const { return currentChannel; }

void Sistema::setCurrentChannel(Channel* channel) { currentChannel = channel;}

std::string Sistema::createUser(const std::string& email, const std::string& password, const std::string& name){
    //verifica se ja existe um usuario com o mesmo email
    for (const auto& user : users) {
        if (user.getEmail() == email) {
            if (user.getEmail() == email) {
                return " Erro: Já existe um usuário com esse email.";
            }
        }
    }

    //gera o proximo ID
    int nextId = users.size() + 1;

    //Cria o novo usuário
    User newUser(nextId, name, email, password);
    users.push_back(newUser);

    return "Usuário criado com sucesso. ID do usuário: " + std::to_string(nextId);
     
}

std::string Sistema::login(const std::string& email, const std::string& password){
    // verifica se ja existe um usuario com o mesmo email e senha
    for (auto& user : users){
        if (user.getEmail() == email && user.getPassword() == password){
            currentUser = &user;
            return "Login Realizado com sucesso. Bem-vindo, " + user.getName() + "!";
        }
    }

    return "Erro: Email ou senha inválidos.";
}

std::string Sistema::quit(){
    // limpa os dados do usuario atual
    currentUser = nullptr;
    currentServer = nullptr;
    currentChannel = nullptr;

    return "Saindo do sistema...";
}

std::string Sistema::disconnect() {
    if (isLoggedIn()) {
        std::string userEmail = currentUser->getEmail();
        currentUser = nullptr;
        currentServer = nullptr;
        currentChannel = nullptr;
        return "Desconectando usuário " + userEmail;
    } else {
        return "Não está conectado";
    }
}


std::string Sistema::createServer(const std::string& serverName) {
    // Verifica se já existe um servidor com o mesmo nome
    for (const auto& server : servers) {
        if (server.getName() == serverName) {
            return "Servidor com esse nome já existe.";
        }
    }

    // Obtém o ID do usuário logado
    int ownerId = currentUser->getId();

    // Cria o novo servidor
    Server newServer(ownerId, serverName, "","");
    servers.push_back(newServer);

    return "Servidor criado.";
}

std::string Sistema::setServerDescription(const std::string& serverName, const std::string& description) {
    // Verifica se o servidor existe
    bool serverExists = false;
    for (auto& server : servers) {
        if (server.getName() == serverName) {
            serverExists = true;

            // Verifica se o usuário é o dono do servidor
            if (server.getOwnerUserId() == currentUser->getId()) {
                server.setDescription(description);
                return "Descrição do servidor '" + serverName + "' modificada!";
            } else {
                return "Você não pode alterar a descrição de um servidor que não foi criado por você.";
            }
        }
    }

    if (!serverExists) {
        return "Servidor '" + serverName + "' não existe.";
    }
    return "";
}

std::string Sistema::setServerInviteCode(const std::string& serverName, const std::string& inviteCode) {
    // Verifica se o servidor existe
    bool serverExists = false;
    for (auto& server : servers) {
        if (server.getName() == serverName) {
            serverExists = true;

            // Verifica se o usuário é o dono do servidor
            if (server.getOwnerUserId() == currentUser->getId()) {
                server.setInviteCode(inviteCode);
                return "Código de convite do servidor '" + serverName + "' modificado!";
            } else {
                return "Você não pode alterar o código de convite de um servidor que não foi criado por você.";
            }
        }
    }

    if (!serverExists) {
        return "Servidor '" + serverName + "' não existe.";
    }
    return "";
}

std::string Sistema::listServers() const {
    std::string serverList;

    for (const auto& server : servers) {
        serverList += server.getName() + "\n";
    }

    return serverList;
}

std::string Sistema::removeServer(const std::string& serverName) {
    for (auto it = servers.begin(); it != servers.end(); ++it) {
        if (it->getName() == serverName) {
            // Verifica se o usuário é o dono do servidor
            if (it->getOwnerUserId() == currentUser->getId()) {
                servers.erase(it);
                return "Servidor '" + serverName + "' removido";
            } else {
                return "Você não é o dono do servidor '" + serverName + "'";
            }
        }
    }

    return "Servidor '" + serverName + "' não encontrado";
}

std::string Sistema::enterServer(const std::string& serverName, const std::string& inviteCode) {
    // Verifica se o usuário está logado
    if (!currentUser) {
        return "Você precisa estar logado para entrar em um servidor.";
    }

    // Procura o servidor pelo nome
    for (auto& server : servers) {
        if (server.getName() == serverName) {
            // Verifica se o usuário é o dono do servidor
            if (server.getOwnerUserId() == currentUser->getId()) {
                server.addParticipant(currentUser->getId());
                currentUser->setCurrentServer(&server);
                return "Entrou no servidor com sucesso.";
            } else if (server.getInviteCode().empty()) {
                server.addParticipant(currentUser->getId());
                currentUser->setCurrentServer(&server);
                return "Entrou no servidor com sucesso.";
            } else if (inviteCode == server.getInviteCode()) {
                server.addParticipant(currentUser->getId());
                currentUser->setCurrentServer(&server);
                return "Entrou no servidor com sucesso.";
            } else {
                return "Servidor requer código de convite válido.";
            }
        }
    }

    return "Servidor '" + serverName + "' não encontrado.";
}



std::string Sistema::leaveServer() {
    if (currentServer) {
        std::string serverName = currentServer->getName();
        currentServer = nullptr;
        currentChannel = nullptr;
        return "Saindo do servidor '" + serverName + "'";
    } else {
        return "Você não está visualizando nenhum servidor";
    }
}

std::string Sistema::listParticipants() const {
    if (currentServer) {
        std::string participantList;

        const std::vector<int>& participantIds = currentServer->getParticipantIDs();
        for (int userId : participantIds) {
            User* user = getUserById(userId);
            if (user) {
                participantList += user->getName() + "\n";
            }
        }

        return participantList;
    } else {
        return "Você não está visualizando nenhum servidor";
    }
}



