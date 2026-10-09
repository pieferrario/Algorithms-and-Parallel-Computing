// Price deviation evaluation v1 - We know the prices and compute mean and deviation.

#include <iostream>
#include <iomanip>

using std::cout; // Usually we don't need this.
using std::cin; // We are using these just to avoid writing
using std::endl; // std::command when we need it
using std::setw;


int main (void)
{
    // We need to put data in a data structure. Imagine that we only want to
    // store prices and compute the mean and deviation. Hence, an array is a
    // reasonable data structure since we assume we know the number of shops in Milan

    const unsigned MAXDIM = 3; // Max number of shops
    double prices[MAXDIM];
    int num = 0; // index to insert in prices & number of items
    bool exit = false; // we use exit to check if we need to exit the loop in which we store the data

    double price; // here is where we store single data from cin
    double sum = 0;

    while (!exit and  num < MAXDIM)
    {
        // Here we insert prices in the data structure
        cout  << "Input price: ";
        cin >> price;
        if (!cin){ // we exit the loop if the cin in ìnput is not compliant with the types
            exit = true;
            cout << "i am exiting the while loop" << endl;
        }
        else
        {
            prices[num] = price;
            cout << "Price = " << price << endl;
            ++num;
            sum += price;
        }
    }

    // now we compute the mean
    if (num > 0)
    {
        double mean = sum/num;
        cout << "\n Mean = " << mean << endl;
        cout << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        for (std::size_t idx = 0; idx <num; ++idx){
            double deviation = prices[idx] - mean;
            cout << setw(20) << prices[idx] << setw(40) << deviation << endl;
        }
    }
    else
        cout << "You cannot divide by 0";
    return 0;
}
