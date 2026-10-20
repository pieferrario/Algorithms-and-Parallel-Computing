#include "Stock_quote.h"

void Stock_quote::add_last_sale_price(float value)
{
    last_prices.push_back(value);
}

void Stock_quote::print() const

// Memo: The print method is inside the class, hence it can access the private members of the class without requiring a getter.
{
    std::cout << "Symbol: " << symbol << std::endl;

    for (size_t idx = 0; idx < last_prices.size(); ++idx)
    {
        std::cout << last_prices[idx] << std::endl;
    }
}
