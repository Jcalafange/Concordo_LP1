#include <iostream>
#include <sstream>
#include "../include/sistema.h"

int main() {
    Sistema sistema;
    std::string input;
    std::string command;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        iss >> command;

        if (command == "quit") {
            std::cout << sistema.quit() << std::endl;
            break;
        } else if (command == "create-user") {
            std::string email, password, name;
            iss >> email >> password;
            std::getline(iss, name);
            std::cout << sistema.createUser(email, password, name) << std::endl;
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
            } else if (command == "set-server-desc") {
                std::string serverName, description;
                iss >> serverName;
                std::getline(iss, description);
                std::cout << sistema.setServerDescription(serverName, description) << std::endl;
            } else if (command == "set-server-invitecode") {
                std::string serverName, inviteCode;
                iss >> serverName >> inviteCode;
                std::cout << sistema.setServerInviteCode(serverName, inviteCode) << std::endl;
            } else if (command == "list-servers") {
                std::cout << sistema.listServers() << std::endl;
            } else if (command == "remove-server") {
                std::string serverName;
                iss >> serverName;
                std::cout << sistema.removeServer(serverName) << std::endl;
            } else if (command == "enter-server") {
                std::string serverName, inviteCode;
                iss >> serverName;
                std::getline(iss, inviteCode);
                std::cout << sistema.enterServer(serverName, inviteCode) << std::endl;
            } else if (command == "leave-server") {
                std::cout << sistema.leaveServer() << std::endl;
            } else if (command == "list-participants") {
                std::cout << sistema.listParticipants() << std::endl;
            } else {
                std::cout << "Comando inválido!" << std::endl;
            }
        } else {
            std::cout << "Faça o login para acessar os comandos!" << std::endl;
        }
    }

    return 0;
}
