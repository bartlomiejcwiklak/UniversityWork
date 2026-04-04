#pragma once
#include <string>
#include <iostream>

class Employee {
public:
    std::string name;
    std::string position;
    int age;

    Employee();
    Employee(std::string name, std::string position, int age);
};

std::ostream& operator<<(std::ostream& os, const Employee& emp);