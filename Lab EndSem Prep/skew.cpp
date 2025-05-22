#include<iostream>
using namespace std;
template<class T>
class Skew
{
    struct SkewNode
    {
        T element;
        SkewNode *left;
        SkewNode *right;
        SkewNode(const T &e, SkewNode *lt = nullptr, SkewNode *rt = nullptr)
            : element(e),left(lt),right(rt) {}
    };
    SkewNode *root;

    void reclaimMemory(SkewNode *&t)
    {
        if(t!=nullptr)
        {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
            t=nullptr;
        }
    }

    SkewNode *merge(SkewNode *h1,SkewNode *h2)
    {
        if(!h1)
            return h2;
        if(!h2)
            return h1;
        if(h1->element > h2->element)
            swap(h1,h2);
        h1->right = merge(h1->right,h2);
        swap(h1->left,h1->right);
        return h1;
    }

    SkewNode* clone(SkewNode *t)
    {
        if(!t)
            return nullptr;
        return new SkewNode(t->element,clone(t->left),clone(t->right));
    }

    void printTree(SkewNode *t,int level) const
    {
       if(t==nullptr)
           return;
       printTree(t->right,level+1);
       for(int i=0;i<level;i++)
           cout<<"      ";
        cout<<t->element<<endl;
       printTree(t->left,level+1);
    }


    public:
    Skew()
    {
        root = nullptr;
    }
    Skew(const Skew &rhs)
    {
        root = clone(rhs.root);
    }
    ~Skew()
    {
        reclaimMemory(root);
    }
    void insert(const T &x)
    {
        root = merge(new SkewNode(x),root);
    }
    const T *findMin() const
    {
        if(root==nullptr)
            return nullptr;
        return &root->element;
    }
    void deleteMin()
    {
        if(root==nullptr)
            return;
        SkewNode *oldRoot = root;
        root = merge(root->left,root->right);
        delete oldRoot;
    }
    void deleteMin(T &minItem)
    {
        const int *minPtr = findMin();
        if(minPtr)
        {
            minItem = *minPtr;
            deleteMin();
        }
    }

    void printTree() const
    {
        printTree(root,0);
    }

    
};
int main()
{
    Skew<int> heap;
    int choice, value;
    do
    {
        cout<<"\n--- Leftist Tree Menu ---";
        cout<<"\n1. Insert";
        cout<<"\n2. Find Min";
        cout<<"\n3. Delete Min";
        cout<<"\n4. Delete";
        cout<<"\n5. Copy Heap";
        cout<<"\n6. Print Tree";
        cout<<"\n0. Exit";
        cout<<"\nEnter your choice : ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter a value to insert : ";
                cin>>value;
                heap.insert(value);
                heap.printTree();
                break;
            case 2:
                {
                    const int *minPtr = heap.findMin();
                    if(minPtr)
                        cout<<"\nMinimum Element = "<<*minPtr;
                }
                break;
            case 3:
            heap.deleteMin();
            heap.printTree();
            break;
            case 4:
                {
                    int minVal;
                    heap.deleteMin(minVal);
                    cout<<"\nDeleted Min Value = "<<minVal<<endl;
                    heap.printTree();
                }
                break;
            case 5:
                heap.printTree();
                break;
            case 6:
            {
                Skew<int> heapCopy(heap);
                cout<<"\nCopied Heap Structure\n";
                heapCopy.printTree();                
            }
                break;
            case 0:
                cout<<"\nExit";
                return 0;
            default:
                cout<<"\nInvalid Choice";
        }
    } while (choice != 0);
}