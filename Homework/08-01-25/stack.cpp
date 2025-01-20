#include<iostream>
#include<string>
using namespace std;

class Stack
{
    static const int N = 5;
    int top;
    int arr[N];
    
    public:
    Stack()
    {
        top = -1;
        for(int i=0;i<N;i++)
            arr[i] = 0;
    }

    bool isEmpty()
    {
        if(top==-1)
            return true;
        else
            return false;
    }

    bool isFull()
    {
        if(top==N-1)
            return true;
        else
            return false;
    }

    void push(int val)
    {
        if(isFull())
            cout<<"\nStack Overflow";
        else
        {
            arr[++top] = val;
        }
    }    

    int pop()
    {
        if(isEmpty())
        {
            cout<<"\nStack Underflow";
            return 0;
        }
        else
        {
            int popval = arr[top];
            arr[top]=0;
            top--;
            return popval;
        }
    }

    int peek()
    {
        if(isEmpty())
        {
            cout<<"\nStack Underflow";
            return 0;
        }
        else
        {
            return arr[top];
        }
    }

    void display()
    {
        cout<<"\nStack\n";
        for(int i=N-1;i>=0;i--)
        {
            cout<<arr[i]<<endl;
        }
    }
};

int main()
{
    Stack s1;
    int option,val;
    do
    {
        cout<<"\n---Stack Operations---";
        cout<<"\n1. Push";
        cout<<"\n2. Pop";
        cout<<"\n3. Peek";
        cout<<"\n4. Display";
        cout<<"\n5. Exit";

        cout<<"\nSelect an operation : ";
        cin>>option;

        switch(option)
        {
            case 1:
                cout<<"\nEnter the value to push : ";
                cin>>val;
                s1.push(val);
                break;
            case 2:
                cout<<"\nPopped : "<<s1.pop();
                break;
            case 3:
                cout<<"\nTop of Stack : "<<s1.peek();
                break;
            case 4:
                s1.display();
                break;
            case 5:
                cout<<"\nThank You";
                break;
            default:
                cout<<"\nInvalid operation";
        }


    } while (option!=5);
    
}