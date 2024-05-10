#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Libreries.hpp"
#include "Register_Product.hpp"
#include "Register_User.hpp"
#include "Register_Employee.hpp"
#include "Admin.hpp"
class Manager
{
private:
    Register_Product *products;
    Register_User *users;
    Register_Employee* employees;
    Admin* admin;
public:
    Manager(){
        users = new Register_User;
        products = new Register_Product;
        employees = new Register_Employee;
    }
    ~Manager(){
        delete users;
        delete products;
        delete employees;
    }

    bool generateTicketForUser(User* user)
    {
        if (user)
        {
            
            user->generateTicket();
            return true;
        }
        return false;
    }

    User* getUserByEmail(string email)
    {
        return users->getUserByEmail(email);
    }

    User *userExist(string email, string password){
        return users->userExist(email, password);
    }
    bool adminExist(string email, string password) {
        return admin->adminExist(email, password);
    }

    bool registerUser(User *user){
        return users->registerUser(user);
    }

    bool deleteUser(User* user)
    {
        return users->deleteUser(user);
    }

    Product* productExist(string name){
        return products->productExist(name);
    }

    bool registerProduct(Product *product){
        return products->registerProduct(product);
    }

    void showProducts(){
        products->showProducts();
    }

    bool showCart(User* user)
    {
        return user->showCart();
    }

    void showProductsSimple(string category) {
        products->showProductsSimple(category);
    }
  
    bool deleteClaimToUser(User* user)
    {
        return user->deleteClaim();
    }

    bool addProductToCart(User* user, string product){
        Product* productAux = products->productExist(product);
        if(productAux){
            user->addProduct(productAux);
            return true;
        }
        return false;
    }

    bool deleteProductToCart(User* user, string name)
    {
        return users->deleteProductToCart(user, name);
    }
    bool clearCart(User* user) {
        return users->deleteAllProductToCart(user);
    }

    bool deleteProduct(size_t id)
    {
        return products->eraseProduct(id);
    }

    void sortProducts(string critetry){
        products->sortProducts(critetry);
    }

    bool updateStock(size_t id, long stock)
    {
        return products->updateStockProduct(id, stock);
    }

    Employee* employeeExist(string dni)
    {
        return employees->employeeExist(dni);
    }

    bool registerEmployee(Employee* employee)
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

    size_t getSizeEmployees()
    {
        return employees->getEmployeesSize();
    }

    size_t getSizeProductsCart(User* user)
    {
        return user->getCartSize();
    }

    size_t cantUsers(){
        return users->getSize();
    }

    size_t cantProducts() {
        return products->getSize();
    }

    Register_Employee* getEmployees()
    {
        return employees;
    }

    Register_User* getUsers(){
        return users;
    }
    Register_Product* getProducts() {
        return products;
    }
};
 #endif