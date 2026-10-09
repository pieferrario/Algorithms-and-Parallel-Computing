/* Price deviation evaluation - v2b
 * Almost identical to v2, but now the center/suburbs arrays are one after the other;
 * the only thing we have to pay attention to is the fact that once cin is in an invalid state,
 * unless we do something about it, it stays in that state, which would prevent us from filling in the second array...
 */
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::format;


string const PROMPT = "Input prices (type anything else to quit): ";
unsigned constexpr MAX_SIZE = 100;

void read_prices ()     // same as v1, just packed into a function for convenience
{
    // data structures; notice that these are local variables,
    // they will be destroyed when read_prices() goes out of scope!
    double total = 0.0;
    unsigned num = 0;
    double prices[MAX_SIZE];

    while (cout << PROMPT << endl && cin && num < MAX_SIZE && cin >> prices[num] && prices[num] > 0)
    {
        total += prices[num++];
    }

    if (num != 0)
    {
        double const mean = total / num;
        cout << endl << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        // Remark: setw adds enough whitespaces to pad the width of the stream to the specified value of characters

        for (unsigned i = 0; i < num; ++i)
        {
            // Your code goes here
            cout << setw(20) << prices[i] << setw(40) << prices[i] - mean << endl;
        }
    }
}

int main ()
{
    read_prices();

    // Question: can we omit the next two lines? try it!
    cin.clear();                        // clears the cin state
    cin.ignore(1000, '\n');       // even if the state is cleared, the "bad" content that we previously typed
                                        // is still in the cin buffer
    read_prices();
    return 0;
}
// Question: is this enough? What about scalability?