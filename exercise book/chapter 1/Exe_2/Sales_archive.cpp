#include "Sales_archive.h"

std::vector <Sales_data>::const_iterator Sales_archive::find_isbn (const std::string & isbn) const
{
     // we loop on the vector and check if the isbn of the book matches the provided one. if so, we return the iterator of the book we've found.
    std::vector<Sales_data>::const_iterator pos = archive.cbegin();
    while (pos < archive.cend() and pos -> isbn() != isbn)
    {
        ++pos;
    }
    return pos;
}

std::vector <Sales_data>::iterator Sales_archive::find_isbn (const std::string & isbn)
{
    // we loop on the vector and check if the isbn of the book matches the provided one. if so, we return the iterator of the book we've found.
    std::vector<Sales_data>::iterator pos = archive.begin();
    while (pos < archive.end() and pos -> isbn() != isbn)
    {
        ++pos;
    }
    return pos;
}

Sales_archive Sales_archive::reduce_by_book() const
{
    // this methods aggregates all the sales of the same book (identified by the ISBN) in a single entry.
    // the idea is the following:
    // 1. we find all the books in the archive having the same isbn -> we use iterators
    // 2. we use combine on those books
    // 3. we create a new archive in which each entry is a unique book

    // First iteration: we set by default the first element of the auxiliary sales_archive structure using a proper const iterator
    std::vector<Sales_data>::const_iterator const_it = archive.cbegin(); // We define an auxiliary iterator which points to the first element of the archive
    Sales_data sales_data = * const_it; // The element pointed by const_it is the first "sales_data" element.
    Sales_archive new_sales_archive(sales_data); // This constructor makes it necessary to have an overload in the header file that comprises inizialisation by passing a sales data element

    for (const_it = archive.cbegin() + 1; const_it < archive.cend(); ++const_it)
    {
        sales_data = *const_it;
        // we find the book associated to the current sales_data
        std::vector<Sales_data>::iterator current_it = new_sales_archive.find_isbn(sales_data.isbn()); // it either returns a position in the new sales archive (i.e. the book was found -> combine) or the last element -> we add a new entry by push_back
        if (current_it == new_sales_archive.archive.cend())
        {
            new_sales_archive.archive.push_back(sales_data);
        }
        else
        {
            current_it -> combine(sales_data); // to use combine i need a non const iterator, thus i have to overload find_isbn with a non const method.
        }
    }
    return new_sales_archive;
}

void Sales_archive::print_archive() const
{
    for (std::vector<Sales_data>::const_iterator current_it = archive.cbegin(); current_it < archive.cend(); ++current_it)
    {
        (*current_it).print();
    }
}