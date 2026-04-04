#include "Employee.h"
#include "Map.h"
#include "Book.h"
#include <iostream>
#include <cassert>

typedef unsigned int ID;
typedef Map<ID, Employee> Database;

using namespace std;

void testEmployeeDatabase();
void addEmployees(Database& database);
void modifyEmployees(Database& database);
void testSpecialCases(Database& database);
void testLibraryDatabase();

int main() {
    testEmployeeDatabase();
    testLibraryDatabase();
    return 0;
};

void testEmployeeDatabase() {
    cout << "--- Employee Database Demo ---" << endl;
    
    Database database;
    addEmployees(database);

    Database newDatabase = database;
    newDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43));
    modifyEmployees(newDatabase);

    cout << "Original database:" << endl << database << endl;
    cout << "Modified database:" << endl << newDatabase << endl;

    database = newDatabase;

    cout << "Database after the assignment:" << endl << database << endl;

    testSpecialCases(database);
}

void addEmployees(Database& database) {
    database.add(761028073, Employee("Jan Kowalski", "salesman", 28));
    database.add(510212881, Employee("Adam Nowak", "storekeeper", 54));
    database.add(730505129, Employee("Anna Zaradna", "secretary", 32));
}

void modifyEmployees(Database& database) {
    Employee* employeePtr;

    employeePtr = database.find(510212881);
    if (employeePtr != nullptr) {
        employeePtr->position = "salesman";
    }
    
    employeePtr = database.find(761028073);
    if (employeePtr != nullptr) {
        employeePtr->age = 29;
    }
}

void testSpecialCases(Database& database) {
    cout << "\n--- Testing Special Cases ---" << endl;

    cout << "Attempting to overwrite key 761028073..." << endl;
    database.add(761028073, Employee("Another Jan", "driver", 40));

    Employee* dupEmp = database.find(761028073);
    assert(dupEmp != nullptr);

    if (dupEmp->name == "Another Jan") {
        cout << "Data has been successfully overwritten." << endl;
    } else {
        cerr << "Error. Data has not been overwritten." << dupEmp->name << endl;
    }
    
    assert(dupEmp->name == "Another Jan"); 
    assert(dupEmp->age == 40);

    cout << "Attempting to find non-existent key 999999999..." << endl;
    Employee* noEmp = database.find(999999999);
    assert(noEmp == nullptr);

    cout << "Non-existent key find test passed." << endl;
}

void testLibraryDatabase() {
    cout << "\n--- Library Database Example ---" << endl;
    
    typedef Map<std::string, Book> Library;
    Library library;

    library.add("Dune", Book("Frank Herbert", "Sci-Fi", 412, "Available"));
    library.add("1984", Book("George Orwell", "Dystopian", 328, "Borrowed"));
    library.add("Moby Dick", Book("Herman Melville", "Fiction", 635, "Available"));
    
    cout << "Initial library:" << endl << library << endl;

    Book* bookPtr = library.find("1984");
    if (bookPtr) {
        bookPtr->status = "Available";
    }

    cout << "--- Library After Update ---" << endl;
    cout << library << endl;
}