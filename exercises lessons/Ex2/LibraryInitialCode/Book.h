//
// Created by Danilo Ardagna on 2019-09-28.
//

#ifndef LIBRARYINITIALCODE_BOOK_H
#define LIBRARYINITIALCODE_BOOK_H

#include <string>
#include <iostream>

class Book
{
private:
    unsigned code;
    unsigned year;
    unsigned pages;
    std::string author;
    std::string title;
    bool available;

public:
    // here we define
    // constructor(s)
    Book (unsigned c, // Instead of using an ambiguous notation, we insert "_" (or call it c) here so that the argument of the function is clear
          unsigned y,
          unsigned p,
          const std::string & a,
          const std::string & t,
          bool av):
    code(c), year(y), pages(p), author(a), title(t), available(av) {}

    // getter(s) -> always const!!
    // if we don't want to access to some attributes, we just cancel the getter function.
    // const at the end of the function declaration means that the function is not going to modify any part of the class;
    // const at the beginning refers to the const type of the object.
    unsigned get_code() const;
    unsigned get_year() const;
    unsigned get_pages() const;
    const std::string & get_author() const;
    const std::string & get_title() const;
    bool get_available() const;
    // setter(s) -> usually void as they are procedures
    void set_available(bool av); // it can't be constant!!

    // print function
    void print() const;



};

#endif //LIBRARYINITIALCODE_BOOK_H
