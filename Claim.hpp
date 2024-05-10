#ifndef CLAIM_HPP
#define CLAIM_HPP
#include "Libreries.hpp"

class Claim
{
private:
    size_t id;
    string issue, claim, status;

public:
    Claim(size_t id = 0, string issue = "", string claim = "", string status = "")
        : id(id), issue(issue), claim(claim), status(status) {}

    string toString() { return "ID: " + to_string(id) + "\nIssue: " + issue + "\nClaim: " + claim + "\nStatus: " + status + "\n"; }

    size_t getId() const { return id; }

    string getIssue() const { return issue; }

    string getClaim() const { return claim; }

    string getStatus() const { return status; }

    bool updateStatus(string status)
    {
        this->status = status;
        return true;
    }
};

#endif