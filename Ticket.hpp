#ifndef TICKET_HPP
#define TICKET_HPP

#include "Libreries.hpp"

class Ticket
{
private:
    double total;
    int id;
    string date;

public:
    Ticket(double total, int id, string date = "")
        : total(total), id(id), date(date)
    {
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

    double getTotal() { return total; }
    int getId() { return id; }
    string getDate() { return date; }

    string toString()
    {
        return "ID: " + to_string(id) + "\nTotal: " + to_string(total) + "\nFecha y hora: " + date + "\n";
    }
};

#endif