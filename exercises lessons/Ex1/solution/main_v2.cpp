/* Price deviation evaluation - v2
 * Just like v1, but now we have to store prices from two distinct store locations (center, 'c', and suburbs 's');
 */
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::format;


string const PROMPT = "Input zone ['c'/'s'], price (type anything else to quit): ";
unsigned constexpr MAX_SIZE = 100;

int main ()
{
    // we replicate the same data structures of the v1 solutions for each zone
    double totalC = 0.0;
    double totalS = 0.0;
    unsigned numC = 0;
    unsigned numS = 0;
    double pricesC[MAX_SIZE];
    double pricesS[MAX_SIZE];

    char zone;
    double price;
    // now, at each new input pair, we also have to make sure that the zone makes sense...
    while (cout << PROMPT << endl &&  cin && cin >> zone && (zone == 'c' || zone == 's') && cin >> price && price > 0)
    {
        // the break statement immediately exits from the loop if either array is exhausted
        if (numC >= MAX_SIZE || numS >= MAX_SIZE)
            break;
        // otherwise, we update the corresponding data structures
        if (zone == 'c')
            // read it as: first, we assign price to pricesC[numC], then numC gets incremented by 1,
            // then the result of the price assignment into pricesC[numC] (price itself) is added to totalC;
            // equivalent to the following
            //      pricesC[numC++] = price;
            //      totalC += price;
            totalC += pricesC[numC++] = price;
        else
            totalS += pricesS[numS++] = price;
    }

    // same as in v1, only copy-pasted for each set of data structures
    if (numC != 0)
    {
        double const meanC = totalC / numC;
        cout << endl << setw(20) << "Prices (C)" << setw(40) << "Deviation from the mean" << endl;
        // Remark: setw adds enough whitespaces to pad the width of the stream to the specified value of characters

        for (unsigned i = 0; i < numC; ++i)
        {
            // Your code goes here
            cout << setw(20) << pricesC[i] << setw(40) << pricesC[i] - meanC << endl;
        }
    }

    if (numS != 0)
    {
        double const meanS = totalS / numS;
        cout << endl << setw(20) << "Prices (S)" << setw(40) << "Deviation from the mean" << endl;
        // Remark: setw adds enough whitespaces to pad the width of the stream to the specified value of characters

        for (unsigned i = 0; i < numS; ++i)
        {
            // Your code goes here
            cout << setw(20) << pricesS[i] << setw(40) << pricesS[i] - meanS << endl;
        }
    }
    return 0;
}
