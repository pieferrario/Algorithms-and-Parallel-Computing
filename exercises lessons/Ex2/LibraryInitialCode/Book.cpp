//
// Created by Danilo Ardagna on 2019-09-28.
//

#include "Book.h"


// unsigned get_code() const;
// in the cpp file we always need to specify the book class through Book::
unsigned Book::get_code() const
{
    return code;
};
// The same applies to the other functions
unsigned Book::get_year() const
{
    return year;
}
unsigned Book::get_pages() const
{
    return pages;
}
const std::string & Book::get_author() const
{
    return author;
}
const std::string & Book::get_title() const
{
    return title;
}
bool Book::get_available() const
{
    return available;
}
void Book::set_available(bool av)
{
    available = av;
}

void Book::print() const
{
    std::cout << "Code " << code << std::endl;
    std::cout << "Year " << year << std::endl;
    std::cout << "Pages " << pages << std::endl;
    std::cout << "Author " << author << std::endl;
    std::cout << "Title " << title << std::endl;
    std::cout << "Available " << available << std::endl;
}

