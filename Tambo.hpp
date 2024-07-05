#include "File.hpp"
#include "Manager.hpp"

class Tambo
{
private:
    Manager *manager;

    // Funcion para imprimir los archivos ASCII
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

    string toUpper(string str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            str[i] = std::toupper(str[i]);
        }
        return str;
    }

    // Funcion para ocultar la contraseña en la consola
    string hidePassword()
    {
        string password;
        char c;
        while ((c = _getch()) != 13)
        {
            if (c == 8)
            {
                if (password.size() > 0)
                {
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else
            {
                cout << "*";
                password.push_back(c);
            }
        }
        cout << endl;
        return password;
    }

    // Menu principal
    char menu()
    {
        system("cls");
        printASCCI("ASCII_Art/menu.txt");
        char option;
        cout << "\n\n\t\t\t\t\t\t\t\t\t======= BIENVENIDO A TAMBO ======" << endl;
        cout << "\t\t\t\t\t\t\t\t\t1. Iniciar Sesion" << endl;
        cout << "\t\t\t\t\t\t\t\t\t2. Registrarse" << endl;
        cout << "\t\t\t\t\t\t\t\t\t3. Creditos" << endl;
        cout << "\t\t\t\t\t\t\t\t\t4. Salir" << endl;
        cout << "\t\t\t\t\t\t\t\t\tIngrese una opcion: ";

        cin >> option;
        cin.ignore();

        return option;
    }

    // Menu de inicio de sesion
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

    // Decidir el tipo de sesion
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

    // Iniciar sesion como usuario
    void signIn()
    {
        string email;
        system("cls");
        cout << "======= INICIAR SESION ======" << endl;
        cout << "Ingrese su correo: ";
        getline(cin, email);
        cout << "Ingrese su contrasena: ";
        string password = hidePassword();

        User *user = manager->userExist(email, password);
        if (user)
        {
            system("cls");
            cout << "\nBienvenido de vuelta " << user->getName() << "\n\n";
            system("pause");
            char option{'_'};
            do
            {
                option = menuShop();
                switch (option)
                {
                case '1':
                    system("cls");
                    showallProductsbyCategory();
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
                    orders(user);
                    break;
                case '5':
                    system("cls");
                    claims(user);
                    break;
                }

            } while (option != '6');
        }
        else
        {
            cout << "Credenciales incorrectas" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
            ;
        }
    }

    // Iniciar sesion como administrador
    void signInPlus()
    {
        string email;
        system("cls");
        cout << "\n======= INICIAR SESION COMO ADMINISTRADOR ======" << endl;
        cout << "Ingrese su correo: ";
        getline(cin, email);
        cout << "Ingrese su contrasena: ";
        string password = hidePassword();

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
                    manageOrdersandSales();
                    break;
                }
            } while (option != '5');
        }
        else
        {
            cout << "Credenciales incorrectas" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Registrarse
    void signUp()
    {
        string name, lastname, adress, phone, email;
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
        cout << "Ingrese un correo: ";
        cin >> email;
        cout << "Ingrese una contrasena: ";
        string password = hidePassword();

        Email *userEmail = new Email(email, password);
        User *user = new User(name, lastname, adress, phone, userEmail);

        if (manager->registerUser(user))
        {
            cout << "Usuario registrado con exito" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
        else
        {
            cout << "Usuario ya registrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Creditos
    void credits()
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t======= CREDITOS ======" << endl;
        cout << "\t\t\t\t\t\t\t\t\tEl presente trabajo consistio en el desarrollo de una aplicacion" << endl;
        cout << "\t\t\t\t\t\t\t\t\tde consola que simula la tienda de abarrotes Tambo." << endl;
        cout << "\n\t\t\t\t\t\t\t\t\tCurso: Algoritmos y Estructura de Datos" << endl;
        cout << "\t\t\t\t\t\t\t\t\tSeccion: SS32" << endl;
        cout << "\n\t\t\t\t\t\t\t\t\tIntegrantes: " << endl;
        cout << "\t\t\t\t\t\t\t\t\t- Contreras Leon, David Fernando - u20231b514" << endl;
        cout << "\t\t\t\t\t\t\t\t\t- Fajardo Monrroy, Walter Luis - u202221632" << endl;
        cout << "\t\t\t\t\t\t\t\t\t- Quispe Marca, Jhair Armando - u20211c699" << endl;
        cout << "\n\t\t\t\t\t\t\t\t\tPresione enter para volver al menu principal..." << endl;
        cin.get();
    }

    // Menu de usuario
    char menuShop()
    {
        system("cls");
        char option;
        cout << "======= MENU ======" << endl;
        cout << "1. Ver productos disponibles" << endl;
        cout << "2. Carrito de compras" << endl;
        cout << "3. Administrar cuenta" << endl;
        cout << "4. Mis Pedidos" << endl;
        cout << "5. Reclamos" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;
        cin.ignore();
        return option;
    }

    // Ver categorias de productos
    string menuSort()
    {
        string option;
        cout << "======= CATEGORIAS ======" << endl;
        cout << "Cervezas" << endl;
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

        cout << "\nPorfavor seleccione una categoria: ";
        getline(cin, option);
        cout << endl;

        return option;
    }

    void showallProductsbyCategory()
    {
        string category;
        string option;

        option = menuSort();
        if (option == "Salir")
        {
            return;
        }
        else
        {
            category = option;
            int op = 0;
            do
            {
                system("cls");
                cout << "======= CATEGORIA " << toUpper(category) << " ESCOGIDA ======" << endl;
                cout << "1. Ver productos por precio mas alto" << endl;
                cout << "2. Ver productos por precio mas bajo" << endl;
                cout << "3. Ver productos de una marca" << endl;
                cout << "4. Salir" << endl;
                cout << "Ingrese una opcion: ";
                cin >> op;
                cin.ignore(); // Limpiar el buffer de entrada

                switch (op)
                {
                case 1:
                    system("cls");
                    cout << "======= PRODUCTOS DISPONIBLES ======" << endl;
                    manager->mergeSortProductsCategory(category, "higher");
                    manager->showProductsSimple(category);
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    cout << "======= PRODUCTOS DISPONIBLES ======" << endl;
                    manager->mergeSortProductsCategory(category, "lower");
                    manager->showProductsSimple(category);
                    system("pause");
                    break;
                case 3:
                {
                    string brand;
                    cout << "\nIngrese la marca de productos que desee buscar: ";
                    getline(cin, brand);
                    system("cls");
                    cout << "======= PRODUCTOS DISPONIBLES ======" << endl;
                    manager->showProductsCategoryBrand(category, brand);
                    system("pause");
                    break;
                }
                case 4:
                    break;
                default:
                    cout << "Opción no válida. Por favor, ingrese una opción válida." << endl;
                    break;
                }

            } while (op != 4);
        }
    }

    // Carrito de compras
    char menuCart()
    {
        char option;
        system("cls");
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

    // Funciones para el carrito de compras
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

    // Agregar producto al carrito
    void shopProduct(User *user)
    {
        string product;
        int quantity;
        system("cls");
        cout << "\n======= AGREGAR PRODUCTO AL CARRITO ======" << endl;
        cout << "Ingrese el nombre del producto: ";
        getline(cin, product);

        cout << "Ingrese la cantidad deseada: ";
        cin >> quantity;
        cin.ignore();

        if (!manager->addProductToCart(user, product, quantity))
        {
            cout << "Producto no encontrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
        else
        {
            cout << "Producto agregado al carrito" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Eliminar producto del carrito
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
            cout << "\n";
        }
        else
        {
            cout << "Producto eliminado del carrito" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Mostrar carrito de compras
    void showCart(User *user)
    {
        char option;
        do
        {

            system("cls");
            cout << "\n======= CARRITO DE COMPRAS ======" << endl;
            cout << "1. Ordenar carrito por precios mas altos" << endl;
            cout << "2. Ordenar carrito por precios mas bajos" << endl;
            cout << "3. Productos en el carrito con mayor cantidad" << endl;
            cout << "4. Productos en el carrito con menor cantidad" << endl;
            cout << "5. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();
            switch (option)
            {
            case '1':
                system("cls");
                cout << "======= CARRITO DE COMPRAS ======" << endl;
                manager->sortCart(user, "lower");
                manager->showCart(user);
                system("pause");
                break;
            case '2':
                system("cls");
                cout << "======= CARRITO DE COMPRAS ======" << endl;
                manager->sortCart(user, "higher");
                manager->showCart(user);
                system("pause");
                break;
            case '3':
                system("cls");
                cout << "======= CARRITO DE COMPRAS ======" << endl;
                manager->sortCart(user, "lowerQuantity");
                manager->showCart(user);
                system("pause");
                break;
            case '4':
                system("cls");
                cout << "======= CARRITO DE COMPRAS ======" << endl;
                manager->sortCart(user, "higherQuantity");
                manager->showCart(user);
                system("pause");
                break;
            }
        } while (option != '5');
    }

    void confirmPurchase(User *user)
    {
        system("cls");
        char option;
        cout << "======= CONFIRMAR COMPRA ======" << endl;
        manager->showCart(user);
        cout << "Desea realizar la compra de los productos? (S/N) ";
        cin >> option;

        if (option == 'S')
        {
            if (manager->getSizeProductsCart(user) == 0)
            {
                cout << "El carrito está vacío. No se puede realizar la compra." << endl;
                system("pause");
                return;
            }

            string shippingType;
            cout << "Ingrese el tipo de envio (Delivery, Recojo en tienda): ";
            cin.ignore();
            getline(cin, shippingType);

            if (shippingType != "Delivery" && shippingType != "Recojo en tienda")
            {
                cout << "Tipo de envío inválido." << endl;
                system("pause");
                return;
            }

            // Crear el pedido
            Order *order = new Order(manager->generateId(), user, shippingType, "En_proceso");

            Employee *assignedEmployee = nullptr;
            if (shippingType == "Delivery")
            {
                assignedEmployee = manager->chooseEmployeeDelivery();
            }
            else if (shippingType == "Recojo en tienda")
            {
                assignedEmployee = manager->chooseEmployeeAttention();
            }

            if (assignedEmployee == nullptr)
            {
                cout << "No hay empleados disponibles para atender su pedido." << endl;
                delete order; // Liberar memoria del pedido creado
                system("pause");
                return;
            }

            // Generar la boleta para el usuario actual
            manager->generateTicketForUser(user);
            // Registrar el pedido
            manager->registerOrder(order);

            manager->changeAvailability(assignedEmployee->getDni());
            cout << "Su pedido sera atendido pronto. La persona encargada de su pedido es:" << "\n\n";
            manager->showEmployee(assignedEmployee->getDni());
            system("pause");

            // Guardar los cambios en el archivo de tickets y actualizar el stock de los productos
            File::saveTickets("Data/ticket.txt", manager, user);
            File::saveOrders("Data/orders.txt", manager);
            File::saveProducts("Data/products.txt", manager);

            // Limpiar el carrito del usuario
            manager->clearCart(user);
        }
        else if (option == 'N')
        {
            system("cls");
        }
        else
        {
            cout << "Opción inválida. Por favor ingrese 'S' o 'N'." << endl;
            system("pause");
        }
    }

    // Funciones para gestionar la cuenta
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
                cout << "\n";
                break;
            case '2':
                system("cls");
                updateInfoAccount(user);
                cout << "\n";
                system("pause");
                cout << "\n";
                break;
            case '3':
                system("cls");
                deleteAccount(user);
                cout << "\n";
                system("pause");
                cout << "\n";
                break;
            }
        } while (option != '4');
    }

    // Mostrar informacion de la cuenta
    void showInfoAccount(User *user)
    {
        cout << "======= INFORMACION DE LA CUENTA ======" << endl;
        cout << user->toString() << endl;
    }

    // Actualizar informacion de la cuenta
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

    // Eliminar cuenta
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
            cout << "\n";
            exit(0);
        }

        else
        {
            cout << "Contrasena incorrecta" << endl;
        }
    }

    // Funciones para los pedidos
    void orders(User *user)
    {
        char option;
        do
        {
            system("cls");
            cout << "======= PEDIDOS ======" << endl;
            cout << "1. Ver todos mis pedidos" << endl;
            cout << "2. Ver pedidos con mayor monto" << endl;
            cout << "3. ver pedidos mas recientes" << endl;
            cout << "4. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case '1':
                showOrdersUser(user);
                cout << "\n";
                system("pause");
                cout << "\n";
                break;
            case '2':
                cout << "\n";
                system("pause");
                cout << "\n";
                break;
            case '3':
                cout << "\n";
                system("pause");
                cout << "\n";
                break;
            }
        } while (option != '4');
    }

    // Mostrar los pedidos de un usuario
    void showOrdersUser(User *user)
    {
        system("cls");
        cout << "======= MIS PEDIDOS ======" << endl;
        manager->showOrdersUser(user);
    }

    // Funciones para los reclamos
    void claims(User *user)
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= RECLAMOS ======" << endl;
            cout << "1. Presentar un reclamo" << endl;
            cout << "2. Contactar con soporte" << endl;
            cout << "3. Ver mis reclamos" << endl;
            cout << "4. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case '1':
                makeComplaint(user);
                break;
            case '2':
                contactSupport(user);
                break;
            case '3':
                showClaimsUser(user);
                cout << "\n";
                system("pause");
                cout << "\n";
                break;
            }
        } while (option != '4');
    }

    // Presentar un reclamo
    void makeComplaint(User *user)
    {
        int option;
        int id = manager->generateId();
        string issue;
        string description;
        system("cls");
        cout << "======= PRESENTAR UN RECLAMO ======" << endl;
        cout << "1. Falta de un producto(s)" << endl;
        cout << "2. Producto equivocado" << endl;
        cout << "3. Producto en mal estado" << endl;
        cout << "4. Otros" << endl;
        while (true)
        {
            cout << "\nIngrese la opcion correspondiente al problema: ";
            cin >> option;
            if (option >= 1 && option <= 4)
            {
                break;
            }
            else
            {
                cout << "Opcion invalida" << endl;
            }
        }
        switch (option)
        {
        case 1:
            issue = "Falta_de_un_producto(s)";
            break;
        case 2:
            issue = "Producto_equivocado";
            break;
        case 3:
            issue = "Producto_en_mal_estado";
            break;
        case 4:
            issue = "Otros";
            break;
        }
        cout << "\nIngrese una descripcion del problema: ";
        cin.ignore();
        getline(cin, description);
        Claim *claim = new Claim(user, id, issue, description, "Pendiente");
        if (manager->registerClaim(claim) && manager->registerArchivedClaim(claim))
        {
            File::saveClaims("Data/claims.txt", manager);
            File::archiveClaims("Data/archivedClaims.txt", manager);
            system("cls");
            cout << "\nReclamo registrado con exito" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
        else
        {
            cout << "Reclamo ya registrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Contactar al soporte
    void contactSupport(User *user)
    {
        system("cls");
        int id;
        cout << "======= CONTACTAR CON SOPORTE ======" << endl;
        cout << "Ingrese el ID del reclamo correspondiente: ";
        cin >> id;
        Claim *claim = manager->archivedClaimExist(id);
        if (claim)
        {
            system("cls");
            cout << "======= CONTACTAR CON SOPORTE ======" << endl;
            manager->showClaimById(id, user);
            cout << "\n";
            Employee *employee = manager->chooseEmployeeAttention();
            cout << "Nos contacteremos pronto con usted, el empleado encargado de atenderlo es:\n\n";
            manager->showEmployee(employee->getDni());
            system("pause");
        }
        else
        {
            cout << "Reclamo no encontrado" << endl;
            cout << "\n";
            system("pause");
        }
    }

    // Mostrar reclamos de un usuario
    void showClaimsUser(User *user)
    {
        system("cls");
        cout << "======= MIS RECLAMOS ======" << endl;
        manager->showClaimsUser(user);
    }

    // Menu de administrador
    char menuAdmin()
    {
        char option;
        system("cls");
        cout << "======= ADMINISTRAR TIENDA TAMBO ======" << endl;
        cout << "1. Gestionar inventario" << endl;
        cout << "2. Gestionar Colaboradores" << endl;
        cout << "3. Gestionar Reclamos" << endl;
        cout << "4. Gestionar Pedidos/Ventas" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;
        cin.ignore();

        return option;
    }

    // Gestionar inventario
    void manageInventory()
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= GESTIONAR INVENTARIO ======" << endl;
            cout << "1. Agregar un producto nuevo" << endl;
            cout << "2. Eliminar un producto" << endl;
            cout << "3. Ver productos en el inventario" << endl;
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
                showProducts();
                break;
            case '4':
                updateStock();
                break;
            }
        } while (option != '5');
    }

    // Agregar un producto
    void addProductsToList()
    {
        string category, nameP, description, brand;
        size_t id = manager->generateId();
        double price;
        long stock;
        system("cls");
        cout << "\n======= AGREGAR PRODDUCTO A LA LISTA ======" << endl;
        cout << "Ingrese la categoria: ";
        getline(cin, category);
        cout << "Ingrese nombre del producto: ";
        cin >> nameP;
        cout << "Ingrese una descripcion: ";
        cin >> description;
        cout << "Ingrese la marca del producto: ";
        cin >> brand;
        cout << "Ingrese el precio c/u: ";
        cin >> price;
        cout << "Ingrese el stock disponible: ";
        cin >> stock;
        Product *product = new Product(category, id, nameP, description, brand, price, stock, 0);
        if (manager->registerProduct(product))
        {
            File::saveProducts("Data/products.txt", manager);
            cout << "\nProducto registrado con exito" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
        else
        {
            cout << "Producto ya registrado" << endl;
        }
    }

    // Eliminar un producto
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
            cout << "\n";
        }
        else
        {
            cout << "Producto no encontrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Mostrar los productos
    void showProducts()
    {
        char option;
        do
        {
            system("cls");
            cout << "======= PRODUCTOS EN EL INVENTARIO ======" << endl;
            cout << "1. Mostrar todos los productos" << endl;
            cout << "2. Productos mas caros" << endl;
            cout << "3. Productos mas baratos" << endl;
            cout << "4. Productos con mayor stock" << endl;
            cout << "5. Productos con menor stock" << endl;
            cout << "6. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();

            switch (option)
            {
            case '1':
                system("cls");
                manager->showProducts();
                system("pause");
                break;
            case '2':
                system("cls");
                manager->mergeSortProducts("higher");
                manager->showProducts();
                system("pause");
                break;
            case '3':
                system("cls");
                manager->mergeSortProducts("lower");
                manager->showProducts();
                system("pause");
                break;
            case '4':
                system("cls");
                manager->mergeSortProducts("higherStock");
                manager->showProducts();
                system("pause");
                break;
            case '5':
                system("cls");
                manager->mergeSortProducts("lowerStock");
                manager->showProducts();
                system("pause");
                break;
            }
        } while (option != '6');
    }

    // Actualizar stock de un producto
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
            cout << "\n";
        }
        else
        {
            cout << "Producto no encontrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Gestionar colaboradores
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
                cout << "\n";
                break;
            }
        } while (option != '4');
    }

    // Agregar un colaborador
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
            cout << "\n";
        }
        else
        {
            cout << "Colaborador ya registrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Eliminar un colaborador
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
            cout << "\n";
        }
        else
        {
            cout << "Colaborador no encontrado" << endl;
            cout << "\n";
            system("pause");
            cout << "\n";
        }
    }

    // Mostrar todos los colaboradores
    void showCollaborators()
    {
        system("cls");
        cout << "\n======= COLABORADORES ======" << endl;
        manager->showEmployees();
    }

    // Gestionar Reclamos
    void manageComplaints()
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= GESTIONAR RECLAMOS ======" << endl;
            cout << "1. Ver primer reclamo de un usuario" << endl;
            cout << "2. Atender primer reclamo" << endl;
            cout << "3. Ver todos los reclamos pendientes" << endl;
            cout << "4. Ver historial de reclamos" << endl;
            cout << "5. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();
            switch (option)
            {
            case '1':
                showFirstClaimUser();
                break;
            case '2':
                attendFirstClaim();
                break;
            case '3':
                showClaimsPending();
                break;
            case '4':
                showArchivedClaims();
                break;
            }
        } while (option != '5');
    }

    // Ver primer reclamo pendiente de un usuario
    void showFirstClaimUser()
    {
        system("cls");
        string email;
        cout << "\nIngrese el correo del usuario: ";
        cin >> email;
        if (manager->getUserByEmail(email))
        {
            system("cls");
            cout << "======= PRIMER RECLAMO PENDIENTE ======" << endl;
            manager->showFirstClaim(email);
            system("pause");
            cout << "\n";
        }
        else
        {
            cout << "Usuario no encontrado" << endl;
        }
    }

    void attendFirstClaim()
    {
        system("cls");
        cout << "\n======= ATENDER PRIMER RECLAMO ======" << endl;
        Claim *claim = manager->getClaims()->front();
        // Guardar reclamos pendientes antes de atender el primero
        File::saveClaims("Data/claims.txt", manager);
        manager->attendFirstClaim();
        // Actualizar archivo de reclamos después de atender el primero
        File::saveClaims("Data/claims.txt", manager);
        // Archivar reclamo después de atenderlo
        File::archiveClaims("Data/archivedClaims.txt", manager);
        cout << "\nReclamo atendido con exito" << endl;
        cout << "\n";
        system("pause");
        cout << "\n";
    }

    // Ver reclamos pendientes
    void showClaimsPending()
    {
        system("cls");
        cout << "\n======= RECLAMOS PENDIENTES ======" << endl;
        manager->showClaimsPending();
        cout << "\n";
        system("pause");
        cout << "\n";
    }

    // Ver historial de reclamos
    void showArchivedClaims()
    {
        system("cls");
        cout << "\n======= HISTORIAL DE RECLAMOS ======" << endl;
        manager->showArchivedClaims();
        cout << "\n";
        system("pause");
        cout << "\n";
    }

    // Gestionar ventas
    void manageOrdersandSales()
    {
        char option{'_'};
        do
        {
            system("cls");
            cout << "======= GESTIONAR PEDIDOS Y VENTAS ======" << endl;
            cout << "1. Ver todos los pedidos" << endl;
            cout << "2. Buscar un pedido" << endl;
            cout << "3. Atender un pedido" << endl;
            cout << "4. Ganancias Totales" << endl;
            cout << "5. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> option;
            cin.ignore();
            switch (option)
            {
            case '1':
                showOrders();
                break;
            case '2':
                searchOrder();
                break;
            case '3':
                attendOrder();
                break;
            case '4':
                totalEarnings();
                break;
            }
        } while (option != '5');
    }

    // Mostrar todos los pedidos
    void showOrders()
    {
        system("cls");
        cout << "\n======= TODOS LOS PEDIDOS ======" << endl;
        manager->showAllOrders();
        cout << "\n";
        system("pause");
        cout << "\n";
    }

    // Buscar un pedido
    void searchOrder()
    {
        system("cls");
        size_t id;
        cout << "\nIngrese el ID del pedido: ";
        cin >> id;
        system("cls");
        cout << "======= PEDIDO ======" << endl;
        manager->showOrderById(id);
        cout << "\n";
        system("pause");
        cout << "\n";
    }

    // Atender un pedido
    void attendOrder()
    {
        system("cls");
        size_t id;
        string status;
        cout << "Ingrese el ID del pedido: ";
        cin >> id;
        system("cls");
        cout << "\n======= ATENDER PEDIDO ======" << endl;
        if (!manager->showOrderById(id))
        {
            cout << "Pedido con ID " << id << " no encontrado\n";
            system("pause");
        }
        else
        {
            cout << "Ingrese el estado del pedido (En_proceso, En_camino, Entregado): ";
            cin.ignore();
            getline(cin, status);
            manager->updateOrderStatus(id, status);
            File::saveOrders("Data/orders.txt", manager);
        }
    }

    // Ganancias totales del archivo de boletas leer los montos y sumarlos, tambien mostrar el numero de boletas
    void totalEarnings()
    {
        ifstream file("Data/orders.txt");
        if (file.is_open())
        {
            string line;
            double totalSales = 0.0;
            int orders = 0;
            while (getline(file, line))
            {
                if (line.find("Total:") != string::npos)
                {
                    totalSales += stod(line.substr(7));
                    orders++;
                }
            }
            file.close();
            system("cls");
            cout << "\n======= GANANCIAS TOTALES ======" << endl;
            cout << "Ganancia Total: " << totalSales << endl;
            cout << "Numero de Pedidos: " << orders << endl;
            cout << "\n";
            system("pause");
        }
        else
        {
            cout << "No se pudo abrir el archivo ticket.txt" << endl;
        }
    }

public:
    Tambo()
    {
        manager = new Manager;
    }

    ~Tambo() { delete manager; }

    void run()
    {
        char option{'_'};
        do
        {
            File::loadData("Data/users.txt", manager, "users");
            File::loadData("Data/products.txt", manager, "products");
            File::loadData("Data/employees.txt", manager, "employees");
            File::loadData("Data/ticket.txt", manager, "tickets");
            File::loadData("Data/claims.txt", manager, "claims");
            File::loadData("Data/archivedClaims.txt", manager, "archivedClaims");
            File::loadData("Data/orders.txt", manager, "orders");

            option = menu();
            switch (option)
            {
            case '1':
                userType();
                break;
            case '2':
                signUp();
                break;
            case '3':
                credits();
                break;
            }
            cout << "\n\n";
        } while (option != '4');

        File::saveUser("Data/users.txt", manager);
    }
};