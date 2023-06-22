/**
 * @file voicechannel.h
 * @brief Classe que representa um canal de voz.
 */

#ifndef VOICECHANNEL_H
#define VOICECHANNEL_H

#include "channel.h"
#include "message.h"

/**
 * @class VoiceChannel
 * @brief Classe que representa um canal de voz.
 */
class VoiceChannel : public Channel {
public:
    /**
     * @brief Construtor da classe VoiceChannel.
     * @param name O nome do canal de voz.
     */
    VoiceChannel(const std::string& name);

    /**
     * @brief Adiciona uma mensagem ao canal de voz.
     * @param message A mensagem a ser adicionada.
     */
    void addMessage(const Message& message);

    /**
     * @brief Obtém a última mensagem do canal de voz.
     * @return A última mensagem do canal de voz.
     */
    Message getLastMessage() const;

private:
    Message lastMessage; /**< A última mensagem do canal de voz. */
};

#endif