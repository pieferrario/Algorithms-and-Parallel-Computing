//
// Created by Danilo Ardagna on 2019-09-28.
//

#include "Library.h"
void Library::add_book(const Book & book)
{
    // std::vector<Book> books; therefore, we rely on push back to add a book to books.
    books.push_back(book); // in this case book is copied inside books. we are storing books and not references to books.
}

int Library::find(const std::string & author, const std::string & title) const
{
    // we will cycle over books
    for (std::size_t idx = 0; idx < books.size(); ++idx) // use < and not <= or it won't work!!
        // return the first available book with the right author and title
    {
        if (books[idx].get_author() == author and
            books[idx].get_title() == title)
            return idx;
    }
    // otherwise we return -1
    return -1;
}

int Library::find_available_book(const std::string & author, const std::string & title) const
{
    // we will cycle over books
    for (std::size_t idx = 0; idx < books.size(); ++idx) // use < and not <= or it won't work!!
        // return the first available book with the right author and title
    {
        if (books[idx].get_author() == author and
            books[idx].get_title() == title and
            books[idx].get_available())
            return idx;
    }
    // otherwise we return -1
    return -1;
}

// return the book code or -1 if the book is not available
int Library::rent_book(const std::string & author, const std::string & title)
{
    // If we find an available book, then we make it unavailable and return the index.
    int book_index = find_available_book(author, title);
    if (book_index == -1)
        return -1;
    books[book_index].set_available(false);

    return books[book_index].get_code();
}

bool Library::return_book(unsigned code)
{
    // Cycle over all the books until we find the one with the correct code (-> it must be unique)
    for (std::size_t idx = 0; idx < books.size(); ++idx)
    {
        Book & book = books[idx];

        if (book.get_code() == code)
        {
        // If found, we check its availability
            if (book.get_available())
            {
                std::cout << "the book is available" << std::endl;
                return false; // It is available -> we are not returning any book
            }

            else
            {
                book.set_available(true);
                std::cout << "you have successfully returned the book" <<std::endl;
                return true;
            }
        }
    }
    // Else return false.
    std::cout << "book not found" << std::endl;
    return false;
}

void Library::print() const {

    for (std::size_t idx = 0; idx < books.size(); ++idx)
        books[idx].print();
}


void Library::print_oldest() const {

    if (books.empty()) {
        std::cout << "No books in the library!" << std::endl;
        return;
    }

    unsigned idx_oldest = 0;
    unsigned year = books[0].get_year();

    for (std::size_t idx=1; idx<books.size(); ++idx) {
        const Book & book = books[idx];

        if (book.get_year() < year) { // if (books[idx].get_year() < year) {
            idx_oldest = idx;
            year = book.get_year();
        }
    }

    books[idx_oldest].print();
}