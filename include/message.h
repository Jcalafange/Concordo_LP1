/**
 * @file message.h
 * @brief Classe que representa uma mensagem.
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <chrono>

/**
 * @class Message
 * @brief Classe que representa uma mensagem.
 */
class Message {
public:
    /**
     * @brief Construtor padrão da classe Message.
     */
    Message();

    /**
     * @brief Construtor da classe Message.
     * @param content O conteúdo da mensagem.
     * @param timestamp O timestamp (tempo) da mensagem.
     * @param sendername O nome do remetente da mensagem.
     */
    Message(const std::string& content, const std::chrono::system_clock::time_point& timestamp, const std::string& senderName);

    /**
     * @brief Obtém o conteúdo da mensagem.
     * @return O conteúdo da mensagem.
     */
    std::string getContent() const;

    /**
     * @brief Obtém o timestamp da mensagem.
     * @return O timestamp da mensagem.
     */
    std::chrono::system_clock::time_point getTimestamp() const;

    /**
     *@brief obtém o id do usuario
     *@return o id do usuario
     */
    int getUserId() const;

    /**
     *@brief obtém o remetente da mensagem
     *@return o remetente da mensagem
     */
    std::string getSenderName() const;

private:
    std::string content; /**< O conteúdo da mensagem. */
    std::chrono::system_clock::time_point timestamp; /**< O timestamp da mensagem. */
    int userId;
    std::string senderName;
};

#endif