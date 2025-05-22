#include <iostream>
using namespace std;

template <class T>
class LeftistHeap 
{
private:
    struct LeftistNode 
    {
        T element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const T &e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0)
            : element{e}, left{lt}, right{rt}, npl{np} {}
    };

    LeftistNode *root;

    void merge(LeftistHeap &rhs)
    {
        if(this==&rhs)
            return;
        root = merge(root,rhs.root);
        rhs.root = NULL;
    }

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2) 
    {
        if (h1==NULL) 
            return h2;
        if (h2==NULL) 
            return h1;
        if (h1->element < h2->element)
            return merge1(h1, h2);
        else
            return merge1(h2, h1);
    }

    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2) 
    {
        if (h1->left==NULL)
            h1->left = h2;
        else 
        {
            h1->right = merge(h1->right, h2);
            if (!h1->right || (h1->left->npl < h1->right->npl))  
                swapChildren(h1);
            h1->npl = (h1->right ? h1->right->npl : -1) + 1;  
        }
        return h1;
    }

    void swapChildren(LeftistNode *t) 
    {
        swap(t->left, t->right);
    }

    void reclaimMemory(LeftistNode *t) 
    {
        if(t) 
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
            t = nullptr;

        }
    }

    LeftistNode *clone(LeftistNode *t) const 
    {
        if (!t) return nullptr;
        return new LeftistNode(t->element, clone(t->left), clone(t->right), t->npl);
    }

    // Print tree structure
    void printTreeHelper(LeftistNode *t,int level=0) const
    {
        if(t==nullptr)
            return;
        printTreeHelper(t->right,level+1);
        for(int i=0;i<level;i++)
            cout<<"      ";
        cout<<t->element<<endl;
        printTreeHelper(t->left,level+1);
    }

public:
    LeftistHeap() : root(nullptr) {}

    // Copy Constructor
    LeftistHeap(const LeftistHeap &rhs) 
    {
        root = clone(rhs.root);
    }

    ~LeftistHeap() 
    { 
        reclaimMemory(root);
    }

    bool isEmpty() const 
    { 
        return root == nullptr; 
    }

    const T *findMin() const 
    {
        if (isEmpty()) 
        {
            cout << "Heap is empty!" << endl;
            return nullptr;
        }
        return &root->element;
    }

    void insert(const T &x) 
    { 
        root = merge(new LeftistNode{x}, root); 
    }

    void deleteMin() 
    {
        if (isEmpty()) 
        {
            cout << "Heap is empty! Cannot delete." << endl;
            return;
        }
        LeftistNode *oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }

    void deleteMin(T &minItem) 
    {
        const T *minPtr = findMin();
        if (!minPtr) return;
        minItem = *minPtr;
        deleteMin();
    }

    void printTree() const 
    {
        if (isEmpty()) 
        {
            cout << "Heap is empty!" << endl;
            return;
        }
        printTreeHelper(root,0);
    }
};

int main() 
{
    LeftistHeap<int> heap;
    int choice, value;
    
    while (true) 
    {
        cout << "\n1) Insert\n2) Find Min\n3) Delete Min\n4) Find and Delete Min\n5) Print Heap (Tree Format)\n6) Copy Heap\n7) Exit\nEnter choice: ";
        cin >> choice;
        
        switch(choice) 
        {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                heap.printTree();
                break;
            case 2: 
                {
                    const int *minPtr = heap.findMin();
                    if (minPtr)
                        cout << "Minimum value: " << *minPtr << endl;
                }
                break;
            case 3:
                heap.deleteMin();
                heap.printTree();
                break;
            case 4: 
                {
                    int minValue;
                    heap.deleteMin(minValue);
                    cout << "Deleted minimum element: " << minValue << endl;
                    heap.printTree();
                }
                break;
            case 5:
                cout << "Heap structure:\n";
                heap.printTree();
                break;
            case 6:
                {
                    LeftistHeap<int> heapCopy(heap);  // Using copy constructor
                    cout << "Copied Heap structure:\n";
                    heapCopy.printTree();
                }
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
}
