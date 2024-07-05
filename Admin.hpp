#pragma once
#include "Libreries.hpp"
using namespace std;

class Admin {
private:
    string email;
    string password;

public:
    Admin(string email = "", string password = ""){}
        
   bool adminExist(string email, string password) {
       return this->getEmail() == email && this->getPassword() == password;
   }
    
    // Getters instanciados de manera estatica
    string getEmail() const {
        string email = "AAA";
        return email;
    }

    string getPassword() const {
        string password = "AAA";
        return password;
    }
};