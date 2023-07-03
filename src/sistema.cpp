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

    // Obtém o ID do usuário
    int userId = currentUser->getId();

    // Cria a mensagem com o conteúdo digitado, data/hora atual e ID do usuário
    Message message(content, std::chrono::system_clock::now(), senderName , userId);

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

void Sistema::salvarUsuarios() {
    std::ofstream arquivo("usuarios.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de usuários." << std::endl;
        return;
    }

    arquivo << users.size() << std::endl; 

    for (const User& user : users) {
        arquivo << user.getId() << std::endl;
        arquivo << user.getName() << std::endl; 
        arquivo << user.getEmail() << std::endl;
        arquivo << user.getPassword() << std::endl;
    }

    arquivo.close();
}

void Sistema::salvarServidores() {
    std::ofstream arquivo("servidores.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de servidores." << std::endl;
        return;
    }

    arquivo << servers.size() << std::endl; // Escreve o total de servidores

    for (const Server& server : servers) {
        arquivo << server.getOwnerUserId() << std::endl; // Escreve o ID do dono do servidor
        arquivo << server.getName() << std::endl; // Escreve o nome do servidor
        arquivo << server.getDescription() << std::endl; // Escreve a descrição do servidor

        if (server.isInviteOnly()) {
            arquivo << server.getInviteCode() << std::endl; // Escreve o código de convite do servidor
        } else {
            arquivo << std::endl; // Se o servidor for aberto, escreve uma linha vazia
        }

        const std::vector<int>& participants = server.getParticipantIDs();
        arquivo << participants.size() << std::endl; // Escreve o número de participantes do servidor

        for (const int participantId : participants) {
            arquivo << participantId << std::endl; // Escreve o ID do participante
        }

        const std::vector<Channel*>& channels = server.getChannels();
        arquivo << channels.size() << std::endl; // Escreve o número de canais do servidor

        for (const Channel* channel : channels) {
            arquivo << channel->getName() << std::endl; // Escreve o nome do canal

            if (const TextChannel* textChannel = dynamic_cast<const TextChannel*>(channel)) {
                arquivo << "TEXTO" << std::endl; // Escreve o tipo do canal: TEXTO
                const std::vector<Message>& messages = textChannel->getMessages();
                arquivo << messages.size() << std::endl; // Escreve o número de mensagens do canal
                for (const Message& message : messages) {
                arquivo << message.getUserId() << std::endl; // Escreve o ID do usuário que escreveu a mensagem

                // Converte o objeto time_point para uma string formatada
                auto timestamp = message.getTimestamp();
                std::time_t timestampAsTimeT = std::chrono::system_clock::to_time_t(timestamp);
                std::tm* timestampLocalTime = std::localtime(&timestampAsTimeT);

                std::stringstream timestampStringStream;
                timestampStringStream << std::put_time(timestampLocalTime, "%d/%m/%Y");
                std::string timestampString = timestampStringStream.str();

                arquivo << timestampString << std::endl; // Escreve a data/hora da mensagem
                arquivo << message.getContent() << std::endl; // Escreve o conteúdo da mensagem
            }
            } else if (const VoiceChannel* voiceChannel = dynamic_cast<const VoiceChannel*>(channel)) {
            const Message& message = voiceChannel->getLastMessage();

            arquivo << "1" << std::endl; // O canal de voz sempre terá 1 mensagem
            arquivo << message.getUserId() << std::endl; // Escreve o ID do usuário que escreveu a mensagem

            // Converte o objeto time_point para uma string formatada
            auto timestamp = message.getTimestamp();
            std::time_t timestampAsTimeT = std::chrono::system_clock::to_time_t(timestamp);
            std::tm* timestampLocalTime = std::localtime(&timestampAsTimeT);

            std::stringstream timestampStringStream;
            timestampStringStream << std::put_time(timestampLocalTime, "%d/%m/%Y %H:%M:%S");
            std::string timestampString = timestampStringStream.str();

            arquivo << timestampString << std::endl; // Escreve a data/hora da mensagem
            arquivo << message.getContent() << std::endl; // Escreve o conteúdo da mensagem
            }
        }
    }

    arquivo.close();
}

void Sistema::salvar() {
    salvarUsuarios();
    salvarServidores();
}


void Sistema::carregarUsuarios() {
    std::ifstream arquivo("usuarios.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de usuários." << std::endl;
        return;
    }

    int totalUsuarios;
    arquivo >> totalUsuarios; // Lê o total de usuários do arquivo

    for (int i = 0; i < totalUsuarios; i++) {
        int id;
        std::string nome, email, senha;

        arquivo >> id; // Lê o ID do usuário
        arquivo.ignore(); // Ignora o caractere de quebra de linha

        std::getline(arquivo, nome); // Lê o nome do usuário
        std::getline(arquivo, email); // Lê o email do usuário
        std::getline(arquivo, senha); // Lê a senha do usuário

        // Crie o objeto User com os dados lidos e adicione-o ao sistema
        User user(id, nome, email, senha);
        users.push_back(user);
    }

    arquivo.close();
}


