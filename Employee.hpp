#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include "Libreries.hpp"

class Employee
{
private:
    string name, lastName;
    string dni;
    string position;
    bool available;

public:
    Employee(string name = "", string lastName = "", string dni = "", string position = "")
        : name(name), lastName(lastName), dni(dni), position(position), available(true) {}

    
    // Metodos de clase
    string toString()
    {
        string result = "Nombre: " + name + "\nApellido: " + lastName + "\nDNI: " + dni + "\nCargo: " + position + "\n";
        return result;
    }

    string toStringForUser()
    {
        string result = "Nombre: " + name + "\nApellido: " + lastName + "\nCargo: " + position + "\n";
        return result;
    }

    // Getters
    string getName() const { return name; }
    string getLastName() const { return lastName; }
    string getDni() const { return dni; }
    string getPosition() const { return position; }
    bool isAvailable()  { return available; }

    // Setters
    void setName(string name) { this->name = name; }
    void setLastName(string lastName) { this->lastName = lastName; }
    void setDni(string dni) { this->dni = dni; }
    void setPosition(string position) { this->position = position; }
    void setAvailable(bool available) { this->available = available; }
};

#endif