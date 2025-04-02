#include <iostream>
using namespace std;

class DynamicTable 
{
private:
    int *arr;
    int capacity;
    int size;
    int totCopies;

public:
    DynamicTable() : capacity(1), size(0), totCopies(0) 
    {
        arr = new int[capacity];
    }

    ~DynamicTable() 
    {
        delete[] arr;
    }

    void insert(int value) 
    {
        if (size == capacity) 
        {
            cout << "Resizing table from capacity " << capacity << " to " << capacity * 2 << endl;
            resize();
        }
        arr[size++] = value;
        displayTable(value);
    }

    void resize() 
    {
        int newCapacity = capacity * 2;
        int *newArr = new int[newCapacity];

        cout << "Copying elements: ";
        for (int i = 0; i < size; i++) 
        {
            newArr[i] = arr[i];
            cout << arr[i] << " ";
            totCopies++;
        }
        cout << endl;

        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

    void displayTable(int value) 
    {
        cout << "Inserted: " << value << " | Table: [ ";
        for (int i = 0; i < size; i++) 
        {
            cout << arr[i] << " ";
        }
        cout << "] \nCapacity: " << capacity << " | Size: " << size << endl;
    }

    void simulate(int n) 
    {
        for (int i = 1; i <= n; i++) 
        {
            cout << "\nStep " << (i ) << ": Inserting " << i << endl;
            insert(i);
        }
        cout << "\n---------------------------------------";
        cout << "\nTotal copies: " << totCopies << endl;
        cout << "Amortized cost per insert: " << (double)(n + totCopies) / n << endl;
        cout << "---------------------------------------";
    }
};

int main() 
{
    int n;
    cout << "Enter number of insertions: ";
    cin >> n;

    DynamicTable table;
    table.simulate(n);

    return 0;
}