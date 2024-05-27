#include "Usuario.h"
#include <sstream>
#include <iomanip>

// Constructor
Usuario::Usuario(const std::string &id, const std::string &user, const std::string &userName, const std::string &description,
                 const std::vector<std::string> &friends, int countFriend, const std::string &lastLogin, const std::string &firstLogin)
        : id(id), user(user), userName(userName), description(description), friends(friends), countFriend(countFriend), lastLogin(lastLogin), firstLogin(firstLogin) {}

// Getters
std::string Usuario::getId() const {
    return id;
}

std::string Usuario::getUser() const {
    return user;
}

std::string Usuario::getUserName() const {
    return userName;
}

std::string Usuario::getDescription() const {
    return description;
}

std::vector<std::string> Usuario::getFriends() const {
    return friends;
}

std::string Usuario::getFriendsStr() const {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < friends.size(); ++i) {
        if (i > 0) {
            oss << ";";
        }
        oss << friends[i];
    }
    oss << "]";
    return oss.str();
}

int Usuario::getCountFriend() const {
    return countFriend;
}

std::string Usuario::getLastLogin() const {
    return lastLogin;
}

std::string Usuario::getFirstLogin() const {
    return firstLogin;
}

// Setters
void Usuario::setId(const std::string &id) {
    this->id = id;
}

void Usuario::setUser(const std::string &user) {
    this->user = user;
}

void Usuario::setUserName(const std::string &userName) {
    this->userName = userName;
}

void Usuario::setDescription(const std::string &description) {
    this->description = description;
}

void Usuario::setFriends(const std::vector<std::string> &friends) {
    this->friends = friends;
}

void Usuario::setCountFriend(int countFriend) {
    this->countFriend = countFriend;
}

void Usuario::setLastLogin(const std::string &lastLogin) {
    this->lastLogin = lastLogin;
}

void Usuario::setFirstLogin(const std::string &firstLogin) {
    this->firstLogin = firstLogin;
}
