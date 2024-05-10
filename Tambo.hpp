#include "File.hpp"
#include "Manager.hpp"

class Tambo
{
private:
    Manager *manager;

    void printASCCI(string file)
    {
        string line = "";
        ifstream infile;
        infile.open(file);
        if (infile.is_open())
        {
            while (getline(infile, line))
            {
                cout << line << endl;
            }
            infile.close();
        }
        else
        {
            cout << "No se pudo abrir el archivo" << endl;
        }
    }
    char menu()
    {
        system("cls");
        printASCCI("ASCII_Art/menu.txt");
        char option;
        cout << "\n\n\t\t\t\t\t\t\t\t\t======= BIENVENIDO A TAMBO ======" << endl;
        cout << "\t\t\t\t\t\t\t\t\t1. Iniciar Sesion" << endl;
        cout << "\t\t\t\t\t\t\t\t\t2. Registrarse" << endl;
        cout << "\t\t\t\t\t\t\t\t\t3. Salir" << endl;
        cout << "\t\t\t\t\t\t\t\t\tIngrese una opcion: ";

        cin >> option;
        cin.ignore();

        return option;
    }
    char initSession()
    {
        char option;
        system("cls");
        cout << " " << endl;
        cout << "======= ELEGIR SESION ======" << endl;
        cout << "1. Iniciar Sesion como Usuario" << endl;
        cout << "2. Iniciar Sesion como Admin" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opcion: ";

        cin >> option;
        cin.ignore();

        return option;
    }
    char menuAdmin()
    {
        char option;
        system("cls");
        cout << "======= ADMINISTRAR TIENDA TAMBO ======" << endl;
        cout << "1. Gestionar inventario" << endl;
        cout << "2. Gestionar Colaboradores" << endl;
        cout << "3. Atender Reclamos" << endl;
        cout << "4. Gestionar Ventas" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;
        cin.ignore();

        return option;
    }
    char menuShop()
    {
        char option;
        cout << "======= MENU DE COMPRAS ======" << endl;
        cout << "1. Ver productos" << endl;
        cout << "2. Carrito de compras" << endl;
        cout << "3. Administrar cuenta" << endl;
        cout << "4. Realizar un reclamo" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;
        cin.ignore();
        return option;
    }

    char menuCart()
    {
        char option;
        cout << "======= CARRITO DE COMPRAS ======" << endl;
        cout << "1. Agregar Producto al carrito" << endl;
        cout << "2. Eliminar Producto del carrito" << endl;
        cout << "3. Mostrar carrito de compras" << endl;
        cout << "4. Confirmar compra" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;
        cin.ignore();

        return option;
    }
    void cart(User *user)
    {

        char option;
        do
        {
            option = menuCart();
            switch (option)
            {
            case '1':
                system("cls");
                shopProduct(user);

                break;
            case '2':
                system("cls");
                deleteProductToCart(user);

                break;
            case '3':
                system("cls");
                showCart(user);

                break;

            case '4':
                system("cls");
                confirmPurchase(user);

                break;
            }
        } while (option != '5');
    }
    void confirmPurchase(User *user)
    {
        char option;

        cout << "Quiere realizar la compra? (S/N)" << endl;
        cin >> option;
        switch (option)
        {
        case 'S':
            manager->generateTicketForUser(user);                       // Generar el ticket para el usuario actual
            File::saveUserAndTickets("Data/ticket.txt", manager, user); // Pasar el usuario actual como argumento
            manager->clearCart(user);
            break;
        case 'N':
            system("cls");
            break;
        }
    }

    void generateTicket(User *user)
    {
        manager->generateTicketForUser(user);
    }
    string menuSort()
    {
        string option;
        cout << "======= FILTROS DE BUSQUEDA ======" << endl;
        cout << "Elegir categoria" << endl;

        cout << "Cerbezas" << endl;
        cout << "Licores" << endl;
        cout << "Helados" << endl;
        cout << "Snacks" << endl;
        cout << "Comidas" << endl;
        cout << "Lacteos" << endl;
        cout << "Listo para tomar" << endl;
        cout << "Panes y kekes" << endl;
        cout << "Aguas y Gaseosas" << endl;
        cout << "Confiteria" << endl;
        cout << "Cigarros y vapores" << endl;
        cout << "Cuidado personal" << endl;

        cout << "Salir" << endl;
        cout << "Ingrese una opcion: ";

        getline(cin, option);
        cout << endl;

        return option;
    }

