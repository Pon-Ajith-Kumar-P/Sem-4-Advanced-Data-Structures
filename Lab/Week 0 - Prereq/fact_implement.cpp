#include<iostream>
using namespace std;
class Factorial
{
    int n;
    public:
    Factorial(int n)
    {
        this->n = n;
    }
    int fact()
    {
        int fact =1;
        for(int i=1;i<=n;i++)
        {
            fact = fact*i;
        }
        return fact;
    }
};
int main()
{
    int n;
    cout<<"Enter the number: ";
    cin>>n;
    Factorial f(n);
    cout<<"Factorial of "<<n<<" is "<<f.fact();
    return 0;
}