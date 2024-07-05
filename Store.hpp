#ifndef STORE_HPP
#define STORE_HPP
#include "Libreries.hpp"

class Store
{
private:
    string name;
    string district;
    string address;

public:
    Store(string name, string district, string address)
        : name(name), district(district), address(address) {}

    string getName() { return name; }
    string getDistrict() { return district; }
    string getAddress() { return address; }

    string toString()
    {
        return "Nombre: " + name + "\nDistrito: " + district + "\nDireccion: " + address + "\n";
    }
};

#endif