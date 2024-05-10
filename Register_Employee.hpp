#ifndef REGISTER_EMPLOYEE_HPP
#define REGISTER_EMPLOYEE_HPP

#include "Employee.hpp"
#include "Libreries.hpp"

class Register_Employee
{
private:
    List<Employee *> *list_Employee;
public:
    Register_Employee()
    {
        list_Employee = new List<Employee *>;
    }
    ~Register_Employee(){
        delete list_Employee;
    }

    bool registerEmployee(Employee *employee)
    {
        Employee *employeeAux = employeeExist(employee->getDni());
        if (!employeeAux)
        {
            list_Employee->push_back(employee);
            return true;
        }
        else
        {
            return false;
        }
    }

    void saveEmployeesList(function<void(Employee *)> func)
    {
        list_Employee->reiterate(func);
    }

    Employee *employeeExist(string dni)
    {
        Employee *employee = nullptr;
        list_Employee->reiterate([&](Employee *employeeAux) -> void
                                {
                                    if (employeeAux->getDni() == dni)
                                    {
                                        employee = employeeAux;
                                    }
                                });
        return employee;
    }

    void showEmployees()
    {
        list_Employee->reiterate([&](Employee *employee)
                                { cout << employee->toString() << endl; });
    }

    size_t getEmployeesSize()
    {
        return list_Employee->getSize();
    }

    bool deleteEmployee(string dni)
    {
        Employee *employee = employeeExist(dni);
        if (employee)
        {
            list_Employee->erasebyValue(employee);
            return true;
        }
        else
        {
            return false;
        }
    }

    
};

#endif // REGISTER_EMPLOYEE_HPP
