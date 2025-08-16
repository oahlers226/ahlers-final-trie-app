# Owen Ahlers CSPB2270 Final Project
# Project Goal: 
The goal of this project is to create a Trie data structure to store a list of common words with shared prefixes. It supports insertion, search, removal, and autocomplete features. A user will be able to enter a prefix and a list of suggested words will be returned.

# Trie (Prefix Tree):
A Trie (pronounced "try"), also commonly referred to as a prefix tree, is a tree-based data structure that is designed to efficiently store strings. Unlike traditional tree structures that store complete keys in each node, Tries distribute string information along the path from root to node and nodes only store a value. Each node represents a single character, and the sequence of nodes to get to any specific node in the tree determines that node's key.

Tries are incredibly efficient at storing and retrieving string values that share a common prefix. This makes them a better choice than a hash table when storing strings that share prefixes. Tries can search for a word in O(L) time, where L is the length of the word, and use less time if the word is small or does not exist in the data structure. Tries have less overhead than a hash table as a hash function is not required and can quickly print out strings in alphabetical order. However, when working with a collection of strings that don't share common prefixes, a hash table would be a better option. For a collection of strings that share a common prefix like "car, care, cart, card, and careful," a Trie only has to store the prefix "car" once, whereas a hash table would have to store the full string value for each of the words. This is why Tries are more efficient for spell checking operations and hash tables are more useful for storing lots of unrelated words.

# Trie Invariants:
* Only one root node, which is empty.
* Each child node only has one parent.
   * Maintain only one path from the root to any one node.
* Boolean flag for nodes that mark the end of a word.
   * Removing a word with valid children nodes, only removes the boolean flag from the appropriate node.
* No duplicate words are stored in the Trie.

# Trie Structure:
An example of how words with shared prefixes are organized in a Trie:
```
{app, apple, car, cart, carton, cord, dog, dogma}

       (root)
     /   |    \
   a     c      d
   |     | \    |
   p     a  o   o
   |     |  |   |
   p--*  r* r   g*   
   |     |  |   |
   l     t* d*  m  
   |     |      |
   e--*  o      a--*
         |
         n--*   
```
\* represents the *isEndOfWord* flag for a node.

### Node Struct:
Trie nodes are very simple because they don't *need* to hold any data values. Nodes can be made more complex if required for the program.
```
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
};
```
* An unordered map is used to hold all the possible child nodes a parent node may have. Unordered maps allow for fast O(1) insertion, search, and removal of child nodes, which is more efficient than a vector or array which requrie O(n) time to search through all elements. Maps also only store the characters than are being used and doesn't waste space by being a fixed size. 
* A boolean flag *isEndOfWord* marks the end of a complete word.

### Core Trie functions:
1. **void insert(string word)**
   * Insert a string a into the Trie, checks for existing characters and only creates new nodes for non-existing characters 

2. **bool search(string word)**
   * Searches through the Trie for an exact match to the given string.
   * Returns boolean value of *isEndOfWord* flag (true if word is found, false otherwise)

3. **void remove(string word)**
   * Sets the *isEndOfWord* flag of a node to false. Removes appropriate nodes if no longer needed.
   * For example: 
      * Removing "car" while "cart" exists in the Trie only sets *isEndOfWord* to false on the "r" node, keeping the "t" node below it. If "car" has no children nodes (c, a, r, all have no children) then those nodes are deleted. 
   * Uses a helper function for recursion

4. **void autoComplete(string word, vector<string>& results)**
   * Allows user to enter a prefix. Returns list of possible words the user is looking for. Returns empty list if prefix is not in tree
   * Uses a helper function for recursion


# Instructions on how to run:
1. Clone the repository
2. Open a terminal and navigate to the project directory.
3. Create a build directory, if it does not already exist:
   ```
   $ mkdir build
   $ cd build
   ```
4. Run CMake from *trie-app/build* directory to configure the project:
   ```
   $ cmake ..
   ```
5. From the *trie-app/build* directory, Build the project and run the test file:
   ```
   $ make && ./trie-tests
   ```

### Test file and expected results:
In the terminal, you will see the output of tests showing that the insert, search, and remove functions all function correctly.

**Insert Test:**
```
Testing insert functionality...
----------------------------------
Inserted word: cat, car, cart, dog, dove, dot, door, apple, app, ape, bat, bath, batman, bar, barn, gravel
```

**Search Test (positive matches):**
```
Testing search for words in trie (positive matches)...
-------------------------------------------------------
Searching for word: cat
Checking characters: c a t Successfully found word: cat

Searching for word: car
Checking characters: c a r Successfully found word: car

Searching for word: cart
Checking characters: c a r t Successfully found word: cart

.....

Searching for word: barn
Checking characters: b a r n Successfully found word: barn

Searching for word: gravel
Checking characters: g r a v e l Successfully found word: gravel
```

**Search Test (negative matches):**
```
Testing search for words NOT in trie (negative matches)...
-----------------------------------------------------------
Searching for word: cab
Checking characters: c a b Failed to find word: cab

Searching for word: doge
Checking characters: d o g e Failed to find word: doge

Searching for word: carton
Checking characters: c a r t o Failed to find word: carton

......

Searching for word: fish
Checking characters: f Failed to find word: fish

Searching for word: cap
Checking characters: c a p Failed to find word: cap
```

**Removal Test:**
```
Testing removal of word: cat
----------------------------------
Searching for word: cat
Checking characters: c a t Searching for word: cat
Checking characters: c a t Successfully removed word: cat

Testing removal of word: car
----------------------------------
Searching for word: car
Checking characters: c a r Searching for word: car
Checking characters: c a r Successfully removed word: car
.......

Testing removal of word: dog
----------------------------------
Searching for word: dog
Checking characters: d o g Searching for word: dog
Checking characters: d o g Successfully removed word: dog
```

**Confirm Removal Test:**
```
Testing search for words in trie (positive matches)...
-------------------------------------------------------
Searching for word: cat
Checking characters: c a t Failed to find word: cat
Searching for word: car
Checking characters: c a r Failed to find word: car
Searching for word: cart
Checking characters: c a r t Successfully found word: cart

Searching for word: dog
Checking characters: d o g Failed to find word: dog
Searching for word: dove
Checking characters: d o v e Successfully found word: dove


All tests completed
----------------------------------
```
After all tests have run, a new Trie will be created with about ~200 common words twith shared prefixes. You can now enter a prefix that you would like to search for. The program will return a list of words that share the given prefix. If the given prefix does not exist in the tree, then the program will tell you that no words were found.

**If prefix matches words in Trie**
```
Enter a prefix to search in the trie: app
Autocomplete results for prefix 'app':
apply
application
apple
applet
```

**If prefix does not match a word in Trie**
```
Enter a prefix to search in the trie: old
Prefix not found in Trie: old
Autocomplete results for prefix 'old':
No results found.
```

Give it a trie!

