#ifndef USER_HPP
#define USER_HPP

#include "Libreries.hpp"
#include "Email.hpp"
#include "Product.hpp"
#include "Ticket.hpp"

class User
{
private:
    string name;
    string lastName;
    string address;
    string phone;

    Email *email;

    List<Ticket *> *tickets;
    Stack<Product *> *cart; // Pila de productos

public:
    User(string name = "", string lastName = "", string address = "", string phone = "", Email *email = nullptr)
        : name(name), lastName(lastName), address(address), phone(phone), email(email)
    {
        cart = new Stack<Product *>;
        tickets = new List<Ticket *>;
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

    void addProduct(Product *product, int quantity)
    {
        product->setQuantity(quantity);
        cart->push(product);
    }

    bool showCart()
    {
        double total = 0;
        if (cart->getSize() == 0)
        {
            cout << "Carrito Vacio" << endl;
            return false;
        }
        else
        {
            cart->iterate([&](Product *product)
                          { cout << product->toStringCart() << endl; 
                          total += product->getPrice() * product->getQuantity(); });
            cout << "Total a pagar: S/. " << total << "\n\n";
            return true;
        }
    }

    void iterateCart(function<void(Product *)> func)
    {
        cart->iterate(func);
    }

    void iterateTickets(function<void(Ticket *)> func)
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

    void sortCart(string critery)
    {
        cout << "Ordenando carrito..." << endl;
        cart->quicksort([&](Product *product1, Product *product2) -> bool
                        {
                        if (critery == "lower")
                        {
                            return product1->getPrice() > product2->getPrice();
                        }
                        else if (critery == "higher")
                        {
                            return product1->getPrice() < product2->getPrice();
                        }
                        else if (critery == "lowerQuantity")
                        {
                            return product1->getQuantity() > product2->getQuantity();
                        }
                        else if (critery == "higherQuantity")
                        {
                            return product1->getQuantity() < product2->getQuantity();
                        }
                        else
                        {
                            return false;
                        } });
    }

    void generateTicket()
    {
        double total = 0;
        cart->iterate([&total](Product *product)
                      { total += product->getPrice() * product->getQuantity(); });

        int id = generateId(); // Genera un ID aleatorio para la boleta
        ostringstream oss;
        oss << fixed << setprecision(2) << total; // Convertir double a string con 2 decimales
        string totalStr = oss.str();

        Ticket *ticket = new Ticket(total, id);
        tickets->push_back(ticket);
        system("cls");
        cout << "====== BOLETA DE COMPRA ======" << endl;
        cout << "\nCompra realiza con exito ...\n"
             << endl
             << "\nID de la boleta: " << id << endl
             << "Total a pagar: S/. " + totalStr << endl
             << "Fecha y hora: " << ticket->getDate() << "\n\n";
    }

    // Setters y Getters
    string getName() { return name; }
    string getLastName() { return lastName; }
    string getAddress() { return address; }
    string getPhone() { return phone; }
    string getEmail() { return email->getEmail(); }
    string getPassword() { return email->getPassword(); }
    size_t getCartSize() { return cart->getSize(); }

    void setName(string name) { this->name = name; }
    void setLastName(string lastName) { this->lastName = lastName; }
    void setAddress(string address) { this->address = address; }
    void setPhone(string phone) { this->phone = phone; }

    // Obtener ultimo ticket
    Ticket *getCurrentTicket() { return tickets->back(); }
};

#endif // USER_HPP