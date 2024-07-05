#include <functional>

using std::function;

template <class T>
class Stack
{
private:
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

    Node<T> *peek;
    size_t size;

    // Intercambiar dos elementos en la pila
    void swap(Node<T> *a, Node<T> *b)
    {
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    // Seleccionar el pivote
    Node<T> *partition(Node<T> *low, Node<T> *high, function<bool(T, T)> comp)
    {
        T pivot = high->data;
        Node<T> *i = low->prev;

        for (Node<T> *j = low; j != high; j = j->next)
        {
            if (comp(j->data, pivot))
            {
                i = (i == nullptr) ? low : i->next;
                swap(i, j);
            }
        }
        i = (i == nullptr) ? low : i->next;
        swap(i, high);
        return i;
    }

    // Quick Sort
    void quickSort(Node<T> *low, Node<T> *high, function<bool(T, T)> comp)
    {
        if (high != nullptr && low != high && low != high->next)
        {
            Node<T> *pivot = partition(low, high, comp);
            quickSort(low, pivot->prev, comp);
            quickSort(pivot->next, high, comp);
        }
    }

public:
    Stack() : peek(nullptr), size(0) {}
    ~Stack()
    {
        Node<T> *current = peek;
        while (current != nullptr)
        {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
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
            peek->prev = newNode;
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
            if (peek != nullptr)
            {
                peek->prev = nullptr;
            }
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

    // Ordenar la pila con Quick Sort
    void quicksort(function<bool(T, T)> comp)
    {
        if (peek == nullptr || peek->next == nullptr)
            return;
        Node<T> *lastnode = peek;
        while (lastnode->next != nullptr)
        {
            lastnode = lastnode->next;
        }
        quickSort(peek, lastnode, comp);
    }
};