#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include "Libreries.hpp"

class Product
{
private:
    string category;
    size_t id;
    string name;
    string description;
    string brand;
    int quantity;
    double price;
    long stock;

public:
    Product(string category = "", size_t id = 0, string name = "", string description = "", string brand = "", double price = 0, long stock = 0, int quantity = 0)
        : category(category), id(id), name(name), description(description), price(price), brand(brand), stock(stock), quantity(quantity) {}
    ~Product(){}

    // Para mostrar los productos al super usuario
    string toString()
    {
            ostringstream oss;
            oss << fixed << setprecision(2) << price; // Convertir double a string con 2 decimales
            string priceStr = oss.str();
            return "Categoria: " + category + "\nID: " + to_string(id) + "\nNombre: " + name + "\nDescripcion: " + description + "\nMarca: " + brand + "\nPrecio: " + priceStr + "\nStock: " + to_string(stock) + "\n";  
    }

    // Para mostrar los productos al usuario
    string toStringMenu()
    {       
            ostringstream oss;
            oss << fixed << setprecision(2) << price; // Convertir double a string con 2 decimales
            string priceStr = oss.str();
            return  "Categoria: " + category + "\nNombre: " + name + "\nDescripcion: " + description + + "\nMarca: " + brand + "\nPrecio: " + priceStr + "\n";   
    }

    // Para mostrar los productos en el carrito
    string toStringCart()
    {
            ostringstream oss;
            oss << fixed << setprecision(2) << price; // Convertir double a string con 2 decimales
            string priceStr = oss.str();
            return  "Categoria: " + category + "\nNombre: " + name + "\nDescripcion: " + description + "\nPrecio: " + priceStr + "\nMarca: " + brand + "\nCantidad: " + to_string(quantity) + "\n";   
    }

    // Getters
    string getCategory() const { return category; }
    string getName() const { return name; }
    long getStock() const { return stock; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    size_t getId() const { return id; }
    string getDescription() const { return description; }
    string getBrand() const { return brand; }

    // Setters
    void updateStock(long stock) { this->stock = stock; }
    void updatePrice(double price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }
};

#endif