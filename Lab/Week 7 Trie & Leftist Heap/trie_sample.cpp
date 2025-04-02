#include <iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26];
    bool flagEOW;

    TrieNode() {
        flagEOW = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    bool deleteHelper(TrieNode* node, const string& word, int depth) 
    {
        if (!node) return false;

        if (depth == word.size()) {
            if (!node->flagEOW) return false;
            node->flagEOW = false;
            for (int i = 0; i < 26; i++)
                if (node->children[i]) return false;
            return true;
        }

        int index = word[depth] - 'a';
        if (deleteHelper(node->children[index], word, depth + 1)) {
            delete node->children[index];
            node->children[index] = nullptr;
            return !node->flagEOW && isEmpty(node);
        }
        return false;
    }

    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++)
            if (node->children[i]) return false;
        return true;
    }

    void printTrieNode(TrieNode* node, string prefix) {
        if (node->flagEOW) cout << prefix << endl;
        for (int i = 0; i < 26; i++) {
            if (node->children[i])
                printTrieNode(node->children[i], prefix + char(i + 'a'));
        }
    }

    void suggest(TrieNode* node, string prefix, vector<string>& results) {
        if (node->flagEOW) results.push_back(prefix);
        for (int i = 0; i < 26; i++) {
            if (node->children[i])
                suggest(node->children[i], prefix + char(i + 'a'), results);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index])
                node->children[index] = new TrieNode();
            node = node->children[index];
        }
        node->flagEOW = true;
    }

    void remove(const string& word) {
        deleteHelper(root, word, 0);
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) return false;
            node = node->children[index];
        }
        return node->flagEOW;
    }

    bool valid_prefix(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index]) return false;
            node = node->children[index];
        }
        return true;
    }

    vector<string> auto_suggest(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index]) return {};
            node = node->children[index];
        }
        vector<string> suggestions;
        suggest(node, prefix, suggestions);
        return suggestions;
    }

    void printTrie() {
        printTrieNode(root, "");
    }
};

int main() {
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

        switch (choice) {
            case 1:
                cout << "Enter word to insert: ";
                cin >> word;
                trie.insert(word);
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                cout << (trie.search(word) ? "Found" : "Not Found") << endl;
                break;
            case 3:
                cout << "Enter word to delete: ";
                cin >> word;
                trie.remove(word);
                break;
            case 4:
                cout << "Trie contents:\n";
                trie.printTrie();
                break;
            case 5:
                cout << "Enter prefix to check: ";
                cin >> word;
                cout << (trie.valid_prefix(word) ? "Yes" : "No") << endl;
                break;
            case 6:
                cout << "Enter prefix for suggestions: ";
                cin >> word;
                {
                    vector<string> suggestions = trie.auto_suggest(word);
                    for (const string& w : suggestions) {
                        cout << w << endl;
                    }
                }
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
