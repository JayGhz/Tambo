#ifndef REGISTER_USER_HPP
#define REGISTER_USER_HPP

#include "Libreries.hpp"
#include "User.hpp"

class Register_User
{
private:
    DoublyLinkedList<User *> *dlusers;

public:
    Register_User()
    {
        dlusers = new DoublyLinkedList<User *>;
    }
    ~Register_User() { delete dlusers; }

    bool registerUser(User *user)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (!userAux)
        {
            dlusers->push_back(user);
            return true;
        }
        else
        {
            return false;
        }
    }

    User *userExist(string email, string password)
    {
        User *user{nullptr};
        dlusers->iterate([&](User *userAux)
                         {
                             if (userAux->userExist(email, password))
                             {
                                 user = userAux;
                             } 
                    }, 'r');
        return user;
    }

    void showUsers()
    {
        dlusers->iterate([&](User *user)
                         {
                             cout << user->toString() << endl;
                         }, 'r');
    }

    void showUser(string email, string password)
    {
        User *user = userExist(email, password);
        if (user != nullptr)
        {
            cout << user->toString() << endl;
        }
        else
        {
            cout << "Usuario no encontrado" << endl;
        }
    }
    bool deleteProductToCart(User* user, string name)
    {
        User* userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            return userAux->deleteProductinCart();
        }
        return false;
    }

    bool deleteAllProductToCart(User* user)
    {
        User* userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            return userAux->deleteAllProductsInCart();
        }
        return false;
        
    }

    void saveUsersList(function<void(User *)> func)
    {

        dlusers->iterate(func, 'n'); //obteniendo el nodo inicial por defecto

    }

    bool deleteUser(User* user)
    {
        User* userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            dlusers->erase(userAux);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool generateTicket(User* user)
    {
        User* userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            userAux->generateTicket();
            return true;
        }
        return false;
    }
   
    User* getUserByEmail(string email)
    {
        User*user{ nullptr };
        dlusers->iterate([&](User* userAux)
            {
                if (userAux->getEmail() == email)
                {
                    user = userAux;
                }
            }, 'r');
        return user;
    }

    size_t getSize()
    {
        return dlusers->getSize();
    }
};

#endif