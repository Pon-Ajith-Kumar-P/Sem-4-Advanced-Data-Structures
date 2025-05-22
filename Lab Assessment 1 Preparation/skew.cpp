#include<iostream>
using namespace std;
template<class T>
class SkewHeap
{
    private:
        struct SkewNode
        {
            T element;
            SkewNode *left;
            SkewNode *right;
            SkewNode(const T &e,SkewNode *lt = nullptr,SkewNode *rt = nullptr)
                : element(e), left(lt), right(rt) {}
        };
        SkewNode *root;

        void makeEmpty(SkewNode *&t)
        {
            if(!t)
                return;
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }

        SkewNode *clone(SkewNode *t)
        {
            if(!t)
                return nullptr;
            return new SkewNode(t->element,clone(t->left),clone(t->right));
        }

        SkewNode *merge(SkewNode *h1,SkewNode *h2)
        {
            if(!h2)
                return h1;
            if(!h1)
                return h2;
            if(h1->element > h2->element)
                swap(h1,h2);
            h1->right = merge(h1->right,h2);
            swap(h1->left,h1->right);
            return h1;
        }

        void printTree(SkewNode *t,int level) const
        {
            if(!t)
                return;
            printTree(t->right,level+1);
            for(int i=0;i<level;i++)
                cout<<"      ";
            cout<<t->element<<endl;
            printTree(t->left, level+1);
        }


    public:
        SkewHeap()
        {
            root = nullptr;
        }
        SkewHeap(const SkewHeap &rhs)
        {
            root = clone(rhs.root);
        }
        ~SkewHeap()
        {
            makeEmpty(root);
        }
        void insert(const T &x)
        {
            root = merge(new SkewNode(x), root);
        }
        const T *findMin() const
        {
            if(root==nullptr)
            {
                cout<<"\nEmpty Heap";
                return nullptr;
            }
            return &root->element;
        }

        void deleteMin()
        {
            if(root==nullptr)
            {
                cout<<"\nEmpty Heap";
                return;
            }
            SkewNode *old = root;
            root = merge(root->left,root->right);
            delete old;
        }

        void deleteMin(T &minItem)
        {
            const T *minVal = findMin();
            if(minVal)
            {
                minItem = *minVal;
                deleteMin();
            }
        }

        void printTree() const
        {
            cout<<"\nLeftist Heap Structure\n";
            printTree(root,0);
        }
};

int main()
{
    SkewHeap<int> heap;
    int choice,value;
    do
    {
        cout<<"\n---Skew Heap Menu";
        cout<<"\n1. Insert";
        cout<<"\n2. Find Min";
        cout<<"\n3. Delete Min";
        cout<<"\n4. Delete";
        cout<<"\n5. Print Tree";
        cout<<"\n6. Copy Heap";
        cout<<"\n0. Exit";
        cout<<"\nEnter your choice : ";
        cin>>choice;
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
                const int *minVal = heap.findMin();
                if(minVal)
                    cout<<"\nMinimum Value = "<<*minVal;
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
                cout<<"\nDeleted Min Element = "<<minVal;
                heap.printTree();
            }
            break;

            case 5:
                heap.printTree();
                break;
            
            case 6:
            {
                SkewHeap<int> heapCopy(heap);
                heapCopy.printTree();
            }
            break;

            case 0:
                cout<<"\nExit";
                break;
            
            default:
                cout<<"\nInvalid Choice";
        }
    }while(choice!=0);
}