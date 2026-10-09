// Price deviation evaluation v4 - We know the prices and the zones and compute mean and deviation.
// Now we want to generalize v3 to the case of z zones instead of 2.

#include <iostream>
#include <iomanip>

using std::cout; // Usually we don't need this.
using std::cin; // We are using these just to avoid writing
using std::endl; // std::command when we need it
using std::setw;

const unsigned MAXZONE = 3; // Global constant, max number of zones.
const unsigned MAXDIM = 10; // Global constant, max number per zone.

void evaluate_deviation(int num, double sum, double prices[]); // we are passing the pointer to the first element of the prices array.
// MEMO: the name of an array is the pointer to its first element.
void evaluate_all_deviations(int num[], double sum[], double prices[][MAXDIM]);

int main (void)
{
    double prices[MAXZONE][MAXDIM]; // Now we use a matrix with MAXZONE rows and MAXDIM columns.
    int num[MAXZONE] = {}; // num is now an array of integers, one per each zone.
    double sum[MAXZONE] = {};

    bool exit = false;


     while (!exit)
     {
         double price;
         cout << "Input price: ";
         cin >> price;

         if (!cin)
         {
             cout << "Invalid input" << endl;
             exit = true;
         }

         int zone;
         if (!exit)
         {
             cout << "In which zone? (from 0 to " << MAXZONE-1 <<")";
             cin >> zone;
             if (zone < 0 or zone >= MAXZONE)
             {
                 cout << "Invalid zone";
                 exit = true;
             }
         }
         // Now we have stored price and zone
         if (!exit)
         {
             prices[zone][num[zone]] = price;
             ++num[zone];
             sum[zone] += price;
             }
         }
    for (std::size_t zone = 0; zone < MAXZONE; ++zone)
    {
    cout << "Zone " << zone << ":" << endl;
    evaluate_deviation(num[zone], sum[zone], prices[zone]);

    }}

void evaluate_deviation(int num, double sum, double prices[]) // we are passing the pointer to the first element of the prices array.
{
    if (num > 0){
        cout << "\nSum = " << sum << endl;
        double mean = sum/num;
        cout << "Mean = " << mean << endl;
        cout << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        for (std::size_t idx = 0; idx <num; ++idx){
            double deviation = prices[idx] - mean;
            cout << setw(20) << prices[idx] << setw(40) << deviation<< endl;
        }
    }

}

// As an alternative we can write an evaluate_all_deviation function
void evaluate_all_deviations(int num[], double sum[], double prices[][MAXDIM])
{
    for (std::size_t zone = 0; zone < MAXZONE; ++zone)
    {
        cout << "\nZone " << zone;
        if (num[zone] == 0)
            cout << endl;
        evaluate_deviation(num[zone], sum[zone], prices[zone]);
    }
}

// see the version with a read_from_input function.