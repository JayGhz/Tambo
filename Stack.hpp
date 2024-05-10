#include <functional>
#include <vector>
#include "Libreries.hpp"
#include "Node.hpp"

using std::function;

template <class T>
class Stack
{
private:
    Node<T> *peek;
    size_t size;

public:
    Stack() : peek(nullptr), size(0){};
    ~Stack()
    {
        Node<T> *current = peek;
        while (peek != nullptr)
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }

        delete peek;
    }

    void push(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (peek == nullptr)
        {
            peek = newNode;
        }
        else
        {
            newNode->next = peek;
            peek = newNode;
        }
        size++;
    }

    void pop()
    {
        if (peek != nullptr)
        {
            Node<T> *current = peek;
            peek = peek->next;
            delete current;
            size--;
        }
    }

    bool iterate(function<void(T)> func)
    {
        Node<T> *current = peek;
        while (current != nullptr)
        {
            func(current->data);
            current = current->next;
        } return true;

        return false;
    }

    T top() 
    {
        if (peek != nullptr)
        {
            return peek->data;
        }
        return T();
    }

    bool empty() { return peek == nullptr; }

    size_t getSize() { return size; }
};
