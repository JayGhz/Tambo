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

    // Registra un producto
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

    // Guarda la lista de productos
    void saveProductsList(function<void(Product *)> func)
    {
        list_Product->reiterate(func); // obteniendo el nodo inicial por defecto
    }

    // Verifica si el producto existe
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

    // Ver todos los productos en la lista
    void showProducts()
    {
        list_Product->reiterate([&](Product *product)
                                { cout << product->toString() << endl; });
    }

    // Ver todos los productos en la lista de una categoria
    void showProductsSimple(string category)
    {
        list_Product->reiterate([&](Product *product)

                                {if (product->getCategory() == category)
        {
            cout << product->toStringMenu() << endl;
        } });
    }

    // Ordenar productos por seleccion
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

    // Ordenar productos por mergesort
    void mergeSortProducts(string critetry)
    {
        list_Product->mergeSort([&](Product *product1, Product *product2) -> bool
                                {
                                  if (critetry == "lower")
                                  {
                                      return product1->getPrice() > product2->getPrice();
                                  }
                                  else if (critetry == "higher")
                                  {
                                      return product1->getPrice() < product2->getPrice();
                                  }
                                  else if(critetry == "lowerStock")
                                  {
                                      return product1->getStock() > product2->getStock();
                                  }
                                  else if(critetry == "higherStock")
                                  {
                                      return product1->getStock() < product2->getStock();
                                  }
                                  else
                                  {
                                      return false;
                                  } });
    }

    // Ordenar productos por mergesort por categoria
    void mergeSortProductsCategory(string category, string critetry)
    {
        list_Product->mergeSort([&](Product *product1, Product *product2) -> bool
                                {
                                  if (product1->getCategory() == category && product2->getCategory() == category)
                                  {
                                      if (critetry == "lower")
                                      {
                                          return product1->getPrice() > product2->getPrice();
                                      }
                                      else if (critetry == "higher")
                                      {
                                          return product1->getPrice() < product2->getPrice();
                                      }
                                      else if(critetry == "lowerStock")
                                      {
                                          return product1->getStock() > product2->getStock();
                                      }
                                      else if(critetry == "higherStock")
                                      {
                                          return product1->getStock() < product2->getStock();
                                      }
                                      else
                                      {
                                          return false;
                                      }
                                  }
                                  else
                                  {
                                      return false;
                                  } });
    }

    void showProductsCategoryBrand(string category, string brand)
    {
        list_Product->reiterate([&](Product *product)
                                {if (product->getCategory() == category && product->getBrand() == brand)
        {
            cout << product->toStringMenu() << endl;
        } });
    }

    // Buscar producto por ID
    Product *getProductById(size_t id)
    {
        Product *product = nullptr;
        list_Product->reiterate([&](Product *productAux) -> void
                                {
                if (productAux->getId() == id)
                {
                    product = productAux;
                } });
        return product;
    }

    // Eliminar producto por ID
    bool eraseProduct(size_t id)
    {
        bool productFound = false; // Variable para rastrear si se encontro el producto
        list_Product->iterate([&](Product *product)
                              {
                if (product->getId() == id) {
                    // Encontrado el producto con el ID dado, ahora podemos eliminarlo
                    list_Product->erasebyValue(product);
                    productFound = true; // Marcamos que se encontro el producto
                } });

        // Si no se encontro ningun producto con el ID dado, devolvemos false
        if (!productFound)
        {
            return false;
        }

        // Si se encontro el producto, devolvemos true
        return true;
    }

    // Actualizar stock de un producto por ID
    bool updateStockProduct(size_t id, long stock)
    {
        bool productFound = false; // Variable para rastrear si se encontro el producto
        list_Product->iterate([&](Product *product)
                              {
                if (product->getId() == id) {
                    // Encontrado el producto con el ID dado, ahora podemos actualizar el stock
                    product->updateStock(stock);
                    productFound = true; // Marcamos que se encontro el producto
                } });
        return productFound;
    }

    // Actualizar precio de un producto por ID
    bool updatePriceProduct(size_t id, double price)
    {
        bool productFound = false; // Variable para rastrear si se encontro el producto
        list_Product->iterate([&](Product *product)
                              {
                if (product->getId() == id) {
                    // Encontrado el producto con el ID dado, ahora podemos actualizar el precio
                    product->updatePrice(price);
                    productFound = true; // Marcamos que se encontro el producto
                } });
        return productFound;
    }

    size_t getSize()
    {
        return list_Product->getSize();
    }
};

#endif