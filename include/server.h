        /**
        * @file server.h
        * @brief Classe que representa um servidor.
        */

        #ifndef SERVER_H
        #define SERVER_H

        #include <iostream>
        #include <algorithm>
        #include <string>
        #include <vector>
        #include "channel.h"
        #include "textchannel.h"
        #include "voicechannel.h"


        /**
        * @class Server
        * @brief Classe que representa um servidor.
        */
        class Server {
        public:
            /**
            * @brief Construtor da classe Server.
            * @param ownerUserId O ID do usuário proprietário do servidor.
            * @param name O nome do servidor.
            * @param description A descrição do servidor.
            * @param inviteCode O código de convite do servidor.
            */
            Server(int ownerUserId, const std::string& name, const std::string& description, const std::string& inviteCode);

            /**
            * @brief Obtém o ID do usuário proprietário do servidor.
            * @return O ID do usuário proprietário do servidor.
            */
            int getOwnerUserId() const;

            /**
            * @brief Obtém o nome do servidor.
            * @return O nome do servidor.
            */
            std::string getName() const;

            /**
            * @brief Obtém a descrição do servidor.
            * @return A descrição do servidor.
            */
            std::string getDescription() const;

            /**
            * @brief Obtém o código de convite do servidor.
            * @return O código de convite do servidor.
            */
            std::string getInviteCode() const;

            /**
            * @brief Adiciona um canal ao servidor.
            * @param channel O canal a ser adicionado.
            */
            void addChannel(Channel* channel);

            /**
            * @brief cria um canal ao serivor com suas caracteristicas
            * @param channel O canal a ser adicionado.
            */
            void createChannel(const std::string& name, const std::string& type);

            /**
            *@brief lista os canais dentro de um servidor
            */
            void listChannels() const;

            /**
            * @brief Obtém os canais do servidor.
            * @return Um vetor contendo os canais do servidor.
            */
            std::vector<Channel*> getChannels() const;

            /**
            * @brief Obtém os IDs dos participantes do servidor.
            * @return Um vetor contendo os IDs dos participantes do servidor.
            */
            std::vector<int> getParticipantIDs() const;

            /**
            * @brief Define a descrição do servidor.
            * @param newDescription A nova descrição do servidor.
            */
            void setDescription(const std::string& newDescription);

            /**
            * @brief Define o código de convite do servidor.
            * @param newInviteCode O novo código de convite do servidor.
            */
            void setInviteCode(const std::string& newInviteCode);

            /**
            * @brief Adiciona um participante ao servidor.
            * @param userId O ID do usuário a ser adicionado.
            */
            void addParticipant(int userId);

            /**
            * @brief remove um participante ao servidor.
            * @param userId O ID do usuário a ser removido.
            */
            void removeParticipant(int userId);

            /**
            * @brief Verifica se um usuário é participante do servidor.
            * @param userId O ID do usuário a ser verificado.
            * @return true se o usuário é participante, false caso contrário.
            */
            bool isParticipant(int userId) const;

        private:
            int ownerUserId; /**< O ID do usuário proprietário do servidor. */
            std::string name; /**< O nome do servidor. */
            std::string description; /**< A descrição do servidor. */
            std::string inviteCode; /**< O código de convite do servidor. */
            std::vector<Channel*> channels; /**< Os canais do servidor. */
            std::vector<int> participantIDs; /**< Os IDs dos participantes do servidor. */
        };

        #endif
