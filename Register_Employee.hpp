#ifndef REGISTER_EMPLOYEE_HPP
#define REGISTER_EMPLOYEE_HPP

#include "Employee.hpp"
#include "Libreries.hpp"

class Register_Employee
{
private:
    BinarySearchTree<Employee *> *tree_Employee;
public:
    Register_Employee()
    {
        tree_Employee = new BinarySearchTree<Employee *> ([](Employee *employee1, Employee *employee2) -> int
                                                         {
                                                             return employee1->getDni().compare(employee2->getDni());
                                                         });
    }
    ~Register_Employee(){
        delete tree_Employee;
    }

    // Registra un empleado
    bool registerEmployee(Employee *employee)
    {
        Employee *employeeAux = employeeExist(employee->getDni());
        if (!employeeAux)
        {
            tree_Employee->insert(employee);
            return true;
        }
        else
        {
            return false;
        }
    }

    // Guarda el arbol de empleados
    void saveEmployeesTree(function<void(Employee *)> func)
    {
        tree_Employee->reiterate(func);
    }

    // Verifica si el empleado existe
    Employee *employeeExist(string dni)
    {
        Employee *employee = nullptr;
        tree_Employee->reiterate([&](Employee *employeeAux) -> void
                                {
                                    if (employeeAux->getDni() == dni)
                                    {
                                        employee = employeeAux;
                                    }
                                });
        return employee;
    }

    // Ver todos los empleados en el arbol
    void showEmployees()
    {
        tree_Employee->reiterate([&](Employee *employee)
                                { cout << employee->toString() << endl; });
    }

    // Ver un empleado en el arbo
    void showEmployee(string dni)
    {
        Employee *employee = employeeExist(dni);
        if (employee)
        {
            cout << employee->toStringForUser() << endl;
        }
        else
        {
            cout << "Empleado no encontrado" << endl;
        }
    }

    size_t getEmployeesSize()
    {
        return tree_Employee->size();
    }

    // Elimina un empleado por su DNI
    bool deleteEmployee(string dni)
    {
        Employee *employee = employeeExist(dni);
        if (employee)
        {
            tree_Employee->remove(employee);
            return true;
        }
        else
        {
            return false;
        }
    }

    // Elegir un empleado con cargo Atencion_al_cliente y se encuentra disponible
    Employee *assignEmployeeAttention()
    {
        Employee *employee = nullptr;
        tree_Employee->reiterate([&](Employee *employeeAux) -> void
                                {
                                    if (employeeAux->getPosition() == "Atencion_al_cliente" && employeeAux->isAvailable())
                                    {
                                        employee = employeeAux;
                                    }
                                });
        return employee;
    }

    // Elegir un empleado con cargo Repartidor y se encuentra disponible
    Employee *assignEmployeeDelivery()
    {
        Employee *employee = nullptr;
        tree_Employee->reiterate([&](Employee *employeeAux) -> void
                                {
                                    if (employeeAux->getPosition() == "Repartidor" && employeeAux->isAvailable())
                                    {
                                        employee = employeeAux;
                                    }
                                });
        return employee;
    }

    // Cambiar el estado de disponibilidad de un empleado
    void changeAvailability(string dni)
    {
        Employee *employee = employeeExist(dni);
        if (employee)
        {
            employee->setAvailable(!employee->isAvailable());
        }
    }
    
};

#endif // REGISTER_EMPLOYEE_HPP
