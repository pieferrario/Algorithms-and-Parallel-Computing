#include <iostream>
#include<vector>

// The symbol /* opens a comment, while */ closes it.
// Delete the symbols to try the code.


// Exercise 1: This simple program should, first,
// apply a temperature correction to a given measurement,
// and then print a countdown from 5 to 0.
// Identify and correct the errors in this piece of code:

/*
int main() {
	unsigned measurement = 10;
	int correction = -20;

	int corrected = measurement + correction;

	std::cout << "Corrected measurement: " << corrected << '\n';

	for (int i = 5; i >= 0; --i)
		std::cout << i << ' ';

	return 0;
}
*/

/*
// Exercise 2: The program should store the squares
// of numbers from 0 to 9 and print them.
// Identify and correct the errors in this piece of code:
int main() {
	std::vector<int> squares;
	for (int i = 0; i < 10; ++i)
		squares.push_back(i * i);

	std::cout << "The vector contains " << squares.size() << " elements\n";

	for (std::size_t i = 0; i < squares.size(); ++i)
		std::cout << squares[i] << '\n';

	return 0;
}
*/


// Exercise 3: The program should add a new delivery to
// the product’s current stock, store the product in a warehouse,
// and print all products.
// Identify and correct the errors in this piece of code:
struct Product {
	std::string name;
	unsigned long long stock;
};

int main()
{
	Product product{"Keyboard", 4000000000};
	product.stock += 1000000000;

	std::vector<Product> warehouse;
	warehouse.push_back(product);

	for (std::size_t i = 0; i < warehouse.size(); ++i)
		std::cout << warehouse[i].name << ": " << warehouse[i].stock << " units\n";

	return 0;
}

