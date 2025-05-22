#include<iostream>
#include "Intcell.h"
using namespace std;
#include<iostream>
using namespace std;
#include "Intcell.h"
Intcell::Intcell(int initialValue)
{
    storedValue = initialValue;
}
int Intcell::read() const
{
    return storedValue;
}
void Intcell::write(int x)
{
    storedValue = x;
}
int main()
{
    Intcell m;
    m.write(5);
    cout << "Cell Contents : " << m.read() << endl;
    return 0;
}