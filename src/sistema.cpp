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

Server* Sistema::getCurrentServer() const { return currentServer; }

User* Sistema::getCurrentUser() const { return currentUser; }

void Sistema::setCurrentUser(User* user) { currentUser = user;}

Channel* Sistema::getCurrentChannel() const { return currentChannel; }

void Sistema::setCurrentChannel(Channel* channel) { currentChannel = channel;}

std::string Sistema::createUser(const std::string& email, const std::string& password, const std::string& name){
    if(!isLoggedIn()){
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
    }else{ return "Disconect-se para criar um novo usuário";}

}

std::string Sistema::login(const std::string& email, const std::string& password){
    if(!isLoggedIn()){
    // verifica se ja existe um usuario com o mesmo email e senha
    for (auto& user : users){
        if (user.getEmail() == email && user.getPassword() == password){
            currentUser = &user;
            return "Login Realizado com sucesso. Bem-vindo, " + user.getName() + "!";
        }
    }

    return "Erro: Email ou senha inválidos.";
    }else{ return "Erro: você ja esta logado em uma conta."; }
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
    if (!currentUser) {
        return "Você precisa estar logado para entrar em um servidor.";
    }

    Server* foundServer = nullptr;

    for (auto& server : servers) {
        if (server.getName() == serverName) {
            if (server.getOwnerUserId() == currentUser->getId() || server.getInviteCode().empty()) {
                foundServer = &server;
                break;
            } else if (inviteCode == server.getInviteCode()) {
                foundServer = &server;
                break;
            } else {
                return "Servidor requer código de convite válido.";
            }
        }
    }

    if (foundServer) {
        foundServer->addParticipant(currentUser->getId());
        currentServer = foundServer;
        return "Entrou no servidor com sucesso.";
    } else {
        return "Servidor '" + serverName + "' não encontrado.";
    }
}

std::string Sistema::enterChannel(const std::string& channelName) {
    if (!isLoggedIn()) {
        return "Faça o login para acessar os comandos!";
    }

    if (currentServer == nullptr) {
        return "Não está em nenhum servidor no momento";
    }

    // Procura o canal com o nome especificado
    for (Channel* channel : currentServer->getChannels()) {
        if (channel->getName() == channelName) {
            // Atualiza o canal atual
            currentChannel = channel;
            return "Entrou no canal '" + channelName + "'";
        }
    }

    return "Canal '" + channelName + "' não existe";
}

std::string Sistema::leaveChannel() {
    if (!isLoggedIn()) {
        return "Faça o login para acessar os comandos!";
    }

    if (currentChannel == nullptr) {
        return "Não está em nenhum canal no momento";
    }

    // Seta o canal atual como nullptr para indicar que não está em nenhum canal
    currentChannel = nullptr;

    return "Saindo do canal";
}

std::string Sistema::leaveServer() {
    if (currentServer) {
        std::string serverName = currentServer->getName();
        currentServer->removeParticipant(currentUser->getId()); // Remova o usuário da lista de participantes do servidor
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

std::string Sistema::sendMessage(const std::string& content) {
    if (!isLoggedIn()) {
        return "Faça o login para acessar os comandos!";
    }

    if (currentChannel == nullptr) {
        return "Não está em nenhum canal no momento";
    }

    // Obtém o ID do usuário logado
    std::string senderName = currentUser->getName();

    // Cria a mensagem com o conteúdo digitado, data/hora atual e ID do usuário
    Message message(content, std::chrono::system_clock::now(), senderName);

    // Adiciona a mensagem ao canal atual
    currentChannel->addMessage(message);

    return "Mensagem enviada com sucesso";
}

void Sistema::listMessages() const {
    if (!isLoggedIn()) {
        std::cout << "Nenhum usuário logado." << std::endl;
        return;
    }

    if (!currentChannel) {
        std::cout << "Nenhum canal selecionado." << std::endl;
        return;
    }

    std::vector<Message> messages;

    if (currentChannel->getType() == "texto") {
        TextChannel* textChannel = dynamic_cast<TextChannel*>(currentChannel);
        if (textChannel) {
            messages = textChannel->getMessages();
        }
    } else if (currentChannel->getType() == "voz") {
        VoiceChannel* voiceChannel = dynamic_cast<VoiceChannel*>(currentChannel);
        if (voiceChannel) {
            messages.push_back(voiceChannel->getLastMessage());
        }
    }

    if (messages.empty()) {
        std::cout << "Sem mensagens para exibir." << std::endl;
        return;
    }

    for (const Message& message : messages) {
        std::time_t timestamp = std::chrono::system_clock::to_time_t(message.getTimestamp());
        std::cout << message.getSenderName() << "<" << std::put_time(std::localtime(&timestamp), "%d/%m/%Y - %H:%M") << ">: " << message.getContent() << std::endl;
    }
}


