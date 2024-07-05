#include "Libreries.hpp"
#include "Order.hpp"
#include <iostream>
#include <functional>

class HashTable
{
private:
    int capacity;
    int size;
    List<Order *> **table;

    // Función hash
    int hashFunction(int id)
    {
        // Función hash: (id * 17 + 3) XOR (id * 13 + 7) % capacity
        int index = ((id * 17 + 3) ^ (id * 13 + 7)) % capacity; // Validar que el índice esté dentro del rango
        return index;
    }

    // Función para redimensionar la tabla hash
    void rehash()
    {
        int oldCapacity = capacity;
        capacity *= 2;
        List<Order *> **oldTable = table;

        table = new List<Order *> *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = new List<Order *>();
        }

        size = 0;
        for (int i = 0; i < oldCapacity; i++)
        {
            oldTable[i]->iterate([&](Order *order)
                                 { insert(order); });
            delete oldTable[i];
        }
        delete[] oldTable;
    }

public:
    // Constructor
    explicit HashTable(int cap = 10) : capacity(cap), size(0)
    {
        table = new List<Order *> *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            table[i] = new List<Order *>();
        }
    }

    // Destructor
    ~HashTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            delete table[i];
        }
        delete[] table;
    }

    // Insertar un pedido
    void insert(Order *order)
    {
        if ((double)size / capacity >= 0.75)
        {
            rehash();
        }

        int index = hashFunction(order->getId());
        table[index]->push_back(order);
        size++;
    }

    // Buscar un pedido por ID
    Order *search(int id)
    {
        int index = hashFunction(id);
        Order *foundOrder = nullptr;
        table[index]->iterate([&](Order *order)
                              {
                                  if (order->getId() == id)
                                  {
                                      foundOrder = order;
                                  } });
        return foundOrder;
    }

    // Eliminar un pedido por ID
    bool remove(int id)
    {
        int index = hashFunction(id);
        Order *foundOrder = nullptr;
        int foundIndex = -1;
        int currentIndex = 0;
        table[index]->iterate([&](Order *order)
                              {
                                  if (order->getId() == id)
                                  {
                                      foundOrder = order;
                                      foundIndex = currentIndex;
                                  }
                                  currentIndex++; });
        if (foundOrder)
        {
            table[index]->eraseat(foundIndex);
            size--;
            return true;
        }
        return false;
    }

    // Mostrar un pedido por ID (para el administrador)
    bool displayOrderById(int id)
    {
        Order *order = search(id);
        if (order)
        {
            order->displayOrderforAdmin();
            return true;
        }
        else
        {
            return false;
        }
    }

    // Mostrar todos los pedidos (para el administrador)
    void displayAllOrders()
    {
        for (int i = 0; i < capacity; i++)
        {
            table[i]->iterate([](Order *order)
                              { order->displayOrderforAdmin(); });
        }
    }

    // Mostrar todos los pedidos de un usuario (para el usuario)
    void displayOrdersUser(User *user)
    {
        for (int i = 0; i < capacity; i++)
        {
            table[i]->iterate([&](Order *order)
                              {
                                  if (order->getUserName() == user->getName())
                                  {
                                      order->displayOrderforUser();
                                  } });
        }
    }

    // Eliminar todos los pedidos (para el administrador)
    void clearAllOrders()
    {
        for (int i = 0; i < capacity; i++)
        {
            table[i]->~List();
        }
        size = 0;
    }

    // Actualizar el estado de un pedido (para el administrador)
    void updateOrderStatus(int id, string status)
    {
        Order *order = search(id);
        if (order)
        {
            order->setStatus(status);
        }
    }


    // Cantidad de pedidos
    size_t getSize()
    {
        return size;
    }

    // Iterar sobre la tabla hash
    void iterate(std::function<void(Order *)> callback)
    {
        for (int i = 0; i < capacity; i++)
        {
            table[i]->iterate(callback);
        }
    }
};
