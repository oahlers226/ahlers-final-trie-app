#include "trie.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Constructor to initialize the Trie
Trie::Trie() {
    root = new TrieNode();
    root->isEndOfWord = false;
}

// Destructor to clean up the Trie
Trie::~Trie() {
    delete root;
}

TrieNode* Trie::init_node() {
    TrieNode* newNode = new TrieNode();
    newNode->isEndOfWord = false;
    return newNode;
}

void Trie::insert(string word) {
    TrieNode* cursor = root;
    // Traverse the trie and insert new characters
    for (char c : word) {
        if (cursor->children.find(c) == cursor->children.end()) {
            cursor->children[c] = new TrieNode();
        }
        cursor = cursor->children[c];
    }
    cursor->isEndOfWord = true;
}


bool Trie::search(string word) {
    TrieNode* cursor = root;
    cout << "Searching for word: " << word << endl;
    cout << "Checking characters:  ";
    for (char ch : word) {
        cout << ch << " ";
        // if the character is not found in the children of the current node, return false
        if (cursor->children.find(ch) == cursor->children.end()) {
            return false;
        }
        cursor = cursor->children[ch];
    }
    return cursor->isEndOfWord;
}

void Trie::remove(string word) {
    // Could have used one function, but I liked the idea of using a helper function for recursion
    removeHelper(root, word, 0);
}
bool Trie::removeHelper(TrieNode* node, string word, int depth) {
    // Base case, if the node is null, return false
    if (!node) {
        return false;
    } 

    // If we have reached the end of the word, 
    if (depth == word.size()) {

        // If node has no children, it can be deleted
        if (node->isEndOfWord) {
            node->isEndOfWord = false;
            return node->children.empty();

        }

        return false;
    }

    // Get the character at the current depth
    char c = word[depth];
    auto it = node->children.find(c);
    TrieNode* child = it->second;

    // If character is not found, return false
    if (node->children.find(c) == node->children.end()) {
        return false;
    }
    
    // Recursively remove child nodes
    bool shouldDeleteChild = removeHelper(child, word, depth+1);

    // If current node is not end of another word and has no children, it can be deleted
    if (shouldDeleteChild) {
        // Ouch :(
        delete child;
        node->children.erase(it);
        return node->children.empty() && !node->isEndOfWord;
    }
    return false;
}




void Trie::autoComplete(string prefix, vector<string>& results) {
    TrieNode* cursor = root;

    // Traverse the trie and find the node with the last character of the prefix
    for (char c : prefix) {
        if (cursor->children.find(c) == cursor->children.end()) {
            cout << "Prefix not found in Trie: " << prefix << endl;
            return; // If prefix not found, return empty results
        } 
        cursor = cursor->children[c];
    }
    // cursor now points to the node corresponding to the last character of the prefix
    // Return all words beginning with the prefix
    vector<string> words;
    string currentWord = prefix;

    autoCompleteHelper(cursor, currentWord, words);

    // insert(position, first, last) inserts elements from the range [first, last) at position
    results.insert(results.end(), words.begin(), words.end());
    return;

}

void Trie::autoCompleteHelper(TrieNode* node, string& currentWord, vector<string>& results) {
    TrieNode* cursor = node;

    // If the current node is end of a word, add the current word to results
    if (cursor->isEndOfWord) {
        results.push_back(currentWord);

    }

    // Iterate through all children of the current node
    for (auto iter = cursor->children.begin(); iter != cursor->children.end(); iter++) {
        char c = iter->first;
        TrieNode* child = iter->second;
        currentWord.push_back(c); // Add character to current word
        autoCompleteHelper(child, currentWord, results);

        // Remove character after exploring this path, returning to the previous state of prefix
        currentWord.pop_back(); 
    }


}