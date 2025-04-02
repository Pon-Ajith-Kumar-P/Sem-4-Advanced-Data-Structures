#include<iostream>
using namespace std;
template<class T>
class Splay
{
    private:
        struct BinaryNode
        {
            T element;
            BinaryNode *left;
            BinaryNode *right;
            BinaryNode(const T &e = T(),BinaryNode *lt = nullptr,BinaryNode *rt = nullptr)
                : element(e),left(lt),right(rt) {}
        };
        BinaryNode *root;
        BinaryNode *nullNode;
        void insert(const T &x)
        {
            BinaryNode *newNode = nullptr;
            if(newNode == nullptr)
                return new BinaryNode;
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
                    newNode->left = nullNode;
                    root = newNode;

                }
                else if(x>root->element)
                {
                    newNode->right = root->right;
                    newNode->left = root;
                    newNode->right = nullNode;
                    root = newNode;
                }
            }
            newNode = nullptr;
        }
        void remove(const T &x)
        {
            if(!contains(x))
                return;
            BinaryNode *newTree;
            if(root->left==nullptr)
                newTree = root->right;
            else
            {
                newTree = root->left;
                splay(x,root);
                newTree->right = root->right;
            }
            delete root;
            root = newTree;
        }
        bool contains(const T &x)
        {
            if(root==nullNode)
                return false;
            splay(x);
            return x==root->element;
        }
        T &findMin() const
        {
            BinaryNode *node = root;
            if(node!=nullNode)
            {
                while(node->left!=nullNode)
                    node = node->left;
            }
            return node->element;
        }
        T &findMax() const
        {
            BinaryNode *node = root;
            if(node!=nullNode)
            {
                if(node->right!=nullNode)
                    node = node->right;
            }
        }

        void splay(const T &x,BinaryNode *&t)
        {
            BinaryNode *leftMax, *rightMin;
            static BinaryNode header;
            header.left = header.right = nullNode;
            leftMax = rightMin = &header;
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
                else if (x>t->element)
                {
                    if(x>t->right->element)
                        srr(t);
                    if(t->right==nullNode)
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

        void srl(BinaryNode *&k2)
        {
            BinaryNode *&k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            k2 = k1;
        }

        void srr(BinaryNode *&k2)
        {
            BinaryNode *&k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            k2 = k1;
        }
};
int main()
{
    return 0;
}