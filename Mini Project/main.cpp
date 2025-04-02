#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include <libpq-fe.h> // PostgreSQL library header
using namespace std;

// Trie Node definition
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    vector<string> suggestions; // Store word suggestions

    TrieNode() : isEndOfWord(false) {}
};

// Trie class
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert word into Trie
    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
            // Add suggestions (optional, for optimization)
            if (find(node->suggestions.begin(), node->suggestions.end(), word) == node->suggestions.end()) {
                node->suggestions.push_back(word);
            }
        }
        node->isEndOfWord = true;
    }

    // Search for word suggestions based on prefix
    vector<string> search(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return {}; // No suggestions
            }
            node = node->children[ch];
        }
        return node->suggestions;
    }
};

// PostgreSQL Database Helper
class Database {
private:
    PGconn* conn;

public:
    Database(const string& connInfo) {
        conn = PQconnectdb(connInfo.c_str());
        if (PQstatus(conn) != CONNECTION_OK) {
            cerr << "Error connecting to database: " << PQerrorMessage(conn) << endl;
        }
    }

    ~Database() {
        PQfinish(conn);
    }

    // Insert word into database
    void insertWord(const string& word) {
        string sql = "INSERT INTO words (word) VALUES ('" + word + "') ON CONFLICT DO NOTHING;";
        PGresult* res = PQexec(conn, sql.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            cerr << "Error inserting word: " << PQerrorMessage(conn) << endl;
        }
        PQclear(res);
    }

    // Load words from database
    vector<string> loadWords() {
        vector<string> words;
        string sql = "SELECT word FROM words;";
        PGresult* res = PQexec(conn, sql.c_str());

        if (PQresultStatus(res) != PGRES_TUPLES_OK) {
            cerr << "Error querying database: " << PQerrorMessage(conn) << endl;
            PQclear(res);
            return words;
        }

        for (int i = 0; i < PQntuples(res); i++) {
            words.push_back(PQgetvalue(res, i, 0));
        }
        PQclear(res);

        return words;
    }
};

int main() {
    // PostgreSQL connection info
    string connInfo = "host=localhost dbname=words_db user=your_username password=your_password";

    // Initialize Database
    Database db(connInfo);

    // Create table if it doesn't exist
    string createTableSQL = "CREATE TABLE IF NOT EXISTS words (id SERIAL PRIMARY KEY, word TEXT UNIQUE);";
    db.insertWord(createTableSQL);

    // Initialize Trie
    Trie trie;

    // Load words from the database into the Trie
    vector<string> words = db.loadWords();
    for (const string& word : words) {
        trie.insert(word);
    }

    // Example word insertion into both Trie and database
    string newWord = "abcd efgh ijkl mnop";
    trie.insert(newWord);
    db.insertWord(newWord);

    // Auto-suggest example
    string prefix = "ab";
    vector<string> suggestions = trie.search(prefix);

    cout << "Suggestions for prefix '" << prefix << "':" << endl;
    for (const string& suggestion : suggestions) {
        cout << suggestion << endl;
    }

    return 0;
}