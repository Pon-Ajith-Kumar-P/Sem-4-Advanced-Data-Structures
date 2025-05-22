#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class AvlTree
{
    private:
        struct AvlNode
        {
            T element;
            AvlNode *left;
            AvlNode *right;
            int height;

            AvlNode(const T &e, AvlNode *lt = NULL, AvlNode *rt = NULL, int h = 0)
                : element(e), left(lt), right(rt), height(h) {}
        };
        AvlNode *root;

        void makeEmpty(AvlNode *&t)
        {
            if(t!=nullptr)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
        }

        void insert(const T &x,AvlNode *&t)
        {
            if(isEmpty(t))
                t = new AvlNode(x);
            else if(x < t->element)
                insert(x,t->left);
            else if(x > t->element)
                insert(x,t->right);
            t->height = max(height(t->left),height(t->right)) + 1;
            balance(t);
        }

        void remove(const T &x,AvlNode *&t)
        {
            if(isEmpty(t))
                return;
            else if(x < t->element)
                remove(x,t->left);
            else if(x > t->element)
                remove(x,t->right);
            else if(t->left!=nullptr && t->right!=nullptr)
            {
                t->element = findMin(t->right)->element;
                remove(t->element,t->right);
            }
            else
            {
                AvlNode *old = t;
                t = (t->left == nullptr) ? t->right : t->left;
                delete old;
            }
            if(!isEmpty(t))
            {
                t->height = max(height(t->left),height(t->right)) + 1;
                balance(t);    
            }
        }

        bool search(const T &x,AvlNode *t) const
        {
            if(isEmpty(t))
                return false;
            else if(x < t->element)
                return search(x,t->left);
            else if(x > t->element)
                return search(x,t->right);
            else
                return true;
        }

        AvlNode *findMin(AvlNode *t) const
        {
            if(!isEmpty(t))
            {
                while(!isEmpty(t->left))
                    t = t->left;
            }
            return t;
        }

        AvlNode *findMax(AvlNode *t) const
        {
            if(!isEmpty(t))
            {
                while(!isEmpty(t->right))
                    t = t->right;
            }
            return t;
        }

        int height(AvlNode *t) const
        {
            return (t==nullptr)?-1:t->height;
        }

        void balance(AvlNode *&t)
        {
            if(isEmpty(t))
                return;
            else if(height(t->left) - height(t->right) > 1)
            {
                if(height(t->left->left) >= height(t->left->right))
                    srl(t);
                else
                    drl(t);
            }
            else if(height(t->right) - height(t->left) > 1)
            {
                if(height(t->right->right) >= height(t->right->left))
                    srr(t);
                else
                    drr(t);
            }
        }

        void srl(AvlNode *&k2)
        {
            AvlNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2->height = max(height(k2->left),height(k2->right)) + 1;
            k1->height = max(height(k1->left),k2->height) + 1;
            k2 = k1;
        }

        void srr(AvlNode *&k2)
        {
            AvlNode *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->height = max(height(k2->left),height(k2->right)) + 1;
            k1->height = max(height(k1->right),k2->height) + 1;
            k2 = k1;
        }

        void drl(AvlNode *&k3)
        {
            srr(k3->left);
            srl(k3);
        }

        void drr(AvlNode *&k3)
        {
            srl(k3->right);
            srr(k3);
        }

        void printTree(AvlNode *t,int level) const
        {
            if(!t)
                return;
            printTree(t->right,level+1);
            for(int i=0;i<level;i++)
                cout<<"      ";
            int bal = height(t->left) - height(t->right);
            cout<<t->element<<"("<<bal<<")"<<endl;
            printTree(t->left, level+1);
        }

        void familyDetails(const T &x, AvlNode *t) const
        {
            if(isEmpty(t))
            {
                cout<<'\nNo elements in the tree';
                return;
            }
            AvlNode *gp = nullptr;
            AvlNode *p = nullptr;
            AvlNode *curr = t;

            while(curr && curr->element!=x)
            {
                gp = p;
                p = curr;
                curr = (x<curr->element)? curr->left : curr->right;
            }

            if(!curr)
            {
                cout<<"\nElement not found in the tree";
                return;
            }

            cout<<"\n\nElement\n"<<curr->element;
            cout<<"\n\nGrandParent\n"<<(gp)? gp->element : -1;
            cout<<"\n\nParent\n"<<(p)? p->element :-1;
            cout<<"\n\nSibling\n"<<(p && p->left && p->right==curr ? p->left->element 
                                    : (p && p->right && p->left==curr ? p->right->element : -1));
            cout<<"\n\nChildren\n";
            if(curr->left)  cout<<curr->left->element<<endl;
            if(curr->right) cout<<curr->right->element;
            if(!curr->left && !curr->right) cout<<"-1";

            cout<<"\n\nGrand Children\n";
            if(curr->left)  
            {
                if(curr->left->left)
                    cout<<curr->left->left->element<<endl;
                if(curr->left->right)
                    cout<<curr->left->right->element<<endl;
            }
            if(curr->right)
            {
                if(curr->right->left)
                    cout<<curr->right->left->element<<endl;
                if(curr->right->right)
                    cout<<curr->right->right->element<<endl;
            } 
            if(!curr->left && !curr->right)
            {
                cout<<"-1";
            }
        }

    public:
        AvlTree()
        {
            root = nullptr;
        }
        ~AvlTree()
        {
            makeEmpty(root);
        }
        bool isEmpty(AvlNode *t) const
        {
            return t==nullptr;
        }
        void insert(const T &x)
        {
            insert(x,root);
        }
        void remove(const T &x)
        {
            remove(x,root);
        }
        bool search(const T &x) const
        {
            return search(x,root);
        }
        T &findMin() const
        {
            return findMin(root)->element;
        }
        T &findMax() const
        {
            return findMax(root)->element;
        }
        void printTree() const
        {
            printf("\nAVL Tree Structure\n");
            printTree(root,0);
        }
        void familyDetails(const T &x) const
        {
            familyDetails(x,root);
        }

};

