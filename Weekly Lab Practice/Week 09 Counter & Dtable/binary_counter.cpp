#include <iostream>
#include <vector>
using namespace std;

class BinaryCounter 
{
private:
    vector<int> bits;
    int flip;    

public:
    BinaryCounter(int n) : bits(n, 0), flip(0) {}

    void increment() 
    {
        int i = 0;
        while (i < bits.size() && bits[i] == 1) 
        {
            bits[i] = 0; 
            i++;
            flip++;
        }
        if (i < bits.size()) 
        {
            bits[i] = 1; 
            flip++;
        }
    }

    void simulate(int steps) 
    {
        int totFlip = 0;
        for (int i = 0; i < steps; i++) 
        {
            increment();
            totFlip += flip;
            cout << "Step " << (i + 1) << ": Flips = " << flip << " | Total Flips so far = " << totFlip;
            cout << " | Binary number: ";
            for (int j = bits.size() - 1; j >= 0; j--) 
            {
                cout << bits[j];
            }
            cout << endl;
            flip = 0; 
        }
        cout << "Final Total flips: " << totFlip << endl;
        cout << "Amortized flips per increment: " << (double)totFlip / steps << endl;
    }
};

int main() 
{
    int n, steps;
    cout << "Enter number of bits: ";
    cin >> n;
    cout << "Enter number of increments: ";
    cin >> steps;
    
    BinaryCounter counter(n);
    counter.simulate(steps);
    
    return 0;
}
