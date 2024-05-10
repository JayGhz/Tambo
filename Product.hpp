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
    double price;
    long stock;

public:
    Product(string category = "", size_t id = 0, string name = "", string description = "", double price = 0, long stock = 0)
        : category(category), id(id), name(name), description(description), price(price), stock(stock) {}
    ~Product(){}
    void updateStock(long stock) { this->stock = stock; }

    string toString()
    {
     
            return "Categoria: " + this->category + "\nID: " + to_string(id) + "\nNombre: " + name + "\nDescripcion: " + description + "\nPrecio: " + to_string(price) + "\nStock: " + to_string(stock) + "\n";
       
    }
    string toStringSimple()
    {
       
            return  "Nombre: " + name + "\nDescripcion: " + description + "\nPrecio: " + to_string(price) + "\nStock: " + to_string(stock) + "\n";
        
    }
    string getCategory() const { return category; }

    string getName() const { return name; }

    long getStock() const { return stock; }

    double getPrice() const { return price; }

    size_t getId() const { return id; }
    
    string getDescription() const { return description; }
};

#endif