#ifndef AVL_H
#define AVL_H
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
      AvlNode(const T &e, AvlNode *lt, AvlNode *rt, int ht = 0)
          : element(e), left(lt), right(rt), height(ht) {}
    };
    AvlNode *root;
    
    void insert(const T &x, AvlNode *&t)
    {
        if (isEmpty(t))
            t = new AvlNode(x, nullptr, nullptr, 0);
        else if (x < t->element)
            insert(x, t->left);
        else if (x > t->element)
            insert(x, t->right);
        else
            { ; }
        balance(t);
    }

    void remove(const T &x, AvlNode *&t)
    {
        if (isEmpty(t))
            return;
        else if (x < t->element)
            remove(x, t->left);
        else if (x > t->element)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    void makeEmpty(AvlNode *&t)
    {
        if (!isEmpty(t))
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
    }

    bool isEmpty(AvlNode *t) const
    {
        return t == nullptr;
    }

    AvlNode *findMin(AvlNode *t) const
    {
        if (!isEmpty(t))
        {
            while (t->left != nullptr)
            {
                t = t->left;
            }
        }
        return t;
    }

    AvlNode *findMax(AvlNode *t) const
    {
        if (!isEmpty(t))
        {
            while (t->right != nullptr)
            {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const T &x, AvlNode *t) const
    {
        if (isEmpty(t))
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (x > t->element)
            return contains(x, t->right);
        else
            return true;
    }

    void printTree(AvlNode *t, int level) const
    {
        if (isEmpty(t))
            return;
        printTree(t->right, level + 1);
        for (int i = 0; i < level; i++)
            cout << "    ";
        cout << t->element << "(" << height(t->left) - height(t->right) << ")" << endl;
        printTree(t->left, level + 1);
    }

    int height(AvlNode *t) const
    {
        return (t == nullptr) ? -1 : t->height;
    }

    void balance(AvlNode *&t)
    {
        if (isEmpty(t))
            return;
        else if (height(t->left) - height(t->right) > 1)
        {
            if (height(t->left->left) >= height(t->left->right))
                srl(t);
            else
                drl(t);
        }
        else if (height(t->right) - height(t->left) > 1)
        {
            if (height(t->right->right) >= height(t->right->left))
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
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height);
        k2 = k1;
    }

    void srr(AvlNode *&k2)
    {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->right), k2->height);
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

    void getdetails(const T &x, AvlNode *t) const
    {
        cout << endl;
        cout << "Element : " << t->element << endl;

        if (t->left == nullptr)
            cout << "Children : " << t->right->element;
        else if (t->right == nullptr)
            cout << "Children : " << t->left->element;
        else
            cout << "Children : " << t->left->element << " " << t->right->element;
    }

  public:
    AVL() : root(nullptr) {}
    ~AVL() 
	{ 
		makeEmpty(root); 
	}

    void insert(const T &x) 
	{ 
		insert(x, root); 
	}
	void remove(const T &x) 
	{ 
		remove(x, root); 
	}
    
	const T &findMin() const 
	{ 
		return findMin(root)->element; 
	}
    const T &findMax() const 
	{ 
		return findMax(root)->element; 
	}
    
	bool contains(const T &x) const 
	{ 
		return contains(x, root); 
	}
    
	void printTree() const 
	{
		 printTree(root, 0); 
	}
    
	void getdetails(const T &x) const 
	{ 
		getdetails(x, root); 
	}
};

#endif // AVL_H
