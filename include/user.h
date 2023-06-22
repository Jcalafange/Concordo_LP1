/**
 * @file user.h
 * @brief Classe que representa um usuário.
 */

#ifndef USER_H
#define USER_H

#include <string>
#include "../include/server.h"

/**
 * @class User
 * @brief Classe que representa um usuário.
 */
class User {
public:
    /**
     * @brief Construtor da classe User.
     * @param id O ID do usuário.
     * @param email O email do usuário.
     * @param password A senha do usuário.
     * @param name O nome do usuário.
     */
    User(int id, const std::string& email, const std::string& password, const std::string& name);

    /**
     * @brief Obtém o ID do usuário.
     * @return O ID do usuário.
     */
    int getId() const;

    /**
     * @brief Obtém o email do usuário.
     * @return O email do usuário.
     */
    std::string getEmail() const;

    /**
     * @brief Obtém a senha do usuário.
     * @return A senha do usuário.
     */
    std::string getPassword() const;

    /**
     * @brief Obtém o nome do usuário.
     * @return O nome do usuário.
     */
    std::string getName() const;

    /**
     * @brief Define o servidor atual do usuário.
     * @param server O servidor atual do usuário.
     */
    void setCurrentServer(Server* server);

private:
    int id; /**< O ID do usuário. */
    std::string email; /**< O email do usuário. */
    std::string password; /**< A senha do usuário. */
    std::string name; /**< O nome do usuário. */
    Server* currentServer; /**< O servidor atual do usuário. */
};

#endif
