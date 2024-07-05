#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Libreries.hpp"
#include "Register_Product.hpp"
#include "Register_User.hpp"
#include "Register_Employee.hpp"
#include "Register_Claim.hpp"
#include "HashTable.hpp"
#include "Store.hpp"
#include "Admin.hpp"
class Manager
{
private:
    Register_Product *products;
    Register_User *users;
    Register_Employee *employees;
    Register_Claim *claims;
    HashTable *orders;
    Admin *admin;

public:
    Manager()
    {
        users = new Register_User;
        products = new Register_Product;
        employees = new Register_Employee;
        claims = new Register_Claim;
        orders = new HashTable;
    }
    ~Manager()
    {
        delete users;
        delete products;
        delete employees;
        delete claims;
        delete orders;
    }

    // FUNCIONES DE USUARIO
    User *getUserByEmail(string email)
    {
        return users->getUserByEmail(email);
    }

    User* getUserByName(string name){
        return users->getUserByName(name);
    }

    User *userExist(string email, string password)
    {
        return users->userExist(email, password);
    }

    bool registerUser(User *user)
    {
        return users->registerUser(user);
    }

    bool deleteUser(User *user)
    {
        return users->deleteUser(user);
    }

    void showProductsSimple(string category)
    {
        products->showProductsSimple(category);
    }

    bool addProductToCart(User *user, string product, int quantity)
    {
        Product *productAux = products->productExist(product);
        if (productAux)
        {
            user->addProduct(productAux, quantity);
            return true;
        }
        return false;
    }

    bool deleteProductToCart(User *user, string name)
    {
        return users->deleteProductToCart(user, name);
    }

    bool clearCart(User *user)
    {
        return users->deleteAllProductToCart(user);
    }

    bool showCart(User *user)
    {
        return users->showCart(user);
    }

    void sortCart(User *user, string critery)
    {
        users->sortCart(user, critery);
    }

    size_t getSizeProductsCart(User *user)
    {
        return users->getCartSize(user);
    }

    bool generateTicketForUser(User *user)
    {
        if (user)
        {

            user->generateTicket();
            // actualizar stock
            user->iterateCart([&](Product *product)
                              {
                                  Product *productAux = products->productExist(product->getName());
                                  if (productAux)
                                  {
                                      productAux->updateStock(productAux->getStock() - product->getQuantity());
                                  }
                              });
            return true;
        }


        return false;
    }

    Claim *claimExist(int id)
    {
        return claims->claimExist(id);
    }

    Claim *archivedClaimExist(int id)
    {
        return claims->archivedClaimExist(id);
    }

    bool registerClaim(Claim *claim)
    {
        return claims->registerClaim(claim);
    }

    bool registerArchivedClaim(Claim *claim)
    {
        return claims->registerArchivedClaim(claim);
    }

    void showClaimsPending()
    {
        claims->showClaimsPending();
    }

    void showArchivedClaims()
    {
        claims->showArchivedClaims();
    }

    void attendFirstClaim()
    {
        claims->attendFirstClaim();

    }

    void showFirstClaim(string email)
    {
        User *user = getUserByEmail(email);
        if (user)
        {
            claims->showFirstClaim(user);
        }
    }

    void showClaimsUser(User *user)
    {
        claims->showClaimsUser(user);
    }

    void showClaimById(int id, User *user)
    {
        claims->showClaimById(id, user);
    }

    size_t getSizeClaimsUser(User *user)
    {
        return claims->getSizeClaimsUser(user);
    }

    int generateId()
    {
        srand(time(nullptr));
        return rand() % 9000 + 1000;
    }

    void registerOrder(Order *order)
    {
        orders->insert(order);
    }

    bool removeOrder(int id)
    {
        return orders->remove(id);
    }

    // mostrar ordenes de un usuario
    void showOrdersUser(User *user)
    {
        orders->displayOrdersUser(user);
    }

    // cantidad de ordenes
    size_t cantOrders()
    {
        return orders->getSize();
    }

    // obtener ordenes
    HashTable *getOrders()
    {
        return orders;
    }

    // guardar ordenes en la tabla hash
    void saveOrdersTable(function<void(Order *)> func)
    {
        orders->iterate(func);
    }

    // actualizar el estado de una orden
    void updateOrderStatus(int id, string status)
    {
        orders->updateOrderStatus(id, status);
    }

    // mostrar orden por id
    bool showOrderById(int id){
        return orders->displayOrderById(id);
    }

    // mostrar todas las ordenes
    void showAllOrders(){
        orders->displayAllOrders();
    }

    // FUNCIONES DE ADMINISTRADOR
    bool adminExist(string email, string password)
    {
        return admin->adminExist(email, password);
    }

    Product *productExist(string name)
    {
        return products->productExist(name);
    }

    bool registerProduct(Product *product)
    {
        return products->registerProduct(product);
    }

    void showProducts()
    {
        products->showProducts();
    }

    bool deleteProduct(size_t id)
    {
        return products->eraseProduct(id);
    }

    void mergeSortProducts(string critetry)
    {
        products->mergeSortProducts(critetry);
    }

    void mergeSortProductsCategory(string category, string critetry)
    {
        products->mergeSortProductsCategory(category, critetry);
    }

    void showProductsCategoryBrand(string category, string brand)
    {
        products->showProductsCategoryBrand(category, brand);
    }

    bool updateStock(size_t id, long stock)
    {
        return products->updateStockProduct(id, stock);
    }

    bool updatePrice(size_t id, double price)
    {
        return products->updatePriceProduct(id, price);
    }

    Employee *employeeExist(string dni)
    {
        return employees->employeeExist(dni);
    }

    bool registerEmployee(Employee *employee)
    {
        return employees->registerEmployee(employee);
    }

    void showEmployees()
    {
        employees->showEmployees();
    }

    bool deleteEmployee(string dni)
    {
        return employees->deleteEmployee(dni);
    }

    void chooseStore(){}

    Employee *chooseEmployeeAttention()
    {
        return employees->assignEmployeeAttention();
    }

    Employee *chooseEmployeeDelivery()
    {
        return employees->assignEmployeeDelivery();
    }

    void changeAvailability(string dni)
    {
        employees->changeAvailability(dni);
    }

    void showEmployee(string dni)
    {
        employees->showEmployee(dni);
    }

    size_t cantUsers()
    {
        return users->getSize();
    }

    size_t cantProducts()
    {
        return products->getSize();
    }

    size_t cantEmployees()
    {
        return employees->getEmployeesSize();
    }

    size_t cantClaims()
    {
        return claims->getSize();
    }

    size_t cantArchivedClaims()
    {
        return claims->getSizeArchivedClaims();
    }

    Register_Employee *getEmployees()
    {
        return employees;
    }

    Register_User *getUsers()
    {
        return users;
    }

    Register_Product *getProducts()
    {
        return products;
    }

    Register_Claim *getClaims()
    {
        return claims;
    }
};
#endif