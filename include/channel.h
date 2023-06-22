/**
 * @file channel.h
 * @brief Classe que representa um canal de comunicação.
 */

#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>

/**
 * @class Channel
 * @brief Classe que representa um canal de comunicação.
 */
class Channel {
public:
    /**
     * @brief Construtor da classe Channel.
     * @param name O nome do canal.
     */
    Channel(const std::string& name);

    /**
     * @brief Obtém o nome do canal.
     * @return O nome do canal.
     */
    std::string getName() const;

private:
    std::string name; /**< O nome do canal. */
};

#endif
