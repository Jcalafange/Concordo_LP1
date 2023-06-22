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
     */
    Message(const std::string& content, const std::chrono::system_clock::time_point& timestamp);

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

private:
    std::string content; /**< O conteúdo da mensagem. */
    std::chrono::system_clock::time_point timestamp; /**< O timestamp da mensagem. */
};

#endif