#ifndef TICKET_HPP
#define TICKET_HPP

#include "Libreries.hpp"


class Ticket
{
private:
    double total;
    int id;
    
public:
    Ticket(double total, int id)
        : total(total), id(id) {}

    double getTotal() { return total; }
    int getId() { return id; }

    string toString()
    {
        string result = "Total: " + to_string(total) + "\nId: " + to_string(id) + "\n";
        return result;
    }
};

#endif