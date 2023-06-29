#include "../include/channel.h"

Channel::Channel(const std::string& name) : name(name) {}

std::string Channel::getName() const { return name; }

std::string Channel::getType() const {
    return "Base";
}