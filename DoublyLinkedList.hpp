#include <cstdio>
#include <functional>
#include <iostream>

using std::function;

template <class T>
class DoublyLinkedList
{
private:
    //Nodo de la lista de doble enlace
    template <class Generic>
    class Node
    {
    public:
        Generic data;
        Node<Generic> *next;
        Node<Generic> *prev;

        Node(Generic data = NULL, Node<Generic> *next = nullptr, Node<Generic> *prev = nullptr)
            : data(data), next(next), prev(prev) {}
    };

    Node<T> *ini;
    Node<T> *final;
    size_t size;

    void reiterate(Node<T> *node, function<void(T)> func)
    {
        if (node != nullptr)
        {
            reiterate(node->next, func);
            func(node->data);
        }
    }

public:
    DoublyLinkedList() : ini(nullptr), final(nullptr), size(0){};
    ~DoublyLinkedList()
    {
        while (ini != nullptr)
        {
            Node<T> *temp = ini;
            ini = ini->next;
            delete temp;
        }
    }

    // Agregar al final
    void push_back(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (ini == nullptr)
        {
            ini = newNode;
            final = newNode;
        }
        else
        {
            final->next = newNode;
            newNode->prev = final;
          final = newNode;
        }
        size++;
    }

    // Elimina por posicion
    void eraseat(int index)
    {
        if (index < 0 || index >= size)
        {
            std::cerr << "Posicion no encontrada" << std::endl;
            return;
        }
        Node<T> *current = ini;
        Node<T> *previous = nullptr;
        for (int i = 0; i < index; i++)
        {
            previous = current;
            current = current->next;
        }
        if (previous != nullptr)
        {
            previous->next = current->next;
        }
            else
            {
                ini = current->next;
            }
        if (current->next != nullptr)
        {
            current->next->prev = previous;
        }
        delete current;
        size--;
    }
    
    // Elimina por valor
    void erase(T value)
    {
        Node<T>* current = ini;
        Node<T>* previous = nullptr;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (previous != nullptr)
                {
                    previous->next = current->next;
                }
                else
                {
                    ini = current->next;
                }
                if (current->next != nullptr)
                {
                    current->next->prev = previous;
                }
                delete current;
                size--;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // Recorrer la lista
    void iterate(function<void(T)> fun, char order)
    {
        if (order == 'r')
        {
            reiterate(ini, fun);
        }
        else
        {
            Node<T> *current = ini;
            while (current != nullptr)
            {
                fun(current->data);
                current = current->next;
            }
        }
    }

    // Ordenar la lista por seleccion
    void sort(function<bool(T, T)> func)
    {
        if (ini != nullptr)
        {
            Node<T> *current = ini;
            while (current != nullptr)
            {
                Node<T> *aux = current->next;
                while (aux != nullptr)
                {
                    if (func(current->data, aux->data))
                    {
                        T temp = current->data;
                        current->data = aux->data;
                        aux->data = temp;
                    }
                    aux = aux->next;
                }
                current = current->next;
            }
        }
    }

    // Recorrer la lista en reversa con recursividad
    void reiterate(function<void(T)> fun)
    {
        reiterate(ini, fun);
    }

    // Verificar si la lista esta vacia
    bool isEmpty()
    {
        return ini == nullptr;
    }

    size_t getSize()
    {
        return size;
    }
};
