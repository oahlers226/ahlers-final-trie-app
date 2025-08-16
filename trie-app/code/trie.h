#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
};

class Trie {
public:
    Trie();
    ~Trie();
    TrieNode* init_node();
    void insert(string word);
    bool search(string word);
    void remove(string word);
    bool removeHelper(TrieNode* node, string word, int depth);
    void autoComplete(string word, vector<string>& results);
    void autoCompleteHelper(TrieNode* node, string& currentWord, vector<string>& results);
private:
    TrieNode* root;
};

#endif // TRIE_H