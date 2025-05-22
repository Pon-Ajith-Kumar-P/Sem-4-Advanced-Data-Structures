#include<iostream>
#include<vector>
using namespace std;
class TrieNode
{
    public:
        bool flag;
        TrieNode *children[26];

        TrieNode()
        {
            flag = false;
            for(int i=0; i<26; i++)
                children[i] = NULL;
        }
        ~TrieNode()
        {
            for(int i=0; i<26; i++)
                delete children[i];

        }        
};
class Trie
{
    private:
        TrieNode *root;

        bool deleteHelper(TrieNode *node,const string &word, int depth)
        {
            if(!node)
                return false;
            if(depth==word.size())
            {
                if(!node->flag)
                    return false;
                node->flag = false;
                for(int i=0;i<26;i++)
                {
                    if(node->children[i])
                        return false;
                }
                return true;
            }
            int index = word[depth] - 'a';
            if(deleteHelper(node->children[index],word,depth+1))
            {
                delete node->children[index];
                node->children[index] = nullptr;
                return isEmpty(node) && (!node->flag);
            }
            return false;
        }

        vector<string> suggest(TrieNode *node, string prefix, vector<string>& res)
        {
            if(node->flag)
                res.push_back(prefix);
            for(int i=0;i<26;i++)
            {
                if(node->children[i])
                    suggest(node->children[i],prefix+(char)(i+'a'),res);
            }
            return res;
        }

        void printTree(TrieNode *node,string prefix)
        {
            if(node->flag)
                cout<<prefix<<endl;
            for(int i=0;i<26;i++)
            {
                if(node->children[i])   
                    printTree(node->children[i],prefix+(char)(i+'a'));
            }
        
        }



    public:
        Trie()
        {
            root = new TrieNode();
        }
        ~Trie() {
            delete root;
        }
        void insert(const string &word)
        {
            TrieNode *node = root;
            for(char ch : word)
            {
                int index = ch - 'a';
                if(!node->children[index])
                    node->children[index] = new TrieNode();
                node = node->children[index];
            }
            node->flag = true;
        }

        bool isEmpty(TrieNode *node)
        {
            for(int i=0;i<26;i++)
            {
                if(node->children[i])
                    return false;
            }
            return true;
        }

        bool search(const string &word)
        {
            TrieNode *node = root;
            for(char ch : word)
            {
                int index = ch - 'a';
                if(!node->children[index])
                    return false;
                node = node->children[index];
            }
            return node->flag;
        }

        bool valid_prefix(const string &word)
        {
            TrieNode *node = root;
            for(char ch : word)
            {
                int index = ch - 'a';
                if(!node->children[index])
                    return false;
                node = node->children[index];
            }
            return true;
        }

        vector<string> auto_suggest(const string &prefix)
        {
            TrieNode *node = root;
            for(char ch : prefix)
            {
                int index = ch - 'a';
                if(!node->children[index])
                    return {};
                node = node->children[index];
            }
            vector<string> suggestions;
            suggest(root,prefix,suggestions);
            return suggestions;
        }

        void remove(const string &word)
        {
            deleteHelper(root,word,0);
        }

        void printTree()
        {
            cout<<"\nTrie Structure\n";
            printTree(root,"");
        }
};

int main()
{
    Trie trie;
    int choice;
    string value;
    do
    {
        cout<<"---Trie Menu---";
        cout<<"\n1. Insert";
        cout<<"\n2. Search";
        cout<<"\n3. Valid Prefix";
        cout<<"\n4. Remove";
        cout<<"\n5. Auto Suggest";
        cout<<"\n6. Print Trie";
        cout<<"\n0. Exit";
        cout<<"\nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"\nEnter a word to insert : ";
                cin>>value;
                trie.insert(value);
                trie.printTree();    
                break;
            case 2:
                cout<<"\nEnter a word to search : ";
                cin>>value;
                if(trie.search(value))
                    cout<<"\nFound";
                else    
                    cout<<"\nNot Found";
                break;
            case 3:
                cout<<"\nEnter a prefix : ";
                cin>>value;
                if(trie.valid_prefix(value))
                    cout<<"\nValid";
                else    
                    cout<<"\nNot Valid";
                break;
            case 4:
                cout<<"\nEnter a word to remove : ";
                cin>>value;
                trie.remove(value);
                trie.printTree();    
                break;
            case 5:
                {
                    
                }
                break;
            case 6:
                trie.printTree();    
                break;
            case 0:
                cout<<"\nExit";
                return 0;
            default:
                cout<<"\nInvalid Choice";        
        }    
    } while (choice!=0);
    return 0;
}