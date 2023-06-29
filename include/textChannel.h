/**
 * @file textchannel.h
 * @brief Classe que representa um canal de texto.
 */

#ifndef TEXTCHANNEL_H
#define TEXTCHANNEL_H

#include "channel.h"
#include "message.h"
#include <vector>

/**
 * @class TextChannel
 * @brief Classe que representa um canal de texto, derivada da classe Channel.
 */
class TextChannel : public Channel {
public:
    /**
     * @brief Construtor da classe TextChannel.
     * @param name O nome do canal de texto.
     */
    TextChannel(const std::string& name);

    /**
     * @brief Adiciona uma mensagem ao canal de texto.
     * @param message A mensagem a ser adicionada.
     */
    void addMessage(const Message& message);

    /**
     * @brief Obtém as mensagens do canal de texto.
     * @return Um vetor contendo as mensagens do canal de texto.
     */
    std::vector<Message> getMessages() const;

    /**
     * @brief Obtém o tipo do canal de texto.
     * @return o tipo canal de texto.
     */
    std::string getType() const override;

private:
    std::vector<Message> messages; /**< Vetor de mensagens do canal de texto. */
};

#endif
