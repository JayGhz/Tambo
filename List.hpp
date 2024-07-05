#pragma once
#include "Node.hpp"
#include <cstdio>
#include <functional>
#include "Libreries.hpp"

using std::function;

template <class T>
class List
{
private:
    Node<T> *ini;
    size_t size = 0;

    // Función para dividir la lista en dos mitades
    Node<T> *getMiddle(Node<T> *ini)
    {
        if (ini == nullptr)
            return ini;

        Node<T> *slow = ini;
        Node<T> *fast = ini->next;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // Función para combinar dos listas ordenadas
    Node<T> *merge(Node<T> *left, Node<T> *right, function<bool(T, T)> comp)
    {
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;

        if (comp(left->data, right->data))
        {
            left->next = merge(left->next, right, comp);
            return left;
        }
        else
        {
            right->next = merge(left, right->next, comp);
            return right;
        }
    }

    // Función recursiva de Merge Sort
    Node<T> *mergeSort(Node<T> *ini, function<bool(T, T)> comp)
    {
        if (ini == nullptr || ini->next == nullptr)
            return ini;

        Node<T> *middle = getMiddle(ini);
        Node<T> *nextToMiddle = middle->next;
        middle->next = nullptr;

        Node<T> *left = mergeSort(ini, comp);
        Node<T> *right = mergeSort(nextToMiddle, comp);

        return merge(left, right, comp);
    }

    // Funcion que recorre la lista en reversa con recursividad
    void reiterate(Node<T> *node, function<void(T)> func)
    {
        if (node != nullptr)
        {
            reiterate(node->next, func);
            func(node->data);
        }
    }

public:
    List() : ini(nullptr), size(0){};
    ~List()
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

        if (size == 0)
        {
            ini = newNode;
        }
        else
        {
            Node<T> *aux = ini;
            for (int i = 1; i < size; i++)
            {
                aux = aux->next;
            }
            Node<T> *neww = new Node<T>(data, aux->next);
            if (neww != nullptr)
            {
                aux->next = neww;
            }
        }
        size++;
    }

    // Eliminar por posicion
    void eraseat(int index)
    {
        if (index < 0 || index >= size)
        {
            std::cerr << "Posicion no encontrada" << std::endl;
        }
        else
        {
            Node<T> *current = ini;
            Node<T> *previous = nullptr;
            for (int i = 0; i < index; i++)
            {
                previous = current;
                current = current->next;
            }
            if (previous == nullptr)
            {
                ini = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            size--;
        }
    }

    // Eliminar por valor
    void erasebyValue(T value)
    {
        Node<T> *current = ini;
        Node<T> *previous = nullptr;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (previous == nullptr)
                {
                    ini = current->next;
                }
                else
                {
                    previous->next = current->next;
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
    void iterate(function<void(T)> func)
    {

        if (ini != nullptr)
        {
            Node<T> *current = ini;
            while (current != nullptr)
            {
                func(current->data);
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
            Node<T> *next = nullptr;
            T temp;
            while (current != nullptr)
            {
                next = current->next;
                while (next != nullptr)
                {
                    if (func(current->data, next->data))
                    {
                        temp = current->data;
                        current->data = next->data;
                        next->data = temp;
                    }
                    next = next->next;
                }
                current = current->next;
            }
        }
    }

    // Ordenar la lista con Merge Sort
    void mergeSort(function<bool(T, T)> comp)
    {
        ini = mergeSort(ini, comp);
    }

    // Recorrer la lista en reversa con recursividad
    void reiterate(function<void(T)> func)
    {
        reiterate(ini, func);
    }

    // Verificar si la lista esta vacia
    bool isEmpty()
    {
        return (ini == nullptr);
    }

    // Obtener el primer elemento
    T back()
    {
        Node<T> *aux = ini;
        for (int i = 1; i < size; i++)
        {
            aux = aux->next;
        }
        return aux->data;
    }

    size_t getSize()
    {
        return size;
    }
};
