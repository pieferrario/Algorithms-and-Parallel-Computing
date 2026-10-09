/* Price deviation evaluation - v1
 * We read input prices from the input stream, as provided by the user, and store them into a C-style array;
 * our task is to make sure that what is provided can be interpreted as a valid price.
 * After filling-in the data structure, we are tasked to print out a table with the recorded prices,
 * and their deviation from the mean
 */
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::format;


unsigned constexpr MAX_SIZE = 100;      // Question: is constexpr absolutely necessary?
                                        // yes, from C++23 every size of an array must be a constexpr,
                                        // not just a const variable!
// const applies to the thing left of it. If there is nothing on the left then it applies to the thing right of it.
string const PROMPT = "Input prices (type anything else to quit): ";

int main ()
{
    // defining the data structures that we will use
    double total = 0.0;
    unsigned num = 0;
    double prices[MAX_SIZE];                // TODO: try out the debugger to see what's in the
                                            // (uninitialized) prices array!

    // we write the PROMPT to the output stream, check whether we can proceed (cin stream in valid state,
    // prices array not yet exhausted...) and update; notice that we might store in prices[num] even an invalid
    // (i.e., negative) price, but it does not matter since we would not update num...
    while (cout << PROMPT << endl && cin && num < MAX_SIZE && cin >> prices[num] && prices[num] > 0)
    {
        // Question: are we accessing the right array cell? remember there is a difference between num++ and ++num
        total += prices[num++];
    }

    if (num != 0)
    {
        // make sure num != 0 before dividing by it!!
        double const mean = total / num;

        cout << endl << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        // Remark: setw adds enough whitespaces to pad the width of the stream to the specified value of characters

        for (unsigned i = 0; i < num; ++i)
        {
            cout << setw(20) << prices[i] << setw(40) << prices[i] - mean << endl;
        }
    }

    return 0;
}