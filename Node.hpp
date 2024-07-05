// Nodo para la lista simple enlazada
#pragma once
#include "Libreries.hpp"

template <class T>
class Node
{
public:
    T data;
    Node<T> *next;

    Node(T data = NULL, Node* next = nullptr)
    : data(data), next(next){}

};