// Price deviation evaluation v2 - We know the prices and the zones and compute mean and deviation.

#include <iostream>
#include <iomanip>

using std::cout; // Usually we don't need this.
using std::cin; // We are using these just to avoid writing
using std::endl; // std::command when we need it
using std::setw;

const unsigned MAXDIM = 10; // Global constant, max number per zone.

int main (void)
{
    double pricesC[MAXDIM];
    double pricesS[MAXDIM];

    int numC = 0;
    int numS = 0;

    bool exit = false;

    double sumC = 0.0;
    double sumS = 0.0;

    const char zoneC = 'c'; // These are the keywords to distinguish center
    const char zoneS = 's'; // and suburb.

     while (!exit and  numC < MAXDIM and numS < MAXDIM)
     {
         double price;
         cout << "Input price: ";
         cin >> price;

         if (!cin)
         {
             cout << "Invalid input" << endl;
             exit = true;
         }

         char zone;
         if (!exit)
         {
            cout << "In which zone? (c or s) ";
            cin >> zone;
             if (zone != zoneC and zone!= zoneS)
             {
                 cout << "Invalid zone";
                 exit = true;
             }
         }
         // Now we have stored price and zone
         if (!exit)
         {
             if (zone == zoneC)
             {
                 pricesC[numC] = price;
                 ++numC;
                 sumC += price;
             }
             else
             {
                 pricesS[numS] = price;
                 ++numS;
                 sumS += price;
             }
         }
     }
     // Compute the mean
    if (numC > 0){
        cout << "\nSumC = " << sumC << endl;
        double meanC = sumC/numC;
        cout << "MeanC = " << meanC << endl;
        cout << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        for (std::size_t idx = 0; idx <numC; ++idx){
            double deviationC = pricesC[idx] - meanC;
            cout << setw(20) << pricesC[idx] << setw(40) << deviationC<< endl;
        }
    }
    if (numS > 0)
    {
        cout << "\nSumS = " << sumS << endl;
        double meanS = sumS/numS;
        cout << "MeanC = " << meanS << endl;
        cout << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        for (std::size_t idx = 0; idx <numS; ++idx){
            double deviationS = pricesS[idx] - meanS;
            cout << setw(20) << pricesS[idx] << setw(40) << deviationS << endl;
        }
    }

    return 0;
}