#include <iostream>
using namespace std;

template <typename T>
class BtreeNode 
{
    private:
    T *keys;
    int t;
    BtreeNode **c;
    int n;
    bool leaf;

    public:
    BtreeNode(int t1, bool leaf1) 
    {
        t = t1;
        leaf = leaf1;
        keys = new T[2 * t - 1];
        c = new BtreeNode *[2 * t];
        n = 0;
    }

    void traverse() 
    {
        int i;
        for (i = 0; i < n; i++) 
        {
            if (leaf == false)
                c[i]->traverse();
            cout << " " << keys[i];
        }
        if (leaf == false)
            c[i]->traverse();
    }

    void InsertNonFull(T k) 
    {
        int i = n - 1;
        if (leaf == true) 
        {
            while (i >= 0 && keys[i] > k) 
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            n = n + 1;
        } 
        else 
        {
            while (i >= 0 && keys[i] > k)
                i--;
            if (c[i + 1]->n == 2 * t - 1) 
            {
                SplitChild(i + 1, c[i + 1]);
                if (keys[i + 1] < k)
                    i++;
            }
            c[i + 1]->InsertNonFull(k);
        }
    }

    void SplitChild(int i, BtreeNode *y) 
    {
        BtreeNode *z = new BtreeNode(y->t, y->leaf);
        z->n = t - 1;
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];
        if (y->leaf == false) 
        {
            for (int j = 0; j < t; j++)
                z->c[j] = y->c[j + t];
        }
        y->n = t - 1;
        for (int j = n; j >= i + 1; j--)
            c[j + 1] = c[j];
        c[i + 1] = z;
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        n = n + 1;
    }

    BtreeNode *search(T k) 
    {
        int i = 0;
        while (i < n && k > keys[i])
            i++;
        if (keys[i] == k)
            return this;
        if (leaf == true)
            return NULL;
        return c[i]->search(k);
    }


    template <typename U>
    friend class Btree;
};

template <typename T>
class Btree 
{
private:
    BtreeNode<T> *root;
    int t;

public:
    Btree(int t1) 
    {
        root = NULL;
        t = t1;
    }

    void traverse() 
    {
        if (root != NULL)
            root->traverse();
    }

    BtreeNode<T> *search(T k) 
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(T k) 
    {
        if (root == NULL) 
        {
            root = new BtreeNode<T>(t, true);
            root->keys[0] = k;
            root->n = 1;
        } 
        else 
        {
            if (root->n == 2 * t - 1) 
            {
                BtreeNode<T> *s = new BtreeNode<T>(t, false);
                s->c[0] = root;
                s->SplitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->c[i]->InsertNonFull(k);
                root = s;
            } 
            else
                root->InsertNonFull(k);
        }
    }

    void printTree() const 
    {
        if (root != NULL)
            root->printTree();
    }
};

int main() 
{
    int t, choice;
    cout << "Enter the degree of B-tree: ";
    cin >> t;
    Btree<int> btree(t);

    do 
    {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Traverse\n";
        cout << "3. Search\n";
        cout << "4. Print Tree\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1: 
            int key;
            cout << "Enter the key to insert: ";
            cin >> key;
            btree.insert(key);
            break;
        case 2:
            cout << "B-tree traversal: ";
            btree.traverse(); 
            cout << endl;
            break;
        case 3: 
            int key;
            cout << "Enter the key to search: ";
            cin >> key; 
            BtreeNode<int> *result = btree.search(key); 
            if (result != NULL)
                cout << "Key " << key << " found in the B-tree.\n";
            else
                cout << "Key " << key << " not found in the B-tree.\n";
            break;
        case 4:
            cout << "B-tree print:\n";
            btree.printTree(); 
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}