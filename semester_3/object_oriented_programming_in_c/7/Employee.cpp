#include "Employee.h"

Employee::Employee() : name(""), position(""), age(0) {}

Employee::Employee(std::string name, std::string position, int age)
    : name(name), position(position), age(age) {}

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    os << "\tName: " << emp.name << "\n" << "\tPosition: " << emp.position << "\n" << "\tAge: " << emp.age;
    return os;
}