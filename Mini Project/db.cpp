#include <bits/stdc++.h>
#include <pqxx/pqxx>
#include <iostream>
using namespace std;
using namespace pqxx;

void fetchData(Trie& trie) {
    try {
        connection conn("dbname=your_db user=your_user password=your_pass");
        work txn(conn);
        result r = txn.exec("SELECT description, code FROM Code_Descriptions");

        for (auto row : r) {
            string desc = row["description"].c_str();
            string code = row["code"].c_str();
            trie.insert(desc, desc, code);
        }
        cout << "Data loaded successfully!" << endl;
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}
