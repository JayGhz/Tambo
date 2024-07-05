#ifndef CLAIM_HPP
#define CLAIM_HPP

#include "Libreries.hpp"
#include "User.hpp"

class Claim
{
private:
    size_t id;
    string issue, description, status;
    string date;
    string answer;
    User *user;

public:
    Claim(User *user, int id = 0, string issue = "", string description = "", string status = "", string answer = "...", string date = "")
        : user(user), id(id), issue(issue), description(description), status(status), answer(answer), date(date)
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

    // Getters
    size_t getId() { return id; }

    string getIssue() { return issue; }

    string getDescription() { return description; }

    string getStatus() { return status; }

    string getAnswer() { return answer; }

    string getDate() { return date; }

    User *getUser() { return user; }

    // Setters
    void setStatus(string status) { this->status = status; }

    void setAnswer(string answer) { this->answer = answer; }

    // Métodos
    string toString() { return "Correo del usuario: " + user->getEmail() + "\nID: " + to_string(id) + "\nProblema: " + issue + "\nDescripcion: " + description + "\nEstado: " + status + +"\nFecha y hora: " + date + "\n"; }
    string toStringUser() { return "Id: " + to_string(id) + "\nProblema: " + issue + "\nDescripcion: " + description + "\nEstado: " + status + "\nRespuesta: " + answer + "\nFecha y hora: " + date + "\n"; }
};

#endif // CLAIM_HPP
