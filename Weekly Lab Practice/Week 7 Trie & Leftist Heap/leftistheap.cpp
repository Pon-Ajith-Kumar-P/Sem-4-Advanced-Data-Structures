#include<iostream>
using namespace std;

template<class T>
class LeftistHeap
{
    struct LeftistNode
    {
        T element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const T &e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0)
            : element(e),left(lt),right(rt),npl(np) {}
    };

    LeftistNode *root;

    void reclaim(LeftistNode *t)
    {
        if(t!=nullptr)
        {
            reclaim(t->left);
            reclaim(t->right);
            delete t;
            t = nullptr;
        }
    }

    void merge(LeftistNode &rhs)
    {
        if(this==rhs)
            return;
        root = merge(root,rhs.root);
        rhs.root = nullptr;
    }

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {
        if(h1==NULL)
            return h2;
        else if(h2==NULL)
            return h1;
        else if(h1->element < h2->element)
            return merge1(h1,h2);
        else
            return merge1(h2,h1);
    }

    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2)
    {
        if(h1->left==NULL)
            h1->left = h2;
        else{
            h1->right = merge(h1->right,h2);
            if(h1->right==nullptr || (h1->left->npl < h1->right->npl))
                swapchild(h1);
            h1->npl = (h1->right ? h1->right->npl : -1) + 1;
        }
        return h1;
    }

    void swapchild(LeftistNode *t)
    {
        LeftistNode *temp = t->left;
        t->left = t->right;
        t->right = temp;
    }

    LeftistNode *clone(LeftistNode *t) const{
        if(t==nullptr)
            return nullptr;
        return new LeftistNode(t->element,clone(t->left),clone(t->right),t->npl);
    }

    void printTreeHelper(LeftistNode *t, int level=0) const
    {
        if(t==nullptr)
            return;
        printTreeHelper(t->right,level+1);
        for(int i=0;i<level;i++)
            cout<<"    ";
        cout<<t->element<<endl;
        printTreeHelper(t->left,level+1);
    }

    public:
    LeftistHeap()
    {
        root = nullptr;
    }
    ~LeftistHeap()
    {
        reclaim(root);
    }
    void insert(const T &x)
    {
        root = merge(new LeftistNode(x), root);
    }
    void printTree()
    {
        if(root==nullptr)
        {
            cout<<"Empty"<<endl;
            return;
        }
        printTreeHelper(root,0);
    }
    void deleteMin()
    {
        if(root==nullptr)
            return;
        LeftistNode *old = root;
        root = merge(root->left,root->right);
        delete old;
        old = nullptr;
    }

    void deleteMin(const T &minItem)
    {
        const T *minPtr = findMin();
        if(minPtr==nullptr)
            return;
        minItem = *minPtr;
        deleteMin();
    }

    const T *findMin() const
    {
        if(root==nullptr)
            return nullptr;
        return &root->element;
    }
    
};
int main()
{
    LeftistHeap<int> tree;

}