#include "../include/user.h"
#include "../include/server.h"


User::User(int id, const std::string& name, const std::string& email, const std::string& password)
    : id(id), name(name), email(email), password(password) {}

int User::getId() const { return id; }

std::string User::getName() const { return name; }

std::string User::getEmail() const { return email; }

std::string User::getPassword() const { return password; }

void User::setCurrentServer(Server* server) {
    currentServer = server;
}