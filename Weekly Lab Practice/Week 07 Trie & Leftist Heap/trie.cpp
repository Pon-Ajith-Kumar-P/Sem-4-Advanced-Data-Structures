#include<iostream>
#include<vector>
using namespace std;
class TrieNode
{
    public:
        TrieNode *children[26];
        bool flag;
        
        TrieNode()
        {
            flag = false;
            for(int i=0;i<26;i++)
                children[i] = nullptr;
        }
};
class Trie
{
    private:
        TrieNode *root;

        bool deleteHelper(TrieNode *node, const string &word, int depth)
        {
            if(!node)
                return false;
           if(word.size() == depth)
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
                return !node->flag && isEmpty(node);
           }
        }

        bool isEmpty(TrieNode *node)
        {
            for(int i=0;i<26;i++)
            {
                if(node->children[i])
                    return false;
            }
        }

        void suggest(TrieNode *node, const string &word, vector<string> &result)
        {
            if(node->flag)
                result.push_back(word);
            for(int i=0;i<26;i++){
                if(node->children[i])   
                    suggest(node,word + char(i+'a'),result);
                    
            }
        }

        void printTreeHelper(TrieNode *node, const string &word)
        {
            if(node->flag)
                cout<<word<<endl;
            for(int i=0;i<26;i++)
            {
                if(node->children[i])
                    printTreeHelper(node,word+char(i+'a'));
            }
        }

    public:
        Trie()
        {
            root = new TrieNode();
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

        void remove(const string &word)
        {
            deleteHelper(root,word,0);
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

        bool validPrefix(const string &word)
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
            suggest(node,prefix,suggestions);
            return suggestions;
        }

        void printTree()
        {
            printTreeHelper(root,"");
        }



};
int main()
{
        Trie trie;
        int choice;
        string word;
        do {
            cout << "\nMenu:\n";
            cout << "1) Insert\n";
            cout << "2) Search\n";
            cout << "3) Delete\n";
            cout << "4) Print Trie\n";
            cout << "5) Valid Prefix\n";
            cout << "6) Auto Suggestion\n";
            cout << "7) Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch(choice)
            {
                case 1:
                    cin>>word;
                    trie.insert(word);
                    break;
                case 2:
                    cin>>word;
                    cout<<(trie.search(word)?"Found":"Not Found");
                    break;
                case 3:
                    cin>>word;
                    trie.remove(word);
                    break;
                case 4:
                    cout<<"Trie Contents: \n";
                    trie.printTree();
                    break;
                case 5:
                    cout<<"Enter prefix : ";
                    cin>>word;
                    cout<<"Valid Prefix : "<<(trie.validPrefix(word)?"Yes":"No");
                    break;
                case 6:
                    cout << "Enter prefix for suggestions: ";
                    cin >> word;
                    {
                        vector<string> suggest = trie.auto_suggest(word);
                        for(const string &w : suggest)
                            cout<<w<<endl;
                    }
                    break;
                    
            }
        }while(choice!=7);
    return 0;
}