    void showallProductsSimple()
    {

        string category;
        string option;

        option = menuSort();
        if (option == "Salir")
        {
        }
        else
        {
            category = option;
            system("cls");
            manager->showProductsSimple(category);
        }
        cout << "\n"; 
        system("pause");
        cout << "\n"; 
    }
    void showallProducts()
    {

        system("cls");

        manager->showProducts();
    }

    void showCart(User *user)
    {
        system("cls");
        cout << "\n======= CARRITO DE COMPRAS ======" << endl;
        if (!manager->showCart(user))
        {
            cout << "No hay productos en el carrito" << endl;
        }

                cout << "\n"; 
        system("pause");
        cout << "\n"; ;
    }

    void shopProduct(User *user)
    {
        string product;
        system("cls");
        cout << "\n======= AGREGAR PRODUCTO AL CARRITO ======" << endl;
        cout << "Ingrese el nombre del producto: ";
        getline(cin, product);

        if (!manager->addProductToCart(user, product))
        {
            cout << "Producto no encontrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Producto agregado al carrito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

    void deleteProductToCart(User *user)
    {
        string product;
        system("cls");
        cout << "\n======= ELIMINAR PRODUCTO DEL CARRITO ======" << endl;
        cout << "Ingrese el nombre del producto: ";
        getline(cin, product);

        if (!manager->deleteProductToCart(user, product))
        {
            cout << "Producto no encontrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Producto eliminado del carrito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

    void showInfoAccount(User *user)
    {
        cout << "======= INFORMACION DE LA CUENTA ======" << endl;
        cout << user->toString() << endl;
    }

    void updateInfoAccount(User *user)
    {
        string name, lastname, adress, phone, email, password;
        system("cls");
        cout << "======= ACTUALIZAR INFORMACION DE LA CUENTA ======" << endl;
        cout << "Ingrese su nombre: ";
        cin >> name;
        cout << "Ingrese su apellido: ";
        cin >> lastname;
        cout << "Ingrese su direccion: ";
        cin >> adress;
        cout << "Ingrese su numero de celular: ";
        cin >> phone;

        user->setName(name);
        user->setLastName(lastname);
        user->setAddress(adress);
        user->setPhone(phone);

        File::saveUser("Data/users.txt", manager);
        cout << "\nInformacion actualizada con exito" << endl;
    }

    void deleteAccount(User *user)
    {
        string password;
        system("cls");
        cout << "======= ELIMINAR CUENTA ======" << endl;
        cout << "Ingrese su contrasena para confirmar: ";
        cin >> password;

        if (user->getPassword() == password)
        {
            manager->deleteUser(user);
            File::saveUser("Data/users.txt", manager);
            cout << "Cuenta eliminada con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
            exit(0);
        }

        else
        {
            cout << "Contrasena incorrecta" << endl;
        }
    }

    void manageAccount(User *user)
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= GESTIONAR CUENTA ======" << endl;
            cout << "1. Ver informacion de la cuenta" << endl;
            cout << "2. Actualizar informacion de la cuenta" << endl;
            cout << "3. Eliminar cuenta" << endl;
            cout << "4. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case '1':
                system("cls");
                showInfoAccount(user);
                        cout << "\n"; 
        system("pause");
        cout << "\n"; ;
                break;
            case '2':
                system("cls");
                updateInfoAccount(user);
                        cout << "\n"; 
        system("pause");
        cout << "\n"; ;
                break;
            case '3':
                system("cls");
                deleteAccount(user);
                        cout << "\n"; 
        system("pause");
        cout << "\n"; ;
                break;
            }
        } while (option != '4');
    }

    void makeComplaint(User *user)
    {
    }

    void userType()
    {
        char option{'_'};
        do
        {
            option = initSession();
            switch (option)
            {
            case '1':
                signIn();
                break;
            case '2':
                signInPlus();
                break;
            }
        } while (option != '3');
    }

    void signIn()
    {
        string email, password;
        system("cls");
        cout << "======= INICIAR SESION ======" << endl;
        cout << "Ingrese su correo: ";
        getline(cin, email);
        cout << "Ingrese su contrasena: ";
        getline(cin, password);

        User *user = manager->userExist(email, password);
        if (user)
        {
            system("cls");
            cout << "\nBienvenido de vuelta " << user->getName() << "\n\n";
            char option{'_'};
            do
            {
                option = menuShop();
                switch (option)
                {
                case '1':
                    system("cls");
                    showallProductsSimple();
                    break;
                case '2':
                    system("cls");
                    cart(user);
                    break;
                case '3':
                    system("cls");
                    manageAccount(user);
                    break;
                case '4':
                    system("cls");
                    makeComplaint(user);
                    break;
                }

            } while (option != '5');
        }
        else
        {
            cout << "Credenciales incorrectas" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }
    void addProductsToList()
    {
        string category, nameP, description;
        size_t id;
        double price;
        long stock;
        system("cls");
        cout << "\n======= AGREGAR PRODDUCTO A LA LISTA ======" << endl;
        cout << "Ingrese la categoria: ";
        getline(cin, category);
        cout << "Ingrese el ID: ";
        cin >> id;
        cout << "Ingrese nombre del producto: ";
        cin >> nameP;
        cout << "Ingrese una descripcion: ";
        cin >> description;
        cout << "Ingrese el precio c/u: ";
        cin >> price;
        cout << "Ingrese el stock disponible: ";
        cin >> stock;
        Product *product = new Product(category, id, nameP, description, price, stock);
        if (manager->registerProduct(product))
        {
            File::saveProducts("Data/products.txt", manager);
            cout << "\nProducto registrado con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Producto ya registrado" << endl;
        }
    }
    void deleteProductFromList()
    {
        size_t id;
        system("cls");
        cout << "\n======= ELIMINAR PRODUCTO ======" << endl;
        cout << "Ingrese el ID del producto: ";
        cin >> id;
        if (manager->deleteProduct(id))
        {
            File::saveProducts("Data/products.txt", manager);
            cout << "Producto eliminado con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Producto no encontrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

    void updateStock()
    {
        size_t id;
        long stock;
        system("cls");
        cout << "\n======= ACTUALIZAR STOCK ======" << endl;
        cout << "Ingrese el ID del producto: ";
        cin >> id;
        cout << "Ingrese el nuevo stock: ";
        cin >> stock;
        if (manager->updateStock(id, stock))
        {
            File::saveProducts("Data/products.txt", manager);
            cout << "Stock actualizado con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Producto no encontrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

    void manageInventory()
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= GESTIONAR INVENTARIO ======" << endl;
            cout << "1. Agregar un producto nuevo" << endl;
            cout << "2. Eliminar un producto" << endl;
            cout << "3. Ver productos" << endl;
            cout << "4. Actualizar stock de un producto" << endl;
            cout << "5. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case '1':
                addProductsToList();
                break;
            case '2':
                deleteProductFromList();
                break;
            case '3':
                showallProducts();
                        cout << "\n"; 
        system("pause");
        cout << "\n"; ;
                break;
            case '4':
                updateStock();
                break;
            }
        } while (option != '5');
    }

    void addCollaborator()
    {
        string name, lastname, dni, position;
        system("cls");
        cout << "\n======= REGISTRAR COLABORADOR ======" << endl;
        cout << "Ingrese el nombre: ";
        cin >> name;
        cout << "Ingrese el apellido: ";
        cin >> lastname;
        cout << "Ingrese el DNI: ";
        cin >> dni;
        cout << "Ingrese el cargo: ";
        cin >> position;

        Employee *employee = new Employee(name, lastname, dni, position);
        if (manager->registerEmployee(employee))
        {
            File::saveEmployees("Data/employees.txt", manager);
            cout << "\nColaborador registrado con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Colaborador ya registrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

    void deleteCollaborator()
    {
        string dni;
        system("cls");
        cout << "\n======= DESPEDIR COLABORADOR ======" << endl;
        cout << "Ingrese el DNI del colaborador: ";
        cin >> dni;
        if (manager->deleteEmployee(dni))
        {
            File::saveEmployees("Data/employees.txt", manager);
            cout << "Colaborador despedido con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Colaborador no encontrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

    void showCollaborators()
    {
        system("cls");
        cout << "\n======= COLABORADORES ======" << endl;
        manager->showEmployees();
    }

    void manageCollaborators()
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= GESTIONAR COLABORADORES ======" << endl;
            cout << "1. Registrar un colaborador nuevo" << endl;
            cout << "2. Despedir colaborador" << endl;
            cout << "3. Mostrar todos los colabadores" << endl;
            cout << "4. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case '1':
                addCollaborator();
                break;
            case '2':
                deleteCollaborator();
                break;
            case '3':
                showCollaborators();
                        cout << "\n"; 
        system("pause");
        cout << "\n"; ;
                break;
            }
        } while (option != '4');
    }

    void manageComplaints() {}

    // show all tickets
    void showTicketsFromFile()
    {
        ifstream file("Data/ticket.txt");
        if (file.is_open())
        {
            string line;
            double totalSales = 0.0; // Variable para almacenar las ganancias totales
            while (getline(file, line))
            {
                if (line.find("Correo:") != string::npos)
                {
                    cout << "Correo del usuario: " << line.substr(8) << endl;
                }
                else if (line.find("ID:") != string::npos)
                {
                    cout << line << endl;
                }
                else if (line.find("Total:") != string::npos)
                {
                    double total = stod(line.substr(7)); // Extraer el monto del ticket
                    cout << "Monto: " << total << endl;
                    totalSales += total; // Sumar al total de ganancias
                }
            }
            file.close();
            cout << "Ganancias totales: " << totalSales << endl;
        }
        else
        {
            cout << "No se pudo abrir el archivo ticket.txt" << endl;
        }
    }

    void manageSales()
    {
        system("cls");
        cout << "\n======= VENTAS ======" << endl;
        showTicketsFromFile();
                cout << "\n"; 
        system("pause");
        cout << "\n"; ;
    }

    void signInPlus()
    {
        string email, password;
        system("cls");
        cout << "\n======= INICIAR SESION COMO ADMINISTRADOR ======" << endl;
        cout << "Ingrese su correo: ";
        getline(cin, email);
        cout << "Ingrese su contrasena: ";
        getline(cin, password);

        bool adminExist = manager->adminExist(email, password);
        if (adminExist)
        {
            system("cls");
            cout << "BIENVENIDO DE VUELTA \n\n";
            char option{'_'};
            do
            {
                option = menuAdmin();
                switch (option)
                {
                case '1':
                    manageInventory();
                    break;
                case '2':
                    manageCollaborators();
                    break;
                case '3':
                    manageComplaints();
                    break;
                case '4':
                    manageSales();
                    break;
                }
            } while (option != '5');
        }
        else
        {
            cout << "Credenciales incorrectas" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }
    void signUp()
    {
        string name, lastname, adress, phone, email, password;
        system("cls");

        cout << "\n======= REGISTRARSE ======" << endl;
        cout << "Ingrese su nombre: ";
        cin >> name;
        cout << "Ingrese su apellido: ";
        cin >> lastname;
        cout << "Ingrese su direccion: ";
        cin >> adress;
        cout << "Ingrese su numero de celular: ";
        cin >> phone;
        cout << "Ingrese su correo: ";
        cin >> email;
        cout << "Ingrese su contrasena: ";
        cin >> password;

        Email *userEmail = new Email(email, password);
        User *user = new User(name, lastname, adress, phone, userEmail);

        if (manager->registerUser(user))
        {
            cout << "Usuario registrado con exito" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
        else
        {
            cout << "Usuario ya registrado" << endl;
                    cout << "\n"; 
        system("pause");
        cout << "\n"; ;
        }
    }

public:
    Tambo()
    {
        manager = new Manager;
    }

    ~Tambo()
    {
        delete manager;
    }

    void run()
    {
        char option{'_'};
        do
        {
            File::loadData("Data/users.txt", manager, "users");
            File::loadData("Data/products.txt", manager, "products");
            File::loadData("Data/employees.txt", manager, "employees");
            File::loadData("Data/ticket.txt", manager, "tickets");

            option = menu();
            switch (option)
            {
            case '1':
                userType();
                break;
            case '2':
                signUp();
                break;
            }
            cout << "\n\n";
        } while (option != '3');
        File::saveUser("Data/users.txt", manager);
    }
};