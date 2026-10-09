/* Price deviation evaluation - v5
 * With the previous solution, we are likely to overallocate the prices 2D array.
 * Here we use two 1D arrays, one for prices, one for zones.
 * The price we pay is that we have to go back to the lookups, which are tedious and inefficient.
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

unsigned read_prices(double[], char[], double[], unsigned[]);
void evaluate_deviations(double const [], char const [], unsigned const, double const[]);

int main ()
{
    double prices[MAX_SIZE];
    char locs[MAX_SIZE];
    double zone_means[NUM_ZONES];
    unsigned zone_counts[NUM_ZONES];

    unsigned num = read_prices(prices, locs, zone_means, zone_counts);
    evaluate_deviations(prices, locs, num, zone_means);
}

unsigned read_prices (
    double prices[],
    char stores[],
    double zone_means[],
    unsigned zone_counts[]
)
/*
 Now we densely store the prices and the locations in two arrays
*/
{
    unsigned num = 0;
    for (size_t i = 0; i < NUM_ZONES; ++i)
    {
        zone_counts[i] = 0;
        zone_means[i] = 0.0;
    }
    while (
        cout << PROMPT << endl
        && cin                      // the stream has successfully stored the previous value
        && num < MAX_SIZE           // the array is not exhausted
        && cin >> stores[num]
        && cin >> prices[num]
        && prices[num] > 0          // we check that the provided price makes sense
    )
    {
        // other than storing values, we must check that the zone provided by the user exists in the list
        // of declared zones, which requires a sequential lookup
        bool zone_found = false;
        for (size_t i = 0; i < NUM_ZONES; ++i)
        {
            if (ZONE_IDS[i] == stores[num])
            {
                zone_found = true;
                zone_counts[i]++;
                zone_means[i] += prices[num];
                break;
            }
        }
        if (!zone_found)
            break;

        // Question: we have already inserted the values in the cells via cin, isn't this a problem?
        ++num;
    }
    for (size_t i = 0; i < NUM_ZONES; ++i) if (zone_counts[i] > 0)
        zone_means[i] /= zone_counts[i];

    if (!cin)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return num;
}

void evaluate_deviations (
    double const prices[],
    char const stores[],
    unsigned const num,
    double const zone_means[]
)
{
    // displaying the results
    cout << endl << setw(20) << "Zones" << setw(40) << "Prices"<< setw(60) << "Zonal Mean Deviation" << endl;
    for (size_t i = 0; i < num; ++i)    // iterating through the array
    {
         // lookup of the corresponding zone (very inefficient, but we are just using C-style arrays!)
         size_t zone_idx = 0;
         for (size_t j = 0; j < NUM_ZONES; ++j)
         {
             if (ZONE_IDS[j] == stores[i])
             {
                 zone_idx = j;
                 break;
             }
         }

         // print the zone, price, and deviation from zonal mean
         cout << setw(20) << stores[i]  << setw(40) << prices[i];
         cout << setw(60) << prices[i] - zone_means[zone_idx] << endl;
    }
}
// TODO: labs announcement