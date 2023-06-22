/**
 * @file sistema.h
 * @brief Classe que representa o sistema.
 */

#ifndef SISTEMA_H
#define SISTEMA_H

#include <vector>
#include "user.h"
#include "server.h"

/**
 * @class Sistema
 * @brief Classe que representa o sistema.
 */
class Sistema {
public:
    /**
     * @brief Construtor da classe Sistema.
     */
    Sistema();

    /**
     * @brief Adiciona um usuário ao sistema.
     * @param user O usuário a ser adicionado.
     */
    void addUser(const User& user);

    /**
     * @brief Obtém um usuário pelo seu ID.
     * @param userId O ID do usuário.
     * @return Um ponteiro para o usuário encontrado ou nullptr se não encontrado.
     */
    User* getUserById(int userId) const;

    /**
     * @brief Adiciona um servidor ao sistema.
     * @param server O servidor a ser adicionado.
     */
    void addServer(const Server& server);

    /**
     * @brief Obtém um servidor pelo seu nome.
     * @param serverName O nome do servidor.
     * @return Um ponteiro para o servidor encontrado ou nullptr se não encontrado.
     */
    Server* getServerByName(const std::string& serverName);

    /**
     * @brief Obtém o usuário atual.
     * @return Um ponteiro para o usuário atual.
     */
    User* getCurrentUser() const;

    /**
     * @brief Define o usuário atual.
     * @param user O usuário atual.
     */
    void setCurrentUser(User* user);

    /**
     * @brief Obtém o servidor atual.
     * @return Um ponteiro para o servidor atual.
     */
    Server* getCurrentServer() const;

    /**
     * @brief Define o servidor atual.
     * @param server O servidor atual.
     */
    void setCurrentServer(const Server* server);

    /**
     * @brief Obtém o canal atual.
     * @return Um ponteiro para o canal atual.
     */
    Channel* getCurrentChannel() const;

    /**
     * @brief Define o canal atual.
     * @param channel O canal atual.
     */
    void setCurrentChannel(Channel* channel);

    /**
     * @brief Verifica se o usuário está logado.
     * @return true se o usuário está logado, false caso contrário.
     */
    bool isLoggedIn() const;

    /**
     * @brief Cria um novo usuário no sistema.
     * @param email O email do usuário.
     * @param password A senha do usuário.
     * @param name O nome do usuário.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string createUser(const std::string& email, const std::string& password, const std::string& name);

    /**
     * @brief Realiza o login de um usuário no sistema.
     * @param email O email do usuário.
     * @param password A senha do usuário.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string login(const std::string& email, const std::string& password);

    /**
     * @brief Finaliza a execução do sistema.
     * @return Uma mensagem de encerramento.
     */
    std::string quit();

    /**
     * @brief Desconecta o usuário do sistema.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string disconnect();

    /**
     * @brief Cria um novo servidor.
     * @param serverName O nome do servidor.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string createServer(const std::string& serverName);

    /**
     * @brief Define a descrição de um servidor.
     * @param serverName O nome do servidor.
     * @param description A nova descrição do servidor.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string setServerDescription(const std::string& serverName, const std::string& description);

    /**
     * @brief Define o código de convite de um servidor.
     * @param serverName O nome do servidor.
     * @param inviteCode O novo código de convite do servidor.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string setServerInviteCode(const std::string& serverName, const std::string& inviteCode = "");

    /**
     * @brief Lista os servidores disponíveis.
     * @return Uma mensagem com a lista de servidores ou uma mensagem de erro.
     */
    std::string listServers() const;

    /**
     * @brief Remove um servidor.
     * @param serverName O nome do servidor a ser removido.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string removeServer(const std::string& serverName);

    /**
     * @brief Entra em um servidor.
     * @param serverName O nome do servidor.
     * @param inviteCode O código de convite do servidor.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string enterServer(const std::string& serverName, const std::string& inviteCode);

    /**
     * @brief Sai do servidor atual.
     * @return Uma mensagem de sucesso ou erro.
     */
    std::string leaveServer();

    /**
     * @brief Obtém os IDs dos participantes do servidor atual.
     * @return Um vetor contendo os IDs dos participantes do servidor atual.
     */
    const std::vector<int>& getParticipantIds() const;

    /**
     * @brief Lista os participantes do servidor atual.
     * @return Uma mensagem com a lista de participantes ou uma mensagem de erro.
     */
    std::string listParticipants() const;

private:
    std::vector<User> users; /**< Vetor de usuários do sistema. */
    std::vector<Server> servers; /**< Vetor de servidores do sistema. */
    User* currentUser; /**< Usuário atual. */
    Server* currentServer; /**< Servidor atual. */
    Channel* currentChannel; /**< Canal atual. */
};

#endif
