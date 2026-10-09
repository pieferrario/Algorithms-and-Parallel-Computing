/* Price deviation evaluation - v3
 * Same as v2, but now we clean up the code a bit with functions
 */
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::format;

string const PROMPT = "Input price: ";
unsigned constexpr MAX_SIZE = 100;

unsigned read_prices(double[]);
void evaluate_deviations(double const [], unsigned, string const &);
// Question: would the code have worked identically were the last parameter of evaluate_deviations() just a ref.?

int main ()
{
    double pricesC[MAX_SIZE];
    unsigned numC = read_prices(pricesC);
    evaluate_deviations(pricesC, numC, "c");        // Question: could I pass the zone via string literal
                                                            // if the parameter was simply a reference to string?
    double pricesS[MAX_SIZE];
    unsigned numS = read_prices(pricesS);
    evaluate_deviations(pricesS, numS, "s");
    return 0;
}

// returns an unsigned, i.e., the number of values (successfully) stored
unsigned read_prices (double prices[])
{
    // Question: why can I pass prices? Am I passing a copy of the entire array?
    // Question: could I have declared the prices argument as double * type?
    unsigned num = 0;
    string s;
    while (
        cout << PROMPT << endl
        && cin                  // the stream has successfully stored the previous value
        && num < MAX_SIZE       // the array is not exhausted
        && cin >> prices[num]   // we try to store the value in the next free cell
        && prices[num] > 0      // we check that the provided price makes sense
    )
    {
        ++num;
    }

    if (!cin)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return num;
}

// Question: why can I pass non const-qualified actual parameters without issues?
void evaluate_deviations (double const prices[], unsigned const num, string const & zone)
{
    if (num != 0)
    {
        cout << endl << setw(20) << format("Prices ({})", zone);
        cout << setw(40) << "Deviation from the mean" << endl;
        double mean = 0.0;
        for (size_t i = 0; i < num; ++i) mean += prices[i] / num;
        for (size_t i = 0; i < num; ++i) cout << setw(20) << prices[i] << setw(40) << prices[i] - mean << endl;
    }
}
