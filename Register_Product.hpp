#ifndef REGISTER_PRODUCT_HPP
#define REGISTER_PRODUCT_HPP

#include "Product.hpp"
#include "Libreries.hpp"

class Register_Product
{
private:
    List<Product *> *list_Product;

public:
    Register_Product()
    {
        list_Product = new List<Product *>;
    }
    ~Register_Product()
    {
        delete list_Product;

    }

    bool registerProduct(Product *product)
    {
        Product *productAux = productExist(product->getName());
        if (!productAux)
        {
            list_Product->push_back(product);
            return true;
        }
        else
        {
            return false;
        }
    }
    void saveProductsList(function<void(Product*)> func)
    {
        list_Product->reiterate(func); //obteniendo el nodo inicial por defecto

    }

    Product *productExist(string name)
    {
        Product *product = nullptr;
        list_Product->reiterate([&](Product *productAux) -> void
                                {
                             if (productAux->getName() == name)
                             {
                                 product = productAux;
                             } });
        return product;
    }
    void showProducts()
    {
        list_Product->reiterate([&](Product* product)
            {cout << product->toString() << endl; });
    }

    void showProductsSimple(string category)
    {
        list_Product->reiterate([&](Product* product)

       {if (product->getCategory() == category)
        {
            cout << product->toStringSimple() << endl;
        }
            });
    }

    void sortProducts(string critetry)
    {
        list_Product->sort([&](Product *product1, Product *product2) -> bool
                           {
                             if (critetry == "name")
                             {
                                 return product1->getName() < product2->getName();
                             }
                             else if (critetry == "price")
                             {
                                 return product1->getPrice() < product2->getPrice();
                             }
                             else if (critetry == "id")
                             {
                                 return product1->getId() < product2->getId();
                             }
                             else
                             {
                                 return false;
                             } });
    }

    Product* getProductById(size_t id)
    {
        Product* product = nullptr;
        list_Product->reiterate([&](Product* productAux) -> void
            {
                if (productAux->getId() == id)
                {
                    product = productAux;
                } });
        return product;
    }

    bool eraseProduct(size_t id)
    {
        bool productFound = false; // Variable para rastrear si se encontró el producto
        list_Product->iterate([&](Product* product)
            {
                if (product->getId() == id) {
                    // Encontrado el producto con el ID dado, ahora podemos eliminarlo
                    list_Product->erasebyValue(product);
                    productFound = true; // Marcamos que se encontró el producto
                } });

        // Si no se encontró ningún producto con el ID dado, devolvemos false
        if (!productFound)
        {
            return false;
        }

        // Si se encontró el producto, devolvemos true
        return true;
     
    }
    bool updateStockProduct(size_t id, long stock)
    {
        bool productFound = false; // Variable para rastrear si se encontró el producto
        list_Product->iterate([&](Product* product)
            {
                if (product->getId() == id) {
                    // Encontrado el producto con el ID dado, ahora podemos actualizar el stock
                    product->updateStock(stock);
                    productFound = true; // Marcamos que se encontró el producto
                } });
        return productFound; // Agrega una declaración de retorno ya que la función debe devolver un valor bool
    }

    size_t getSize()
    {
        return list_Product->getSize();
    }
};

#endif