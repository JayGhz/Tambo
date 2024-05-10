#ifndef FILE_HPP
#define FILE_HPP

#include "Manager.hpp"

class File
{
private:
    static void _loadUsers(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string name, lastname, adress, phone, email, password;

        int cartSize = 0;

        if (file >> name >> lastname >> adress >> phone >> email >> password)
        {
            Email *userEmail = new Email(email, password);
            User *user = new User(name, lastname, adress, phone, userEmail);

            for (size_t i = 0; i < cartSize; i++)
            {
                string name, description, category;
                size_t id = 0;
                long stock = 0;
                double price = 0;
                // cargando datos de productos del carrito
                Product *product = new Product(category, id, name, description, price, stock);
                user->addProduct(product);
            }

            manager->registerUser(user);

            _loadUsers(file, n - 1, manager);
        }
    }

    static void _loadProducts(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string name, description, category;
        size_t id;
        long stock;
        double price;

        if (file >> category >> id >> name >> description >> price >> stock)
        {
            Product *product = new Product(category, id, name, description, price, stock);
            manager->registerProduct(product);

            _loadProducts(file, n - 1, manager); // recursividad
        }
    }

    static void _loadEmployees(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string name, lastname, dni, position;

        if (file >> name >> lastname >> dni >> position)
        {
            Employee *employee = new Employee(name, lastname, dni, position);
            manager->registerEmployee(employee);

            _loadEmployees(file, n - 1, manager);
        }
    }

    static void _loadUsersAndTickets(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string email;

        if (file >> email)
        {
            User *user = manager->getUserByEmail(email);
            if (user)
            {
                string line;
                getline(file, line); // Consumir la línea en blanco después del correo
                getline(file, line); // Leer la línea "BOLETA:"

                double total = 0;
                int id = 0;

                while (getline(file, line) && line != "") // Leer cada línea hasta encontrar una línea en blanco
                {
                    if (line.substr(0, 6) == "Total:") // Buscar la línea "Total:"
                    {
                        total = stod(line.substr(7)); // Leer el total
                    }
                    else if (line.substr(0, 3) == "ID:") // Buscar la línea "ID:"
                    {
                        id = stoi(line.substr(4)); // Leer el ID
                    }
                    else // Si no es Total ni ID, es un producto en la boleta
                    {
                        // Extraer el nombre y el precio del producto
                        size_t delimiter = line.find_last_of("-");
                        string productName = line.substr(10, delimiter - 10); // Nombre del producto
                        double price = stod(line.substr(delimiter + 2));      // Precio del producto

                        // Crear un nuevo producto y agregarlo a la boleta
                        Product *product = new Product(productName, price);
                        user->addProduct(product);
                    }
                }

                // Crear un nuevo ticket y asignarle el total y el ID
                Ticket *ticket = new Ticket(total, id);
                user->generateTicket();

                manager->registerUser(user);
            }
        }

        _loadUsersAndTickets(file, n - 1, manager);
    }

public:
    static void loadData(string text, Manager *manager, string tipo)
    {
        fstream file;
        file.open(text, ios::in);

        if (file.is_open())
        {
            long n;
            file >> n;

            if (tipo == "users")
            {
                _loadUsers(file, n, manager);
            }
            else if (tipo == "products")
            {
                _loadProducts(file, n, manager);
            }
            else if (tipo == "employees")
            {
                _loadEmployees(file, n, manager);
            }
            else if (tipo == "tickets")
            {
                _loadUsersAndTickets(file, n, manager);
            }
            file.close();
        }
    }

    static void saveUser(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out);
        if (file.is_open())
        {

            file << manager->cantUsers() << endl;

            manager->getUsers()->saveUsersList([&](User *user)
                                               {
                                                   file << user->getName() << " " << user->getLastName() << " " << user->getAddress() << " " << user->getPhone() << " " << user->getEmail() << " " << user->getPassword() << endl;

                                                   /*  user->iterateCart([&](Product* product)
                                                     {
                                                         file << product->getName() << " " << product->getDescription() << " " << product->getCategory() << " " << product->getId() << " " << product->getStock() << " " << product->getPrice() << endl;
                                                     });*/ });

            file.close();
        }
    }
    static void saveProducts(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out);

        if (file.is_open())
        {
            file << manager->cantProducts() << endl;
            manager->getProducts()->saveProductsList([&](Product *p)
                                                     { file << p->getCategory() << " " << p->getId() << " " << p->getName() << " " << p->getDescription() << " "

                                                            << p->getPrice() << " " << p->getStock() << endl; });

            file.close();
        }
    }
    static void saveEmployees(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out);

        if (file.is_open())
        {
            file << manager->getSizeEmployees() << endl;
            manager->getEmployees()->saveEmployeesList([&](Employee *e)
                                                       { file << e->getName() << " " << e->getLastName() << " " << e->getDni() << " " << e->getPosition() << endl; });
        }
    }

    static void saveUserAndTickets(string text, Manager *manager, User *user)
    {
        ofstream file;
        file.open(text, ios::app); // Abrir el archivo en modo de adjuntar
        if (file.is_open())
        {
            file << "Correo: " << user->getEmail() << endl;
            file << "BOLETA" << endl;

            // Generar el ticket actual
            Ticket *currentTicket = user->getCurrentTicket();
            if (currentTicket)
            {
                file << "Total: " << currentTicket->getTotal() << endl;
                file << "ID: " << currentTicket->getId() << endl;
            }

            // Iterar sobre el carrito y guardar los productos
            user->iterateCart([&](Product *product)
                              { file << "Producto: " << product->getName() << " - " << "Precio: " << product->getPrice() << endl; });

            // Guardar el ticket en el archivo
            file << endl;
            file.close();
        }
    }
};

#endif