/* Price deviation evaluation - v4
 * The previous versions cannot easily scale to more than 2 zones (too much copy-paste!).
 * Here we use two-dimensional price arrays to store prices in a single variable.
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
unsigned constexpr NUM_ZONES = 2;
char const ZONE_IDS[] = {'c', 's'};


// Remember: you MUST declare all but the first dimension for a multidimensional array!
void read_prices(double[][MAX_SIZE], double [], unsigned []);
void evaluate_deviations(double const[][MAX_SIZE], double const[], unsigned const []);

int main ()
{
    double prices[NUM_ZONES][MAX_SIZE];     // the rows (first index) encode the zones, the columns (second index)
                                            // different entries
    double zone_means[NUM_ZONES];           // before we had scalars to keep track of counts/sums, now they have become
                                            // arrays
    unsigned zone_counts[NUM_ZONES];

    read_prices(prices, zone_means, zone_counts);
    evaluate_deviations(prices, zone_means, zone_counts);
}

void read_prices (
    double prices[][MAX_SIZE],
    double zone_means[],
    unsigned zone_counts[]
)
{
    char zone;
    double price;
    for (size_t i = 0; i < NUM_ZONES; ++i)
    {
        // initialization of the counts/means
        zone_counts[i] = 0;
        zone_means[i] = 0.0;
    }

    while (cout << PROMPT << endl && cin && cin >> zone && cin >> price && price > 0)
    {
        // other than storing values, we must check that the zone provided by the user exists in the list
        // of declared zones, which requires a sequential lookup
        bool zone_found = false;
        for (size_t i = 0; i < NUM_ZONES; ++i)
        {
            if (ZONE_IDS[i] == zone and zone_counts[i] < MAX_SIZE)
            {
                zone_found = true;
                prices[i][zone_counts[i]++] = price;
                zone_means[i] += price;
                break;  // this break statement only affects the for loop
            }
        }
        if (!zone_found) break;
    }
    for (size_t i = 0; i < NUM_ZONES; ++i)
        if (zone_counts[i] > 0)
            zone_means[i] /= zone_counts[i];

    if (!cin)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void evaluate_deviations (
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
            cout << setw(20) << ZONE_IDS[i]  << setw(40) << prices[i][j];
            cout << setw(60) << prices[i][j] - zone_means[i] << endl;
        }
    }
}
