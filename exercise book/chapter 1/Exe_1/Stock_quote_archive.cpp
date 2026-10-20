#include "Stock_quote_archive.h"

std::vector<Stock_quote>:: iterator Stock_quote_archive::find (const std::string & symbol)
{
    bool found = false;
    std::vector<Stock_quote>::iterator it = stock_quotes.begin();
    while (it != stock_quotes.end() and !found)
    {
        if (it->get_symbol() == symbol)
            found = true;
        else ++it;
    }
    return it;
}
void Stock_quote_archive::add_stock_quote (const Stock_quote & s)
{
    stock_quotes.push_back(s);
}


void Stock_quote_archive::add_last_sale_price (const std::string & s, float price)
{
    std::vector<Stock_quote>::iterator it = find(s);
    if (it != stock_quotes.end())
        it -> add_last_sale_price (price);
}

void Stock_quote_archive::print() const
{
    // I use a const iterator to loop on stock_quotes. The iterator is const since we just need to cycle on the vector.
    std::vector<Stock_quote>::const_iterator it = stock_quotes.cbegin();
    while (it != stock_quotes.cend())
    {
        it->print();
        ++it;
    }
}