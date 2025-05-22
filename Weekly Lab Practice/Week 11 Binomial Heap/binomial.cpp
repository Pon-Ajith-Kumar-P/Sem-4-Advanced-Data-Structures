#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

template <typename T>
class BinomialQueue {
public:
    BinomialQueue() : theTrees(DEFAULT_TREES, nullptr), currentSize(0) {}

    BinomialQueue(const T& item) : theTrees(DEFAULT_TREES, nullptr), currentSize(1) {
        theTrees[0] = new BinomialNode(item, nullptr, nullptr);
    }

    BinomialQueue(const BinomialQueue& rhs) : theTrees(rhs.theTrees.size(), nullptr), currentSize(rhs.currentSize) {
        for (int i = 0; i < rhs.theTrees.size(); ++i)
            theTrees[i] = clone(rhs.theTrees[i]);
    }

    ~BinomialQueue() {
        makeEmpty();
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    const T& findMin() const {
        return theTrees[findMinIndex()]->element;
    }

    void insert(const T& x) {
        BinomialQueue oneItem(x);
        merge(oneItem);
    }

    void deleteMin() {
        T x;
        deleteMin(x);
    }

    void deleteMin(T& minItem) {
        int minIndex = findMinIndex();
        minItem = theTrees[minIndex]->element;

        BinomialNode* oldRoot = theTrees[minIndex];
        BinomialNode* deletedTree = oldRoot->leftChild;
        delete oldRoot;

        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize(minIndex + 1);
        deletedQueue.currentSize = (1 << minIndex) - 1;

        for (int j = minIndex - 1; j >= 0; --j) {
            deletedQueue.theTrees[j] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[j]->nextSibling = nullptr;
        }

        theTrees[minIndex] = nullptr;
        currentSize -= deletedQueue.currentSize + 1;

        merge(deletedQueue);
    }

    void makeEmpty() {
        for (auto& root : theTrees)
            makeEmpty(root);
        currentSize = 0;
    }

    void merge(BinomialQueue& rhs) {
        if (this == &rhs)
            return;

        currentSize += rhs.currentSize;

        if (currentSize > capacity()) {
            int oldNumTrees = theTrees.size();
            int newNumTrees = max(theTrees.size(), rhs.theTrees.size()) + 1;
            theTrees.resize(newNumTrees);
            for (int i = oldNumTrees; i < newNumTrees; ++i)
                theTrees[i] = nullptr;
        }

        BinomialNode* carry = nullptr;
        for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2) {
            BinomialNode* t1 = theTrees[i];
            BinomialNode* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;
            int whichCase = (t1 != nullptr) + 2 * (t2 != nullptr) + 4 * (carry != nullptr);

            switch (whichCase) {
                case 0: break;
                case 1: break;
                case 2: theTrees[i] = t2; rhs.theTrees[i] = nullptr; break;
                case 4: theTrees[i] = carry; carry = nullptr; break;
                case 3: carry = combineTrees(t1, t2); theTrees[i] = rhs.theTrees[i] = nullptr; break;
                case 5: carry = combineTrees(t1, carry); theTrees[i] = nullptr; break;
                case 6: carry = combineTrees(t2, carry); rhs.theTrees[i] = nullptr; break;
                case 7:
                    theTrees[i] = carry;
                    carry = combineTrees(t1, t2);
                    rhs.theTrees[i] = nullptr;
                    break;
            }
        }

        for (auto& root : rhs.theTrees)
            root = nullptr;
        rhs.currentSize = 0;
    }

    void printTree() const {
        cout << "\n--- Binomial Queue Structure ---\n";
        for (int i = 0; i < theTrees.size(); ++i) {
            if (theTrees[i] != nullptr) {
                cout << "Tree of order " << i << ":\n";
                printTree(theTrees[i], 0);
                cout << endl;
            }
        }
        if (isEmpty()) {
            cout << "The binomial queue is empty.\n";
        }
    }

private:
    struct BinomialNode {
        T element;
        BinomialNode* leftChild;
        BinomialNode* nextSibling;

        BinomialNode(const T& e, BinomialNode* lt, BinomialNode* rt)
            : element{ e }, leftChild{ lt }, nextSibling{ rt } {}
    };

    const static int DEFAULT_TREES = 1;
    vector<BinomialNode*> theTrees;
    int currentSize;

    int findMinIndex() const {
        int i;
        for (i = 0; theTrees[i] == nullptr; ++i);
        int minIndex = i;
        for (; i < theTrees.size(); ++i)
            if (theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element)
                minIndex = i;
        return minIndex;
    }

    int capacity() const {
        return (1 << theTrees.size()) - 1;
    }

    BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2) {
        if (t2->element < t1->element)
            return combineTrees(t2, t1);
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        return t1;
    }

    void makeEmpty(BinomialNode*& t) {
        if (t != nullptr) {
            makeEmpty(t->leftChild);
            makeEmpty(t->nextSibling);
            delete t;
            t = nullptr;
        }
    }

    BinomialNode* clone(BinomialNode* t) const {
        if (t == nullptr)
            return nullptr;
        return new BinomialNode(t->element, clone(t->leftChild), clone(t->nextSibling));
    }

    void printTree(BinomialNode* t, int indent) const {
        if (t != nullptr) {
            cout << setw(indent) << "";
            cout << t->element << "\n";
            printTree(t->leftChild, indent + 4);
            printTree(t->nextSibling, indent);
        }
    }
};

int main() {
    BinomialQueue<int> bq;
    int choice, value;

    while (true) {
        cout << "\n--- Binomial Queue Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. Find Min\n";
        cout << "3. Delete Min\n";
        cout << "4. Check if Empty\n";
        cout << "5. Make Empty\n";
        cout << "6. Print Tree\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                bq.insert(value);
                bq.printTree();
                break;

            case 2:
                cout << "Minimum element: " << bq.findMin() << endl;
                break;

            case 3:
                bq.deleteMin();
                cout << "Minimum element deleted.\n";
                bq.printTree();
                break;

            case 4:
                cout << (bq.isEmpty() ? "Queue is empty.\n" : "Queue is not empty.\n");
                break;

            case 5:
                bq.makeEmpty();
                cout << "Queue cleared.\n";
                break;

            case 6:
                bq.printTree();
                break;

            case 7:
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
 