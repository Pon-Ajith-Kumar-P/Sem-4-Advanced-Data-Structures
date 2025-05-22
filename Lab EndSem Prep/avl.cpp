#include<iostream>
#include<algorithm>
using namespace std;
template<class T>
class AVL
{
    private:
        struct AvlNode 
        {
            T element;
            AvlNode *left;
            AvlNode *right;
            int height;
            AvlNode(const T &e,AvlNode *lt=nullptr,AvlNode *rt=nullptr,int ht=0)
                : element(e), left(lt), right(rt), height(ht) {}
        };
        AvlNode *root;

        void makeEmpty(AvlNode *&t)
        {
            if(!isEmpty(t))
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
                t=nullptr;
            }
        }

        void insert(const T &x,AvlNode *&t)
        {
            if(isEmpty(t))
                t = new AvlNode(x);
            else if(x<t->element)
                insert(x,t->left);
            else if(x>t->element)
                insert(x,t->right);
            else
                {;}
            t->height = max(height(t->left),height(t->right))+1;
            balance(t);
        }

        void remove(const T &x,AvlNode *&t)
        {
            if(isEmpty(t))
                return;
            else if(x<t->element)
                remove(x,t->left);
            else if(x>t->element)
                remove(x,t->right);
            else if(t->left!=nullptr && t->right!=nullptr)
            {
                t->element = findMin(t->right)->element;
                remove(t->element,t->right);
            }
            else
            {
                AvlNode *old = t;
                t = (t->left != nullptr)?t->left:t->right;
                delete old;
            }
            if(!isEmpty(t))
            {
                t->height = max(height(t->left),height(t->right))+1;
                balance(t);    
            }
        }

        bool search(const T &x,AvlNode *t) const
        {
            if(isEmpty(t))
                return false;
            else if(x<t->element)
                return search(x,t->left);
            else if(x>t->element)
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

         void familyDetails(const T &x,AvlNode *t) const
         {
            if(isEmpty(t))
            {
                cout<<"\nNo element in the tree";
                return;
            }
            AvlNode *gp = nullptr;
            AvlNode *p = nullptr;
            AvlNode *curr = t;

            while(curr && curr->element!=x)
            {
                gp = p;
                p = curr;
                curr = (x < curr->element) ? curr->left : curr->right; 
            }

            if(curr == nullptr)
            {
                cout<<"\nNo Element found in the tree";
                return;
            }

            cout<<"\nElement : "<<curr->element;
            cout << "\nGrand Parent : " << ((gp) ? gp->element : -1);
            cout << "\nParent : " << ((p) ? p->element : -1);
            cout<<"\nSiblings : "<<(p && p->left && p->right==curr? p->left->element 
                                : (p && p->left==curr && p->right ? p->right->element : -1));
            
            cout<<"\nChildren : ";
            if(curr->left) cout<<curr->left->element<<" ";
            if(curr->right) cout<<curr->right->element<<" ";
            if(!curr->left && !curr->right) cout<<"-1";

            cout<<"\nGrand Children : ";
            if(curr->left)
            {
                if(curr->left->left) cout<<curr->left->left->element<<" ";
                if(curr->left->right) cout<<curr->left->right->element<<" ";
            }
            if(curr->right)
            {
                if(curr->right->left) cout<<curr->right->left->element<<" ";
                if(curr->right->right) cout<<curr->right->right->element<<" ";
            }
            if(!curr->left && !curr->right)
            {
                cout<<"-1";
            }

         }

         void inorderTree(AvlNode *t) const
         {
            if(!isEmpty(t))
            {
                inorderTree(t->left);
                cout<<t->element<<" ";
                inorderTree(t->right);
            }
         }

         void printTree(AvlNode *t,int level) const
         {
            if(isEmpty(t))
                return;
            printTree(t->right,level+1);
            for(int i=0;i<level;i++)
                cout<<"      ";
            int bal = height(t->left) - height(t->right);
            cout<<t->element<<"("<<bal<<")"<<endl;
            printTree(t->left,level+1);
         }

         int height(AvlNode *t) const
         {
            return ((t == nullptr) ? -1 : t->height);
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
            k2->height = max(height(k2->left),height(k2->right))+1;
            k1->height = max(height(k1->left),k2->height)+1;
            k2 = k1;
         }

         void srr(AvlNode *&k2)
         {
            AvlNode *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2->height = max(height(k2->left),height(k2->right))+1;
            k1->height = max(height(k1->right),k2->height)+1;
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

    public:
        AVL()
        {
            root = nullptr;
        }
        ~AVL()
        {
            makeEmpty(root);
        }
        bool isEmpty(AvlNode *t) const
        {
            return (t==nullptr);
        }
        void insert(const T &x) 
        {
            insert(x,root);
        }
        void remove(const T &x) 
        {
            remove(x,root);
        }
        bool search(const T &x) 
        {
            return search(x,root);
        }
        const T &findMin() const
        {
            return findMin(root)->element;
        }
        const T &findMax() const
        {
            return findMax(root)->element;
        }
        void inorderTree() const
        {
            inorderTree(root);
        }
        void printTree() const
        {
            cout<<"\n--- AVL Tree Structure ---\n";
            printTree(root,0);
        }
        void familyDetails(const T &x)
        {
            familyDetails(x,root);
        }

};
int main()
{
    AVL<int> tree;
    int choice, value;
    do
    {
        cout<<"\n--- AVL Tree Menu ---";
        cout<<"\n1. Insert";
        cout<<"\n2. Remove";
        cout<<"\n3. Search";
        cout<<"\n4. Find Min";
        cout<<"\n5. Find Max";
        cout<<"\n6. Inorder";
        cout<<"\n7. Print Tree";
        cout<<"\n8. Family Details";
        cout<<"\n0. Exit";
        cout<<"\nEnter your choice : ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter a value to insert : ";
                cin>>value;
                tree.insert(value);
                tree.printTree();
                break;
            case 2:
                cout<<"\nEnter a value to remove : ";
                cin>>value;
                tree.remove(value);
                tree.printTree();
                break;
            case 3:
                cout<<"\nEnter a value to search : ";
                cin>>value;
                if(tree.search(value))
                    cout<<"\nFound";
                else
                    cout<<"\nNot Found";
                break;
            case 4:
                cout<<"\nMinimum Element = "<<tree.findMin();
                break;
            case 5:
                cout<<"\nMaximum Element = "<<tree.findMax();
                break;
            case 6:
                cout<<"\nInorder Traversal : ";
                tree.inorderTree();
                break;
            case 7:
                cout<<"\nPrint Tree : ";
                tree.printTree();
                break;
            case 8:
                cout<<"\nFamily Details\n";
                cout<<"\nEnter a value to get details : ";
                cin>>value;
                tree.familyDetails(value);
                break;
            case 0:
                cout<<"\nExit";
                return 0;
            default:
                cout<<"\nInvalid Choice";
        }
    } while (choice != 0);
}