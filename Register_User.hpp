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

    // Verifica si el usuario existe
    User *userExist(string email, string password)
    {
        User *user{nullptr};
        dlusers->iterate([&](User *userAux)
                         {
                             if (userAux->userExist(email, password))
                             {
                                 user = userAux;
                             } }, 'r');
        return user;
    }

    // Ver usuarios registrados
    void showUsers()
    {
        dlusers->iterate([&](User *user)
                         { cout << user->toString() << endl; }, 'r');
    }

    // Ver usuario actual
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

    // Borrar un producto del carrito
    bool deleteProductToCart(User *user, string name)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            return userAux->deleteProductinCart();
        }
        return false;
    }

    // Borrar todos los productos del carrito
    bool deleteAllProductToCart(User *user)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            return userAux->deleteAllProductsInCart();
        }
        return false;
    }

    // Guardar lista de usuarios
    void saveUsersList(function<void(User *)> func)
    {
        dlusers->iterate(func, 'n'); // obteniendo el nodo inicial por defecto
    }

    // Borrar cuenta de usuario
    bool deleteUser(User *user)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
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

    // Generar una boleta
    bool generateTicket(User *user)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            userAux->generateTicket();
            return true;
        }
        return false;
    }

    // Ordenar el carrito
    void sortCart(User *user, string critery)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            userAux->sortCart(critery);
        }
    }

    // Obtener el tamaño del carrito
    size_t getCartSize(User *user)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            return userAux->getCartSize();
        }
        return 0;
    }

    // Mostrar el carrito
    bool showCart(User *user)
    {
        User *userAux = userExist(user->getEmail(), user->getPassword());
        if (userAux)
        {
            return userAux->showCart();
        }
        return false;
    }

    //Obtener un usuario por email
    User *getUserByEmail(string email)
    {
        User *user{nullptr};
        dlusers->iterate([&](User *userAux)
                         {
                if (userAux->getEmail() == email)
                {
                    user = userAux;
                } }, 'r');
        return user;
    }

    //Obtener un usuario por nombre
    User *getUserByName(string name)
    {
        User *user{nullptr};
        dlusers->iterate([&](User *userAux)
                         {
                if (userAux->getName() == name)
                {
                    user = userAux;
                } }, 'r');
        return user;
    }

    size_t getSize()
    {
        return dlusers->getSize();
    }
};

#endif