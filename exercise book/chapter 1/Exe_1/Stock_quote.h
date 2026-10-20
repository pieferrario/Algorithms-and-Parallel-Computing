#ifndef STOCKQUOTE_H
#define STOCKQUOTE_H

#include <vector>
#include <string>
#include <iostream>

class Stock_quote
{
private:
    std::string symbol;
    std::vector<float> last_prices;
public:
    // Constructor
    Stock_quote (const std::string & s): symbol(s) {};

    // Getter
    std::string get_symbol() const
    {
        return symbol;
    }

    // Additional methods
    void add_last_sale_price(float value);
    void print() const;
};

#endif // STOCKQUOTE_H
