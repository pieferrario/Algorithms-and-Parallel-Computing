#include "Book.h"
#include "Library.h"

using std::cout;
using std::endl;

int main()
{
  Book b1(
      1,
      2013,
      1399,
      "S. B. Lippman",
      "C++ primer",
      true
  );

  Book b2(
      2,
      2013,
      1361,
      "B. Stroustrup",
      "The C++ programming language",
      true
  );
    Book b3(
          2,
          2013,
          1361,
          "B. Stroustrup",
          "The C++ programming language",
          false
      );

  b1.print();
  b2.print();


  Library lib;

  lib.add_book(b1);
  lib.add_book(b2);
  lib.add_book(b3);

  lib.rent_book("S. B. Lippman", "C++ primer");
  lib.print();
  cout << "****************+"<< endl;

  lib.rent_book("S. B. Lippman", "C++ primer");
  lib.print();
  cout << "****************+"<< endl;

  lib.return_book(1);
  lib.print();
  cout << "****************+"<< endl;

  lib.return_book(1);
  lib.print();
  cout << "****************+"<< endl;

  cout << "Oldest book" << endl;
  lib.print_oldest();

  return 0;
}