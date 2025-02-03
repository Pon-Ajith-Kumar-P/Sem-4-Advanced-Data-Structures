#include <iostream>
using namespace std;

// Template class for B-tree node
template <typename T>
class BtreeNode {
private:
    T *keys; // Array to store keys
    int t; // Minimum degree (defines the range for number of keys)
    BtreeNode **c; // Array of child pointers
    int n; // Current number of keys
    bool leaf; // True if leaf node, false otherwise

public:
    // Constructor for B-tree node
    BtreeNode(int t1, bool leaf1) {
        t = t1; // Set the minimum degree
        leaf = leaf1; // Set if the node is a leaf
        keys = new T[2 * t - 1]; // Allocate memory for keys
        c = new BtreeNode *[2 * t]; // Allocate memory for child pointers
        n = 0; // Initialize number of keys as 0
    }

    // Function to traverse all nodes in a subtree rooted with this node
    void traverse() {
        int i;
        // Traverse through all keys and children
        for (i = 0; i < n; i++) {
            // If this is not a leaf, traverse the subtree rooted with child c[i]
            if (leaf == false)
                c[i]->traverse();
            // Print the key
            cout << " " << keys[i];
        }
        // Print the subtree rooted with last child
        if (leaf == false)
            c[i]->traverse();
    }

    // Function to insert a new key in the subtree rooted with this node
    void InsertNonFull(T k) {
        int i = n - 1; // Initialize index as the rightmost element
        if (leaf == true) {
            // If this is a leaf node
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i]; // Move keys greater than k one position ahead
                i--;
            }
            keys[i + 1] = k; // Insert the new key at found location
            n = n + 1; // Increment the number of keys
        } else {
            // If this node is not a leaf
            while (i >= 0 && keys[i] > k)
                i--;
            if (c[i + 1]->n == 2 * t - 1) {
                // If the child where the key is to be inserted is full
                SplitChild(i + 1, c[i + 1]);
                if (keys[i + 1] < k)
                    i++;
            }
            c[i + 1]->InsertNonFull(k); // Recur to insert the key
        }
    }

    // Function to split the child y of this node
    void SplitChild(int i, BtreeNode *y) {
        BtreeNode *z = new BtreeNode(y->t, y->leaf); // Create a new node
        z->n = t - 1; // Set the number of keys in the new node
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t]; // Copy the last (t-1) keys of y to z
        if (y->leaf == false) {
            for (int j = 0; j < t; j++)
                z->c[j] = y->c[j + t]; // Copy the last t children of y to z
        }
        y->n = t - 1; // Reduce the number of keys in y
        for (int j = n; j >= i + 1; j--)
            c[j + 1] = c[j]; // Shift children of this node to make space for new child
        c[i + 1] = z; // Link the new child to this node
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j]; // Shift keys of this node to make space for new key
        keys[i] = y->keys[t - 1]; // Copy the middle key of y to this node
        n = n + 1; // Increment the number of keys in this node
    }

    // Function to search a key in the subtree rooted with this node
    BtreeNode *search(T k) {
        int i = 0;
        while (i < n && k > keys[i])
            i++;
        if (keys[i] == k)
            return this; // If the key is found, return this node
        if (leaf == true)
            return NULL; // If the key is not found and this is a leaf node, return NULL
        return c[i]->search(k); // Recur to search in the appropriate child
    }
    
    // Friend class Btree to access private members
    template <typename U>
    friend class Btree;
};

// Template class for B-tree
template <typename T>
class Btree {
private:
    BtreeNode<T> *root; // Pointer to root node
    int t; // Minimum degree

public:
    // Constructor for B-tree
    Btree(int t1) {
        root = NULL; // Initialize root as NULL
        t = t1; // Set the minimum degree
    }

    // Function to traverse the B-tree
    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    // Function to search a key in the B-tree
    BtreeNode<T> *search(T k) {
        return (root == NULL) ? NULL : root->search(k);
    }

    // Function to insert a new key in the B-tree
    void insert(T k) {
        if (root == NULL) {
            root = new BtreeNode<T>(t, true); // Allocate memory for root
            root->keys[0] = k; // Insert the first key
            root->n = 1; // Initialize number of keys in root as 1
        } else {
            if (root->n == 2 * t - 1) {
                BtreeNode<T> *s = new BtreeNode<T>(t, false); // Allocate memory for new root
                s->c[0] = root; // Make old root as child of new root
                s->SplitChild(0, root); // Split the old root and move a key to the new root
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->c[i]->InsertNonFull(k); // Insert the new key in the appropriate child
                root = s; // Change root
            } else
                root->InsertNonFull(k); // Insert the new key in the non-full root
        }
    }

};

int main() {
    int t, choice;
    cout << "Enter the degree of B-tree: ";
    cin >> t; // Input the degree of B-tree
    Btree<int> btree(t); // Create a B-tree of given degree

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Traverse\n";
        cout << "3. Search\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Input the user's choice

        switch (choice) {
        case 1: {
            int key;
            cout << "Enter the key to insert: ";
            cin >> key; // Input the key to insert
            btree.insert(key); // Insert the key in the B-tree
            break;
        }
        case 2:
            cout << "B-tree traversal: ";
            btree.traverse(); // Traverse the B-tree
            cout << endl;
            break;
        case 3: {
            int key;
            cout << "Enter the key to search: ";
            cin >> key; // Input the key to search
            BtreeNode<int> *result = btree.search(key); // Search the key in the B-tree
            if (result != NULL)
                cout << "Key " << key << " found in the B-tree.\n";
            else
                cout << "Key " << key << " not found in the B-tree.\n";
            break;
        }
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4); // Repeat until the user chooses to exit

    return 0;
}