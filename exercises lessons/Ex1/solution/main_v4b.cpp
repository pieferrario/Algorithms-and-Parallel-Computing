/* Price deviation evaluation - v4b
 * Same as v4, only now weask the user to directly insert the index of the location.
 * This allows us to skip the lookups and simplify the code.
 */
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::string;
using std::format;

/*
    Let's simplify the previous by just using numeric zone codes...
*/
string const PROMPT = "Input zone [0/1], price (type anything else to quit): ";
unsigned constexpr MAX_SIZE = 100;
unsigned constexpr NUM_ZONES = 2;


// Remember: you MUST declare all but the first dimension for a multidimensional array!
void read_prices(double[][MAX_SIZE], double [], unsigned []);
void deviations(double const[][MAX_SIZE], double const[], unsigned const []);

int main ()
{
    double prices[NUM_ZONES][MAX_SIZE];
    double zone_means[NUM_ZONES];
    unsigned zone_counts[NUM_ZONES];

    read_prices(prices, zone_means, zone_counts);
    deviations(prices, zone_means, zone_counts);
}

void read_prices (
    double prices[][MAX_SIZE],
    double zone_means[],
    unsigned zone_counts[]
)
/*
    Now we densely store the prices and the locations in two arrays
*/
{
    unsigned zone;
    double price;
    for (size_t i = 0; i < NUM_ZONES; ++i)
    {
        zone_counts[i] = 0;
        zone_means[i] = 0.0;
    }

    while (
        cout << PROMPT << endl
        && cin
        && cin >> zone
        && zone < NUM_ZONES             // no need for a search operation
        && zone_counts[zone] < MAX_SIZE    // as soon as a zone is already full, we break from the loop
        && cin >> price                 // otherwise we proceed to store the result...
        && price > 0                    // ...if it is valid!
    )
    {
        prices[zone][zone_counts[zone]++] = price;
        zone_means[zone] += price;
    }
    for (size_t i = 0; i < NUM_ZONES; ++i) if (zone_counts[i] > 0) zone_means[i] /= zone_counts[i];

    if (!cin)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void deviations (
    double const prices[][MAX_SIZE],
    double const zone_means[],
    unsigned const zone_counts[]
)
{
    // displaying the results
    cout << endl << setw(20) << "Zones" << setw(40) << "Prices"<< setw(60) << "Zonal Mean Deviation" << endl;
    for (size_t i = 0; i < NUM_ZONES; ++i)
    {
        for (size_t j = 0; j < zone_counts[i]; ++j)
        {
            // print the zone, price, and deviation from zonal mean
            cout << setw(20) << i << setw(40) << prices[i][j];
            cout << setw(60) << prices[i][j] - zone_means[i] << endl;
        }
    }
}