#ifndef USER_HPP
#define USER_HPP

#include "Libreries.hpp"
#include "Email.hpp"
#include "Product.hpp"
#include "Ticket.hpp"
#include"Claim.hpp"
class User
{
private:
    string name;
    string lastName;
    string address;
    string phone;

    Email *email;


    List<Ticket*>* tickets;
    Stack<Product *> *cart; //Pila de carritos
    Queue<Claim*>* claims;

public:
    User(string name = "", string lastName = "", string address = "", string phone = "", Email *email = nullptr)
        : name(name), lastName(lastName), address(address), phone(phone), email(email) {
        cart = new Stack<Product*>; claims = new Queue<Claim*>; tickets = new List<Ticket*>;
    }

    ~User()
    {
        delete email;
        delete cart;
        delete tickets;
    }

    // Metodos de clase
    string toString()
    {
        string result = "Nombre: " + name + "\nApellido " + lastName + "\nDireccion: " + address + "\nCelular: " + phone + "\n";
        return result;
    }

    int generateId()
    {
        
        srand(time(nullptr));

        
        return rand() % 9000 + 1000;
    }



    bool userExist(string email, string password)
    {
        return this->email->getEmail() == email && this->email->getPassword() == password;
    }

    void addProduct(Product *product)
    {
        cart->push(product);
    }

    void addClaim(Claim* claim)
    {
        claims->enqueue(claim);
    }

    bool showCart()
    {
        if (cart->getSize() == 0)
        {
            cout << "Carrito Vacio" << endl;
            return false;
        }
        else
        {
            cart->iterate([](Product *product)
                          { cout << product->toString() << endl; });
            return true;
        }
    }



    bool showClaims()
    {
        if (claims->getSize() == 0)
        {
            cout << "No ha presantado ninguna queja" << endl;
            return false;
        }
        else
        {
            claims->iterate([](Claim* claim)
                { cout << claim->toString() << endl; });
            return true;
        }
    }

    void iterateCart(function<void(Product *)> func)
    {
        cart->iterate(func);
    }

    void iterateClaims(function<void(Claim*)> func)
    {
        claims->iterate(func);
    }

    void iterateTickets(function<void(Ticket*)> func)
    {
        tickets->iterate(func);
    }

    bool deleteProductinCart()
    {
        if (cart->getSize() == 0)
        {
            cout << "Carrito Vacio" << endl;
            return false;
        }
        else
        {
            cart->pop();
            return true;
        }
    }

    bool deleteAllProductsInCart()
    {
        while (!cart->empty())
        {
            cart->pop();
        }
        return true;
    }

    bool deleteClaim()
    {
        if (claims->getSize() == 0)
        {
            cout << "No ha presantado ninguna queja" << endl;
            return false;
        }
        else
        {
            claims->dequeue();
            return true;
        }
    }
  
    void generateTicket()
    {
        if (cart->getSize() == 0)
        {
            cout << "El carrito esta vacio. No se puede generar una boleta." << endl;
            return;
        }

        double total = 0.0;
      
        
        cart->iterate([&total](Product* product)
            {  
                total += product->getPrice(); });
      
        int id = generateId(); // Genera un ID aleatorio para la boleta

        Ticket* ticket = new Ticket(total, id);
        tickets->push_back(ticket);
        system("cls");
        cout << "\nCOMPRA REALIZADA CON EXITO!" << endl
            << "ID de la boleta: " << id << endl
            << "Total a pagar: S/. " << total << "\n\n";
            system("pause");
    }

    // Setters y Getters
    string getName() const { return name; }
    string getLastName() const { return lastName; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    string getEmail() const { return email->getEmail(); }
    string getPassword() const { return email->getPassword(); }
    size_t getCartSize() const { return cart->getSize(); }

    //get current ticket
    Ticket* getCurrentTicket() const { return tickets->back(); }

    void setName(string name) { this->name = name; }
    void setLastName(string lastName) { this->lastName = lastName; }
    void setAddress(string address) { this->address = address; }
    void setPhone(string phone) { this->phone = phone; }
};

#endif // USER_HPP