int main()
{
    AvlTree<int> tree;
    int choice, value;
    do
    {
        cout<<"\n-----AVL Menu-----";
        cout<<"\n1.Insert";
        cout<<"\n2.Remove";
        cout<<"\n3.Search";
        cout<<"\n4.Find Min";
        cout<<"\n5.Find Max";
        cout<<"\n6.Print Tree";
        cout<<"\n7. Family Details";
        cout<<"\n0.Exit";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter a value to insert : ";
                cin>>value;
                cout<<"\nBefore Insertion";
                tree.printTree();
                tree.insert(value);
                cout<<"\nAfter Insertion";
                tree.printTree();
                break;
            case 2:
                cout<<"\nEnter a value to remove : ";
                cin>>value;
                cout<<"\nBefore Deletion";
                tree.printTree();
                tree.remove(value);
                cout<<"\nAfter Deletion";
                tree.printTree();
                break;
    
            case 3:
                cout<<"\nEnter a value to search : ";
                cin>>value;
                if(tree.search(value))
                    cout<<"\nSearch Found";
                else
                    cout<<"\nSearch Not Found";
                break;
    
            case 4:
                cout<<"\nMinimum Element = "<<tree.findMin();
                break;
    
            case 5:
                cout<<"\nMaximum Element = "<<tree.findMax();
                break;
            
            case 6:
                tree.printTree();
                break;

            case 7:
                cout<<"\nEnter a value to get Family Details : ";
                cin>>value;
                tree.familyDetails(value);
                break;
            
            case 0:
                cout<<"\nExit the program";
                return 0;
    
            default:
                cout<<"\nInvalid Choice";
        }
    } while (choice!=0);
    

}