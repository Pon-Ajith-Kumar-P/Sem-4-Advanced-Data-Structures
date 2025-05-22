#include <iostream>
#include <vector>
using namespace std;

class TrieNode {
public:
    TrieNode* children[26]; // Fixed array for lowercase English letters
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

    // Helper function to delete a word
    bool deleteHelper(TrieNode* node, const string& word, int depth) {
        if (!node) return false;

        if (depth == word.size()) {
            if (!node->flagEOW) return false;
            node->flagEOW = false;
            for (int i = 0; i < 26; i++)
                if (node->children[i]) return false; // If node still has children, don't delete
            return true; // If no children, delete node
        }

        int index = word[depth] - 'a';
        if (deleteHelper(node->children[index], word, depth + 1)) {
            delete node->children[index];
            node->children[index] = nullptr;
            return !node->flagEOW && isEmpty(node);
        }
        return false;
    }

    // Helper function to check if node has no children
    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++)
            if (node->children[i]) return false;
        return true;
    }

    // Helper function to print Trie words
    void printTrieNode(TrieNode* node, string prefix) {
        if (node->flagEOW) cout << prefix << endl;
        for (int i = 0; i < 26; i++) {
            if (node->children[i])
                printTrieNode(node->children[i], prefix + char(i + 'a'));
        }
    }

    // Helper function for auto-suggestions
    void suggest(TrieNode* node, string prefix, vector<string>& results) {
        if (node->flagEOW) results.push_back(prefix);
        for (int i = 0; i < 26; i++) {
            if (node->children[i])
                suggest(node->children[i], prefix + char(i + 'a'), results);
        }
    }

public:
    Trie() { root = new TrieNode(); }

    // Insert a word into the Trie
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

    // Delete a word from the Trie
    void remove(const string& word) {
        deleteHelper(root, word, 0);
    }

    // Search for a word in the Trie
    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) return false;
            node = node->children[index];
        }
        return node->flagEOW;
    }

    // Check if a prefix exists in the Trie
    bool valid_prefix(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            if (!node->children[index]) return false;
            node = node->children[index];
        }
        return true;
    }

    // Auto-suggest words based on a given prefix
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

    // Print the entire Trie
    void printTrie() {
        printTrieNode(root, "");
    }
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("care");
    trie.insert("dog");
    trie.insert("dot");

    cout << "Trie contents:\n";
    trie.printTrie();

    cout << "\nSearching 'cat': " << (trie.search("cat") ? "Found" : "Not Found") << endl;
    cout << "Valid prefix 'ca': " << (trie.valid_prefix("ca") ? "Yes" : "No") << endl;

    cout << "\nAuto-suggestions for 'ca':\n";
    vector<string> suggestions = trie.auto_suggest("ca");
    for (const string& word : suggestions) {
        cout << word << endl;
    }

    trie.remove("car");
    cout << "\nTrie after deleting 'car':\n";
    trie.printTrie();

    return 0;
}
