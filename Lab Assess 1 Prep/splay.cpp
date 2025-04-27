#include<iostream>
#include<string>
using namespace std;
template<class T>
class SplayTree
{
    private:
        struct BinaryNode
        {
            T element;
            BinaryNode *left;
            BinaryNode *right;
            BinaryNode(const T &e = T(), BinaryNode *lt = nullptr, BinaryNode *rt = nullptr)
                : element(e), left(lt), right(rt) {}
        };

        BinaryNode *root;
        BinaryNode *nullNode;

        void insertNode(const T &x)
        {
            static BinaryNode* newNode = nullptr;
            if(newNode == nullptr)
                newNode = new BinaryNode;
            newNode->element = x;
            if(root==nullNode)
            {
                newNode->left = newNode->right = nullNode;
                root = newNode;
            }            
            else
            {
                splay(x,root);
                if(x<root->element)
                {
                    newNode->left = root->left;
                    newNode->right = root;
                    root->left = nullNode;
                    root = newNode;
                }
                else if(x>root->element)
                {
                    newNode->right = root->right;
                    newNode->left = root;
                    root->right = nullNode;
                    root = newNode;
                }
                else
                    return;
            }
            newNode = nullptr;
        }

        bool containsNode(const T &x)
        {
            if(root==nullNode)
                return false;
            splay(x,root);
            return root->element==x;
        }

        void removeNode(const T &x)
        {
            if(!containsNode(x))
                return;
            BinaryNode *newTree;
            if(root->left == nullNode)
                newTree = root->right;
            else
            {
                newTree = root->left;
                splay(x,newTree);
                newTree->right = root->right;
            }
            delete root;
            root = newTree;
        }

        void makeEmpty(BinaryNode *&t)
        {
            if(t!=nullNode)
            {
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
        }

        BinaryNode* findMin(BinaryNode *t) const
        {
            if(t!=nullNode)
            {
                while(t->left!=nullNode)
                    t = t->left;
            }
            return t;
        }

        BinaryNode* findMax(BinaryNode *t) const
        {
            if(t!=nullNode)
            {
                while(t->right!=nullNode)
                    t = t->right;
            }
            return t;
        }

        void printTree(BinaryNode *t, int level) const
        {
            if(t==nullNode)
                return;
            printTree(t->right,level+1);
            for(int i=0;i<level;i++)
                cout<<"    ";
            cout<<t->element<<endl;
            printTree(t->left,level+1);
        }

        void srl(BinaryNode *&k2)
        {
            BinaryNode *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        void srr(BinaryNode *&k2)
        {
            BinaryNode *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2 = k1;
        }

        void splay(const T &x, BinaryNode *&t)
        {
            BinaryNode *leftMax, *rightMin;
            static BinaryNode header;
            header.left = header.right = nullNode;
            leftMax = rightMin = &header;
            nullNode->element = x;
            while(true)
            {
                if(x<t->element)
                {
                    if(x<t->left->element)
                        srl(t);
                    if(t->left == nullNode)
                        break;
                    rightMin->left = t;
                    rightMin = t;
                    t = t->left;
                }
                else if(x>t->element)
                {
                    if(x>t->right->element)
                        srr(t);
                    if(t->right == nullNode)
                        break;
                    leftMax->right = t;
                    leftMax = t;
                    t = t->right;
                }
                else
                {
                    break;
                }    
            }
            leftMax->right = t->left;
            rightMin->left = t->right;
            t->left = header.right;
            t->right = header.left;
        }

    public:
        SplayTree()
        {
            nullNode = new BinaryNode;
            nullNode->left = nullNode->right = nullNode;
            root = nullNode;
        }
       ~SplayTree()
        {
            makeEmpty(root);
            delete nullNode;
        }

        void insert(const T &x)
        {
            insertNode(x);
        }
        
        void remove(const T &x)
        {
            removeNode(x);
        }

        bool contains(const T &x)
        {
            return containsNode(x);
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
            cout<<"\nSplay Tree Structure\n";
            printTree(root,0);
        }

};
int main()
{
    SplayTree<int> tree;
    int value, choice;
    do
    {
        cout<<"\n-----AVL Menu-----";
        cout<<"\n1.Insert";
        cout<<"\n2.Remove";
        cout<<"\n3.Search";
        cout<<"\n4.Find Min";
        cout<<"\n5.Find Max";
        cout<<"\n6.Print Tree";
        cout<<"\n0.Exit";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter value to insert : ";
                cin>>value;
                tree.insert(value);
                tree.printTree();
                break;
            case 2:
                cout<<"\nEnter value to remove : ";
                cin>>value;
                tree.remove(value);
                tree.printTree();
                break;
            case 3:
                cout<<"\nEnter value to search : ";
                cin>>value;
                if(tree.contains(value))
                    cout<<"\nFound";
                else    
                    cout<<"\nNot Found";
                break;
            case 4:
                cout<<"\nMinimum Value = "<<tree.findMin();
                break;
            case 5:
                cout<<"\nMaximum Value = "<<tree.findMax();
                break;
            case 6:
                tree.printTree();
                break;
            case 0:
                cout<<"\nExiting the program";
                return 0;
            default:
                cout<<"\nInvalid Choice";
    }
    }while(choice!=0);
}
