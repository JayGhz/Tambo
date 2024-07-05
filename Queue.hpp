#include <functional>
#include <vector>
#include "Libreries.hpp"
#include "Node.hpp"

using std::function;

template <class T>
class Queue
{
private:
    Node<T> *peek;
    size_t size;

public:
    Queue() : peek(nullptr), size(0){};
    ~Queue()
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

    void enqueue(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (peek == nullptr)
        {
            peek = newNode;
        }
        else
        {
            Node<T> *current = peek;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    void dequeue()
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
        }
        return true;
    }

    size_t getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    T front()
    {
        return peek->data;
    }
    
    T back()
    {
        Node<T> *current = peek;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        return current->data;
    }
};