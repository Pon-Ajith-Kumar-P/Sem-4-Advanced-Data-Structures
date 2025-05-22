#include <iostream>
#include <vector>
using namespace std;

class AugmentedStack {
private:
    vector<int> stackArray;
    int top;
    int totalPushes;
    int totalPops;
    int totalMultipops;
    int multipopOp;

public:
    AugmentedStack(int capacity) : stackArray(capacity, 0), top(-1), totalPushes(0), totalPops(0), totalMultipops(0), multipopOp(0) {}

    bool push(int value) {
        if (top == (int)stackArray.size() - 1) {
            cout << "Stack Overflow\n";
            return false;
        }
        stackArray[++top] = value;
        totalPushes++;
        displayAmortizedCost();
        return true;
    }

    int pop() {
        if (top == -1) {
            cout << "Stack Underflow\n";
            return -1;
        }
        int poppedValue = stackArray[top--];
        totalPops++;
        displayAmortizedCost();
        return poppedValue;
    }

    void multipop(int k) {
        int count = 0;
        while (top != -1 && count < k) {
            cout << "Popped: " << pop() << "\n";
            count++;
        }
        totalMultipops += count;
        multipopOp++;
        displayAmortizedCost();
    }

    void displayStack() {
        if (top == -1) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack contents: ";
        for (int i = 0; i <= top; i++) {
            cout << stackArray[i] << " ";
        }
        cout << "\n";
    }

    void displayAmortizedCost() {
        double amorPush = (totalPushes == 0) ? 0 : (double)totalPushes / totalPushes;
        double amorPop = (totalPops == 0) ? 0 : (double)totalPops / totalPops;
        double amorMultipop = (multipopOp == 0) ? 0 : (double)totalMultipops / multipopOp;
        cout << "---------------------------------------------\n";
        cout << "Amortized cost per push: " << amorPush << "\n";
        cout << "Amortized cost per pop: " << amorPop << "\n";
        cout << "Amortized cost per multipop: " << amorMultipop << "\n";
        cout << "---------------------------------------------\n";
    }
};

int main() {
    int capacity;
    cout << "Enter stack capacity: ";
    cin >> capacity;
    AugmentedStack stack(capacity);

    int choice, value, k;
    do {
        cout << "\n-----Augmented Stack-----\n1. Push\n2. Pop\n3. MultiPop\n4. Display Stack\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                stack.push(value);
                break;
            case 2:
                cout << "Popped: " << stack.pop() << "\n";
                break;
            case 3:
                cout << "Enter number of elements to pop: ";
                cin >> k;
                stack.multipop(k);
                break;
            case 4:
                stack.displayStack();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}