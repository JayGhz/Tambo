#ifndef EMAIL_HPP
#define EMAIL_HPP

#pragma once
#include "Libreries.hpp"

class Email
{
private:
    string email;
    string password;

public:
    Email(string email = "", string password = "")
        : email(email), password(password) {}

    // Getters and Setters
    string getEmail() const { return email; }

    string getPassword() const { return password; }

    void setEmail(string email) { this->email = email; }

    void setPassword(string password) { this->password = password; }
};

#endif