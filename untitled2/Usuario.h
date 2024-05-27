//
// Created by nicol on 26-05-2024.
//

#ifndef UNTITLED2_USUARIO_H
#define UNTITLED2_USUARIO_H
#include <string>
#include <vector>
#include <ctime>

class Usuario {
public:
    Usuario(const std::string &id, const std::string &user, const std::string &userName, const std::string &description,
            const std::vector<std::string> &friends, int countFriend, const std::string &lastLogin, const std::string &firstLogin);

    // Getters
    std::string getId() const;
    std::string getUser() const;
    std::string getUserName() const;
    std::string getDescription() const;
    std::vector<std::string> getFriends() const;
    std::string getFriendsStr() const;
    int getCountFriend() const;
    std::string getLastLogin() const;
    std::string getFirstLogin() const;

    // Setters
    void setId(const std::string &id);
    void setUser(const std::string &user);
    void setUserName(const std::string &userName);
    void setDescription(const std::string &description);
    void setFriends(const std::vector<std::string> &friends);
    void setCountFriend(int countFriend);
    void setLastLogin(const std::string &lastLogin);
    void setFirstLogin(const std::string &firstLogin);

private:
    std::string id;
    std::string user;
    std::string userName;
    std::string description;
    std::vector<std::string> friends;
    int countFriend;
    std::string lastLogin;
    std::string firstLogin;
};


#endif //UNTITLED2_USUARIO_H
