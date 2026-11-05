#ifndef SALES_ARCHIVE_H
#define SALES_ARCHIVE_H

#include <vector>

#include "Sales_data.h"

class Sales_archive
{
private:
        std::vector<Sales_data> archive;

        // auxiliary methods
        std::vector <Sales_data>::const_iterator find_isbn (const std::string & isbn) const; // the method is constant since we don't modify the isbn
        std::vector <Sales_data>::iterator find_isbn (const std::string & isbn); // the method is non constant since we will need to use combine, which requires a non const iterator
public:
        // constructor
        Sales_archive() = default;
        Sales_archive(const Sales_data & sales_data_): archive({sales_data_}){}
        Sales_archive(const std::vector<Sales_data> & archive_): archive(archive_) {} // Since archive might be a large data structure, I pass it by reference

        // getter
        const std::vector<Sales_data> & get_archive (void) const {return archive;} // It is a getter thus it is constant.

        // setter
        void add_elem (const Sales_data &sd) {archive.push_back(sd);}

        // required public method
        Sales_archive reduce_by_book (void) const;

        // auxiliary method
        void print_archive() const;

};


#endif /* SALES_ARCHIVE_H */
