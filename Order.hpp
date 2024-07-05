#ifndef ORDER_HPP
#define ORDER_HPP

#include "Libreries.hpp"
#include "User.hpp"

class Order
{
private:
    int id;
    User *user;
    string shippingType;
    string status;
    string date;
    double totalAmount;
    Stack<Product *> products; // Pila de productos

public:
    Order(int id, User *user, string shippingType, string status, string date = "")
        : id(id), user(user), shippingType(shippingType), status(status), date(date), totalAmount(0)
    {
        // Copiar los productos del carrito del usuario a la orden
        user->iterateCart([&](Product *product)
                          {
            Product *productCopy = new Product(*product); // Copiar el producto
            products.push(productCopy);
            totalAmount += productCopy->getPrice() * productCopy->getQuantity(); });

        if (date.empty())
        {
            time_t now = time(0);
            tm *ltm = localtime(&now);

            char buffer[80];
            strftime(buffer, 80, "%d/%m/%Y||%I:%M:%S", ltm);
            this->date = buffer;
        }
        else
        {
            this->date = date;
        }
    }

    ~Order()
    {
        products.iterate([](Product *product)
                         { delete product; });
    }

    // Métodos de clase
    int getId() { return id; }
    string getUserName() { return user->getName(); }
    string getShippingType() { return shippingType; }
    string getStatus() { return status; }
    double getTotalAmount() { return totalAmount; }
    string getDate() { return date; }
    Stack<Product *> getProducts() { return products; }

    void setStatus(string status) { this->status = status; }
    void setTotalAmount(double totalAmount) { this->totalAmount = totalAmount; }

    void displayOrderforUser()
    {
        cout << "ID: " << id << endl;
        cout << "Tipo de envio: " << shippingType << endl;
        cout << "Estado: " << status << endl;
        cout << "Monto total: " << totalAmount << endl;
        cout << "Fecha y hora: " << date << "\n\n";
    }

    void displayOrderforAdmin()
    {
        cout << "ID: " << id << endl;
        cout << "Nombre del usuario: " << user->getName() << endl;
        cout << "Tipo de envio: " << shippingType << endl;
        cout << "Productos: " << endl;

        // Mostrar los productos de la orden
        products.iterate([](Product *product)
                         { cout << "- " << product->getName() << " (Cantidad: " << product->getQuantity() << ", Precio: " << product->getPrice() << ")" << endl; });

        cout << "Estado: " << status << endl;
        cout << "Monto total: " << totalAmount << endl;
        cout << "Fecha y hora: " << date << "\n\n";
    }
};

#endif // ORDER_HPP