void Sistema::carregarServidores() {
    std::ifstream arquivo("servidores.txt");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de servidores." << std::endl;
        return;
    }

    int totalServidores;
    arquivo >> totalServidores; // Lê o total de servidores do arquivo

    for (int i = 0; i < totalServidores; i++) {
        int ownerUserId;
        std::string name, description, inviteCode;
        std::vector<int> participantIDs;
        std::vector<Channel*> channels;

        arquivo >> ownerUserId; // Lê o ID do usuário dono do servidor
        arquivo.ignore(); // Ignora o caractere de quebra de linha

        std::getline(arquivo, name); // Lê o nome do servidor
        std::getline(arquivo, description); // Lê a descrição do servidor

        std::getline(arquivo, inviteCode); // Lê o código de convite do servidor
        if (inviteCode.empty()) {
            // O servidor é aberto, não há código de convite
            inviteCode = ""; // Defina o código de convite como uma string vazia
        }

        int numParticipants;
        arquivo >> numParticipants; // Lê o número de participantes do servidor
        arquivo.ignore(); // Ignora o caractere de quebra de linha

        for (int j = 0; j < numParticipants; j++) {
            int participantId;
            arquivo >> participantId; // Lê o ID do participante
            arquivo.ignore(); // Ignora o caractere de quebra de linha
            participantIDs.push_back(participantId);
        }

        int numChannels;
        arquivo >> numChannels; // Lê o número de canais do servidor
        arquivo.ignore(); // Ignora o caractere de quebra de linha

        for (int j = 0; j < numChannels; j++) {
            std::string channelName, channelType;
            int numMessages;

            std::getline(arquivo, channelName); // Lê o nome do canal
            std::getline(arquivo, channelType); // Lê o tipo do canal

            if (channelType == "TEXTO") {
                TextChannel* textChannel = new TextChannel(channelName);

                arquivo >> numMessages; // Lê o número de mensagens do canal
                arquivo.ignore(); // Ignora o caractere de quebra de linha

                for (int k = 0; k < numMessages; k++) {
                    int userId;
                    std::string timestampString, content;

                    arquivo >> userId; // Lê o ID do usuário que escreveu a mensagem
                    arquivo.ignore(); // Ignora o caractere de quebra de linha

                    std::getline(arquivo, timestampString); // Lê a data/hora da mensagem
                    std::getline(arquivo, content); // Lê o conteúdo da mensagem

                    // Converte a string de data/hora para o tipo time_point
                    std::tm timestampLocalTime = {};
                    std::istringstream timestampStringStream(timestampString);
                    timestampStringStream >> std::get_time(&timestampLocalTime, "%d/%m/%Y");
                    auto timestamp = std::chrono::system_clock::from_time_t(std::mktime(&timestampLocalTime));

                    // Cria a mensagem com os dados lidos e adiciona ao canal de texto
                    Message message(content, timestamp, "", userId);
                    textChannel->addMessage(message);
                }

                channels.push_back(textChannel);
            } else if (channelType == "VOZ") {
                VoiceChannel* voiceChannel = new VoiceChannel(channelName);

                // Como o canal de voz só tem uma mensagem, podemos criar diretamente
                int userId;
                std::string timestampString, content;

                arquivo >> userId; // Lê o ID do usuário que escreveu a mensagem
                arquivo.ignore(); // Ignora o caractere de quebra de linha

                std::getline(arquivo, timestampString); // Lê a data/hora da mensagem
                std::getline(arquivo, content); // Lê o conteúdo da mensagem

                // Converte a string de data/hora para o tipo time_point
                std::tm timestampLocalTime = {};
                std::istringstream timestampStringStream(timestampString);
                timestampStringStream >> std::get_time(&timestampLocalTime, "%d/%m/%Y %H:%M:%S");
                auto timestamp = std::chrono::system_clock::from_time_t(std::mktime(&timestampLocalTime));

                // Cria a mensagem com os dados lidos e adiciona ao canal de voz
                Message message(content, timestamp, "", userId);
                voiceChannel->addMessage(message);

                channels.push_back(voiceChannel);
            }
        }

        // Cria o objeto Server com os dados lidos e adiciona-o ao sistema
        Server server(ownerUserId, name, description, inviteCode);
        server.setParticipantIDs(participantIDs);
        server.setChannels(channels);
        servers.push_back(server);
    }

    arquivo.close();
}

void Sistema::carregar() {
    carregarUsuarios();
    carregarServidores();
}