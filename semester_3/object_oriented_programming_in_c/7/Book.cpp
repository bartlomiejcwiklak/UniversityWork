#include "Book.h"

Book::Book() : author(""), category(""), pages(0), status("") {}

Book::Book(std::string author, std::string category, int pages, std::string status)
    : author(author), category(category), pages(pages), status(status) {}

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "\tAuthor: " << book.author << "\n" << "\tCategory: " << book.category << "\n" << "\tPages: " << book.pages << "\n" << "\tStatus: " << book.status;
    return os;
}