#include <iostream>
using namespace std;

template <class T>
class SkewHeap {
private:
    struct SkewNode {
        T element;
        SkewNode *left;
        SkewNode *right;
        
        SkewNode(const T &e, SkewNode *lt = nullptr, SkewNode *rt = nullptr)
            : element{e}, left{lt}, right{rt} {}
    };
    
    SkewNode *root;
    
    SkewNode *merge(SkewNode *h1, SkewNode *h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        if (h1->element > h2->element)
            swap(h1, h2);
        
        h1->right = merge(h1->right, h2);
        swap(h1->left, h1->right);
        return h1;
    }
    
    void reclaimMemory(SkewNode *t) {
        if (!t) return;
        reclaimMemory(t->left);
        reclaimMemory(t->right);
        delete t;
    }
    
    SkewNode *clone(SkewNode *t) const {
        if (!t) return nullptr;
        return new SkewNode(t->element, clone(t->left), clone(t->right));
    }
    
    void printTreeHelper(SkewNode *t, int level = 0) const {
        if (!t) return;
        printTreeHelper(t->right, level + 1);
        for (int i = 0; i < level; i++) cout << "      ";
        cout << t->element << endl;
        printTreeHelper(t->left, level + 1);
    }
    
public:
    SkewHeap() : root(nullptr) {}
    
    SkewHeap(const SkewHeap &rhs) {
        root = clone(rhs.root);
    }
    
    ~SkewHeap() {
        reclaimMemory(root);
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }
    
    const T *findMin() const {
        if (isEmpty()) {
            cout << "Heap is empty!" << endl;
            return nullptr;
        }
        return &root->element;
    }
    
    void insert(const T &x) {
        root = merge(new SkewNode{x}, root);
    }
    
    void deleteMin() {
        if (isEmpty()) {
            cout << "Heap is empty! Cannot delete." << endl;
            return;
        }
        SkewNode *oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }
    
    void deleteMin(T &minItem) {
        const T *minPtr = findMin();
        if (!minPtr) return;
        minItem = *minPtr;
        deleteMin();
    }
    
    void printTree() const {
        if (isEmpty()) {
            cout << "Heap is empty!" << endl;
            return;
        }
        printTreeHelper(root, 0);
    }
};

int main() {
    SkewHeap<int> heap;
    int choice, value;
    
    while (true) {
        cout << "\n1) Insert\n2) Find Min\n3) Delete Min\n4) Find and Delete Min\n5) Print Heap (Tree Format)\n6) Copy Heap\n7) Exit\nEnter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                heap.insert(value);
                heap.printTree();
                break;
            case 2: {
                const int *minPtr = heap.findMin();
                if (minPtr)
                    cout << "Minimum value: " << *minPtr << endl;
                break;
            }
            case 3:
                heap.deleteMin();
                heap.printTree();
                break;
            case 4: {
                int minValue;
                heap.deleteMin(minValue);
                cout << "Deleted minimum element: " << minValue << endl;
                heap.printTree();
                break;
            }
            case 5:
                cout << "Heap structure:\n";
                heap.printTree();
                break;
            case 6: {
                SkewHeap<int> heapCopy(heap);
                cout << "Copied Heap structure:\n";
                heapCopy.printTree();
                break;
            }
            case 7:
                return 0;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }
}