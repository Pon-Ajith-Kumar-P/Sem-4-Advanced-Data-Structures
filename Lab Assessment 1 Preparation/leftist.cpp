#include<iostream>
using namespace std;
template<class T>
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
                : element(e), left(lt), right(rt), npl(np) {}
        };

        LeftistNode *root;

        void makeEmpty(LeftistNode *&t)
        {
            if (t == nullptr)
                return;
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }

        LeftistNode* clone(LeftistNode *t) const
        {
            if(!t)
                return nullptr;
            return new LeftistNode(t->element,clone(t->left),clone(t->right),t->npl);
        }

        LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
        {
            if(!h1)
                return h2;
            if(!h2)
                return h1;
            if(h1->element < h2->element)
                return merge1(h1,h2);
            else
                return merge1(h2,h1);
        }

        LeftistNode* merge1(LeftistNode *h1, LeftistNode *h2)
        {
            if(!h1->left)
                h1->left = h2;
            else
            {
                h1->right = merge(h1->right,h2);
                if(h1->left->npl < h1->right->npl)
                    swap(h1->left,h1->right);
                h1->npl = ((h1->right)?h1->right->npl:-1)+1;
            }
            return h1;
        }

        void printTree(LeftistNode *t,int level) const
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
        LeftistHeap()
        {
            root=nullptr;
        }
        LeftistHeap(const LeftistHeap &rhs)
        {
            root = clone(rhs.root);
        }
        ~LeftistHeap()
        {
            makeEmpty(root);
        }
        void insert(const T &x)
        {
            root = merge(new LeftistNode(x),root);
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
            LeftistNode *old = root;
            root = merge(root->left,root->right);
            delete old;
        }
        void deleteMin(T &minItem)
        {
            const int *minPtr = findMin();
            if(minPtr)
            {
                deleteMin();
                minItem = *minPtr;
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
    LeftistHeap<int> heap;
    int choice,value;
    do
    {
        cout<<"\n---Leftist Heap Menu";
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
                    cout<<"\nMinimum Element = "<<*minVal;
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
                    cout<<"\nDeleted Minimum Element = "<<minVal;
                    heap.printTree();
                }
                break;
            case 5:
                heap.printTree();
                break;
            case 6:
            {
                LeftistHeap<int> heapCopy(heap);  // Using copy constructor
                cout << "Copied Heap structure:\n";
                heapCopy.printTree();
        }
                break;
            case 0:
                cout<<"\nExit";
                return 0;
            default:
                cout<<"\nInvalid Choice";
        }
    }while(choice!=0);

}