#pragma once
#include <string>
#include <iostream>

class Book {
public:
    std::string author;
    std::string category;
    int pages;
    std::string status;

    Book();
    Book(std::string author, std::string category, int pages, std::string status);
};

std::ostream& operator<<(std::ostream& os, const Book& book);