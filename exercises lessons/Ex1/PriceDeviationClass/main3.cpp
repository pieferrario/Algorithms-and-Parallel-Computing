// Price deviation evaluation v3 - We know the prices and the zones and compute mean and deviation.
// However, v2 was not great since it was a sequence of ctrl+c ctrl+v.
// Here we write a proper function to evaluate the deviation.

#include <iostream>
#include <iomanip>

using std::cout; // Usually we don't need this.
using std::cin; // We are using these just to avoid writing
using std::endl; // std::command when we need it
using std::setw;

const unsigned MAXDIM = 10; // Global constant, max number per zone.

void evaluate_deviation(int num, double sum, double prices[]); // we are passing the pointer to the first element of the prices array.
// MEMO: the name of an array is the pointer to its first element.
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
    cout << "Zone C" <<endl;
    evaluate_deviation(numC, sumC, pricesC);
    cout << "Zone S" <<endl;
    evaluate_deviation(numS, sumS, pricesS);
    return 0;
}

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