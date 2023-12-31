#include <iostream>
#include <sstream>
#include "../include/sistema.h"


int main() {
    Sistema sistema;
    std::string input;
    std::string command;
    sistema.carregar();

    while (true) { 

        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        iss >> command;

        if (command == "quit") {

            std::cout << sistema.quit() << std::endl;
            sistema.salvar();
            
            break;
        } else if (command == "create-user") {
            
            std::string email, password, name;
            iss >> email >> password;
            std::getline(iss, name);
            std::cout << sistema.createUser(email, password, name) << std::endl;
            sistema.salvar();
            
        } else if (command == "login") {
            
            std::string email, password;
            iss >> email >> password;
            std::cout << sistema.login(email, password) << std::endl;
            
        } else if (sistema.isLoggedIn()) {
            if (command == "disconnect") {
                
                std::cout << sistema.disconnect() << std::endl;
                
            } else if (command == "create-server") {
                
                std::string serverName;
                iss >> serverName;
                std::cout << sistema.createServer(serverName) << std::endl;
                sistema.salvar();
                
            } else if (command == "set-server-desc") {
                
                std::string serverName, description;
                iss >> serverName;
                std::getline(iss, description);
                std::cout << sistema.setServerDescription(serverName, description) << std::endl;
                sistema.salvar();
                
            } else if (command == "set-server-invitecode") {
                
                std::string serverName, inviteCode;
                iss >> serverName >> inviteCode;
                std::cout << sistema.setServerInviteCode(serverName, inviteCode) << std::endl;
                sistema.salvar();
                
            } else if (command == "list-servers") {
                
                std::cout << sistema.listServers() << std::endl;
                
            } else if (command == "remove-server") {
                
                std::string serverName;
                iss >> serverName;
                std::cout << sistema.removeServer(serverName) << std::endl;
                sistema.salvar();
                
            } else if (command == "enter-server") {
                
                std::string serverName, inviteCode;
                iss >> serverName;
                std::getline(iss, inviteCode);
                std::cout << sistema.enterServer(serverName, inviteCode) << std::endl;
                sistema.salvar();
                
            } else if (command == "leave-server") {
                
                std::cout << sistema.leaveServer() << std::endl;
                sistema.salvar();
                
            } else if (command == "list-participants") {
                
                std::cout << sistema.listParticipants() << std::endl;
                
            } else if (command == "create-channel") {
                if (sistema.getCurrentServer() != nullptr) {
                    
                    std::string channelName, channelType;
                    iss >> channelName >> channelType;
                    sistema.getCurrentServer()->createChannel(channelName, channelType);
                    sistema.salvar();
                    
                } else {
                    
                    std::cout << "Nenhum servidor selecionado." << std::endl;
                    
                }
            } else if (command == "list-channels") {
                
                if (sistema.getCurrentServer() != nullptr) {
                    sistema.getCurrentServer()->listChannels();
                    
                } else {
                    std::cout << "Nenhum servidor selecionado." << std::endl;
                    
                }
            }else if (command == "enter-channel") {
                
                std::string channelName;
                iss >> channelName;
                std::cout << sistema.enterChannel(channelName) << std::endl;
                sistema.salvar();
                
            }else if (command == "leave-channel") {
                
                std::cout << sistema.leaveChannel() << std::endl;
                sistema.salvar();
                
            }else if (command == "send-message") {
                
                std::string content;
                std::getline(std::cin, content);
                std::cout << sistema.sendMessage(content) << std::endl;
                sistema.salvar();
                
            }else if (command == "list-messages") {
                
                sistema.listMessages();
                
            }else {
                std::cout << "Comando inválido!" << std::endl;
                
            }
        } else {
            
            std::cout << "Faça o login para acessar os comandos!" << std::endl;
            
        }
    }

    return 0;
}
