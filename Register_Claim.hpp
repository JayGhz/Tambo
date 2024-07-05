#ifndef REGISTER_CLAIM_HPP
#define REGISTER_CLAIM_HPP

#include "Claim.hpp"
#include "Libreries.hpp"

class Register_Claim
{
private:
    Queue<Claim *> *claims;
    List<Claim *> *archivedClaims;

public:
    Register_Claim()
    {
        claims = new Queue<Claim *>;
        archivedClaims = new List<Claim *>;
    }
    ~Register_Claim()
    {
        delete claims;
        delete archivedClaims;
    }

    // Registra un reclamo
    bool registerClaim(Claim *claim)
    {
        claims->enqueue(claim);
        return true;
    }

    // Registra un reclamo archivado
    bool registerArchivedClaim(Claim *claim)
    {
        archivedClaims->push_back(claim);
        return true;
    }

    // Verifica si el reclamo existe
    Claim *claimExist(int id)
    {
        Claim *claim = nullptr;
        claims->iterate([&](Claim *claimAux) -> void
                        {
                            if (claimAux->getId() == id)
                            {
                                claim = claimAux;
                            } });
        return claim;
    }

    // Verifica si el reclamo archivado existe
    Claim *archivedClaimExist(int id)
    {
        Claim *claim = nullptr;
        archivedClaims->iterate([&](Claim *claimAux) -> void
                                {
                                    if (claimAux->getId() == id)
                                    {
                                        claim = claimAux;
                                    } });
        return claim;
    }

    // Guarda los reclamos en la cola
    void saveClaimsQueue(function<void(Claim *)> func)
    {
        claims->iterate(func);
    }

    // Guarda los reclamos archivados en la lista
    void saveArchivedClaims(function<void(Claim *)> func)
    {
        archivedClaims->iterate(func);
    }

    // Ver los reclamos de un usuario en la lista archivada
    void showClaimsUser(User *user)
    {
        archivedClaims->iterate([&](Claim *claim) -> void
                                {
                                    if (claim->getUser() == user)
                                    {
                                        cout << claim->toStringUser() << endl;
                                    } });
    }

    // Ver un reclamo por ID de un usuario
    void showClaimById(int id, User *user)
    {
        archivedClaims->iterate([&](Claim *claim) -> void
                                {
                                    if (claim->getId() == id && claim->getUser() == user)
                                    {
                                        cout << claim->toStringUser() << endl;
                                    } });
    }

    // Ver primer reclamo de un usuario
    void showFirstClaim(User *user)
    {
        bool found = false; // Bandera para indicar si se encontró un reclamo para el usuario

        claims->iterate([&](Claim *claim) -> void
                        {
                            if (claim->getUser() == user && !found)
                            {
                                cout << claim->toStringUser() << endl;
                                found = true; // Cambiar la bandera si se encuentra un reclamo para el usuario
                            } });

        if (!found)
        {
            cout << "No ha presentado ningun reclamo" << endl;
        }
    }

    // Ver todos los reclamos en la cola con estado pendiente
    void showClaimsPending()
    {
        claims->iterate([&](Claim *claim) -> void
                        {
                            if (claim->getStatus() == "Pendiente")
                            {
                                cout << claim->toString() << endl;
                            } });
    }

    // Ver todos los reclamos archivados en la lista
    void showArchivedClaims()
    {
        archivedClaims->iterate([&](Claim *claim) -> void
                                { cout << claim->toString() << endl; });
    }

    // Atender primer reclamo
    void attendFirstClaim()
    {
        if (claims->isEmpty())
        {
            cout << "No hay reclamos pendientes" << endl;
            return;
        }

        Claim *claim = claims->front();
        cout << claim->toString() << endl;
        int id = claim->getId();

        string status;
        string answer;
        cout << "Ingrese el estado que desea asignarle al reclamo (Atendido, Rechazado): ";
        cin >> status;
        cout << "Ingrese la respuesta al reclamo: ";
        cin >> answer;

        // Buscar el reclamo en la lista de reclamos archivados
        Claim *claimArchived = archivedClaimExist(id);
        if (claimArchived)
        {
            claimArchived->setStatus(status);
            claimArchived->setAnswer(answer);
            claims->dequeue();
            return;
        }
    }

    // Obtiene la cantidad de reclamos de un usuario
    size_t getSizeClaimsUser(User *user)
    {
        size_t count = 0;
        claims->iterate([&](Claim *claim) -> void
                        {
                            if (claim->getUser() == user)
                            {
                                count++;
                            } });
        return count;
    }

    // Obtener el primer reclamo de la cola
    Claim *front()
    {
        return claims->front();
    }

    size_t getSize()
    {
        return claims->getSize();
    }

    size_t getSizeArchivedClaims()
    {
        return archivedClaims->getSize();
    }
};

#endif // REGISTER_CLAIM_HPP