#ifndef FILE_HPP
#define FILE_HPP

#include "Manager.hpp"

class File
{
private:
    // Función recursiva para cargar los usuarios
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

            // for (size_t i = 0; i < cartSize; i++)
            // {
            //     string name, description, category;
            //     size_t id = 0;
            //     long stock = 0;
            //     double price = 0;
            //     // cargando datos de productos del carrito
            //     Product *product = new Product(category, id, name, description, price, stock);
            //     user->addProduct(product);
            // }

            manager->registerUser(user);

            _loadUsers(file, n - 1, manager);
        }
    }

    // Función recursiva para cargar los productos
    static void _loadProducts(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string name, description, category, brand;
        size_t id;
        long stock;
        double price;

        if (file >> category >> id >> name >> description >> brand >> price >> stock)
        {
            Product *product = new Product(category, id, name, description, brand, price, stock);
            manager->registerProduct(product);

            _loadProducts(file, n - 1, manager); // recursividad
        }
    }

    // Función recursiva para cargar los empleados
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

    // Función recursiva para cargar las boletas generadas por los usuarios
    static void _loadTikects(fstream &file, long n, Manager *&manager)
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
                string status;
                string date;

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
                    else if (line.substr(0, 6) == "Fecha:") // Buscar la línea "Fecha:"
                    {
                        date = line.substr(7); // Leer la fecha
                    }
                    else // Si no es Total ni ID, es un producto en la boleta
                    {
                        // Extraer el nombre y el precio del producto
                        size_t delimiter = line.find_last_of("-");
                        string productName = line.substr(10, delimiter - 10); // Nombre del producto
                        double price = stod(line.substr(delimiter + 2));      // Precio del producto
                        int quantity = stod(line.substr(delimiter + 2));       // Cantidad del producto

                        // Crear un nuevo producto y agregarlo a la boleta
                        Product *product = new Product(productName, price);
                        user->addProduct(product, quantity);
                    }
                }

                // Crear un nuevo ticket y asignarle el total y el ID
                Ticket *ticket = new Ticket(total, id);
                user->generateTicket();
                manager->registerUser(user);
            }
        }

        _loadTikects(file, n - 1, manager);
    }

    // Función recursiva para cargar los reclamos
    static void _loadClaims(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string email, issue, description, status, answer, date;
        size_t id;

        if (file >> email >> id >> issue >> description >> status >> answer >> date)
        {
            User *user = manager->getUserByEmail(email);
            if (user)
            {
                Claim *claim = new Claim(user, id, issue, description, status, answer, date);
                manager->registerClaim(claim);
            }

            _loadClaims(file, n - 1, manager);
        }
    }

    // Funcion recursiva para cargar los reclamos archivados
    static void _loadArchivedClaims(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        string email, issue, description, status, answer, date;
        size_t id;

        if (file >> email >> id >> issue >> description >> status >> answer >> date)
        {
            User *user = manager->getUserByEmail(email);
            if (user)
            {
                Claim *claim = new Claim(user, id, issue, description, status, answer, date);
                manager->registerArchivedClaim(claim);
            }

            _loadArchivedClaims(file, n - 1, manager);
        }
    }

    // Funcion recursiva para cargar los pedidos
    static void _loadOrders(fstream &file, long n, Manager *&manager)
    {
        if (n <= 0)
            return;

        int id;
        string userName, shippingType, status, date;
        double totalAmount;

        if (file >> id >> userName >> shippingType >> status >> date >> totalAmount)
        {
            Order *order = new Order(id, manager->getUserByName(userName), shippingType, status, date);
            order->setTotalAmount(totalAmount);
            manager->registerOrder(order);

            _loadOrders(file, n - 1, manager);
        }
    }

public:
    // Cargar datos de un archivo según el tipo
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
                _loadTikects(file, n, manager);
            }
            else if (tipo == "claims")
            {
                _loadClaims(file, n, manager);
            }
            else if (tipo == "archivedClaims")
            {
                _loadArchivedClaims(file, n, manager);
            }
            else if (tipo == "orders")
            {
                _loadOrders(file, n, manager);
            }
            file.close();
        }
    }

    // Guardar usuarios en un archivo
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

    // Guardar productos en un archivo
    static void saveProducts(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out);

        if (file.is_open())
        {
            file << manager->cantProducts() << endl;
            manager->getProducts()->saveProductsList([&](Product *p)
                                                     { file << p->getCategory() << " " << p->getId() << " " << p->getName() << " " << p->getDescription() << " "

                                                            << p->getBrand() << " " << p->getPrice() << " " << p->getStock()  << endl; });

            file.close();
        }
    }

    // Guardar empleados en un archivo
    static void saveEmployees(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out);

        if (file.is_open())
        {
            file << manager->cantEmployees() << endl;
            manager->getEmployees()->saveEmployeesTree([&](Employee *e)
                                                       { file << e->getName() << " " << e->getLastName() << " " << e->getDni() << " " << e->getPosition() << endl; });
        file.close();
        }
    }

    // Guardar boletas en un archivo
    static void saveTickets(string text, Manager *manager, User *user)
    {
        ofstream file;
        file.open(text, ios::app); // Abrir el archivo en modo de adjuntar
        if (file.is_open())
        {
            file << "BOLETA" << endl;
            file << "Correo: " << user->getEmail() << endl;

            // Generar la boleta actual
            Ticket *currentTicket = user->getCurrentTicket();
            if (currentTicket)
            {
                file << "ID: " << currentTicket->getId() << endl;
                file << "Total: " << currentTicket->getTotal() << endl;
                file << "Fecha: " << currentTicket->getDate() << endl;
            }

            // Iterar sobre el carrito y guardar los productos
            user->iterateCart([&](Product *product)
                              { file << "Producto: " << product->getName() << " - " << "Precio: " << product->getPrice() << " - " << "Cantidad: " << product->getQuantity() << endl; });

            // Guardar la boleta en el archivo
            file << endl;
            file.close();
        }
    }


    // Guardar reclamos en un archivo
    static void saveClaims(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out);

        if (file.is_open())
        {
            file << manager->cantClaims() << endl;
            manager->getClaims()->saveClaimsQueue([&](Claim *claim)
                                                  { file << claim->getUser()->getEmail() << " " << claim->getId() << " " << claim->getIssue() << " " << claim->getDescription() << " " << claim->getStatus() << " " << claim->getAnswer() << " " << claim->getDate() << endl; });

            file.close();
        }
    }

    // Funcion para archivar los reclamos archivados
    static void archiveClaims(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out); // Abrir el archivo en modo de escritura
        if (file.is_open())
        {
            file << manager->cantArchivedClaims() << endl;
            manager->getClaims()->saveArchivedClaims([&](Claim *claim)
                                                     { file << claim->getUser()->getEmail() << " " << claim->getId() << " " << claim->getIssue() << " " << claim->getDescription() << " " << claim->getStatus() << " " << claim->getAnswer() << " " << claim->getDate() << endl; });
            file.close();
        }
    }

    // Funcion para guardar los pedidos en un archivo
    static void saveOrders(string text, Manager *manager)
    {
        ofstream file;
        file.open(text, ios::out); // Abrir el archivo en modo de escritura
        if (file.is_open())
        {
            file << manager->cantOrders() << endl;
            manager->saveOrdersTable([&](Order *order)
                                                  { file << order->getId() << " " << order->getUserName() << " " << order->getShippingType() << " " << order->getStatus() << " " << order->getDate() << " " << order->getTotalAmount()  << endl; });
            file.close();
        }
    }
};

#endif