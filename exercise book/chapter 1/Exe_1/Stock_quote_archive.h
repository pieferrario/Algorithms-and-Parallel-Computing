#ifndef STOCKQUOTEARCHIVE_H
#define STOCKQUOTEARCHIVE_H

#include "Stock_quote.h"

class Stock_quote_archive
{
private:
    std::vector<Stock_quote> stock_quotes;
    std::vector<Stock_quote>:: iterator find (const std::string & symbol);
public:
    void add_stock_quote (const Stock_quote & s);

    // we're asked to build an add_last_sale_price function. to do so,
    // we want it to find a stock quote given its symbol and append the last price
    // to the vector of prices relative to that stock symbol.
    // therefore we need an add_last_sale_price method in the class Stock_quote
    // and a find method in the private part of this class.

    void add_last_sale_price (const std::string & s, float price);

    void print() const;
};

#endif // STOCKQUOTEARCHIVE_H