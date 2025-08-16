#include "../code/trie.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


// Test data set for trie
const vector<string> trie_test_words = {
    "cat",
    "car",
    "cart",
    "dog",
    "dove",
    "dot",
    "door",
    "apple",
    "app",
    "ape",
    "bat",
    "bath",
    "batman",
    "bar",
    "barn",
    "gravel"
};

// Test data set for words that shouldn't be found in the trie
const vector<string> trie_negative_test_words = {
    "cab",
    "doge",
    "carton",
    "apples",
    "bats",
    "barns",
    "grave",
    "zebra",
    "fish",
    "cap"
};

// Data for auto-complete demo
const vector<string> trie_words = {
    "apple", "applet", "application", "apply", "apt", "apex", "apron", "ape", "apology",
    "banana", "band", "bandage", "bandana", "banner", "bank", "bark", "barn", "barrel",
    "book", "bookmark", "bookcase", "booklet", "boom", "boot", "booth", "boost", "border",
    "cat", "catch", "cater", "caterpillar", "category", "cattle", "cave", "cavern", "canvas",
    "car", "cart", "carton", "carpet", "carriage", "carry", "carrot", "cartwheel", "carbon",
    "dog", "dogma", "doghouse", "dogwood", "doll", "dollar", "dome", "domino", "donut",
    "desk", "desktop", "descent", "describe", "desert", "design", "desire", "destiny", "destroy",
    "egg", "eggplant", "ego", "eagle", "ear", "earth", "earring", "early", "earn",
    "fish", "fishing", "fist", "fit", "fix", "fixed", "fixture", "figure", "file",
    "frog", "frost", "front", "frown", "fruit", "fruity", "frugal", "frustrate", "friction",
    "goat", "goal", "goatling", "goblet", "goblin", "gold", "golf", "gone", "gong",
    "hat", "hatch", "hate", "hasty", "hatred", "have", "haven", "hawk", "hazard",
    "ink", "inkwell", "input", "inquire", "inside", "insert", "insight", "inspire", "install",
    "jam", "jamb", "jacket", "jail", "jailor", "jaguar", "jazz", "jeans", "jeep",
    "key", "keyboard", "keyhole", "keystone", "kettle", "ketchup", "kick", "kid", "kidney",
    "lamp", "lamplight", "land", "landing", "landmark", "lane", "language", "laptop", "large",
    "mouse", "mousetrap", "mount", "mountain", "mouth", "move", "movie", "mower", "mosaic",
    "nose", "nostril", "notebook", "note", "notice", "notion", "novel", "novice", "now",
    "owl", "own", "owner", "oak", "oar", "oasis", "oath", "obey", "object",
    "pig", "piglet", "pigeon", "pile", "pill", "pillar", "pilot", "pine", "pink",
    "quilt", "quill", "quilted", "quiver", "quiz", "quote", "quota", "quorum", "quick",
    "rose", "rosette", "roster", "rotate", "rough", "round", "route", "row", "royal",
    "sock", "socket", "soccer", "social", "society", "soft", "sofa", "solar", "soldier",
    "table", "tablet", "tabloid", "tackle", "tact", "tail", "take", "talk", "tall",
    "umbrella", "umpire", "unable", "unaware", "uncle", "under", "undo", "unfold", "unicorn",
    "van", "vane", "vanish", "vanity", "vapor", "variety", "vary", "vast", "vault",
    "wolf", "woman", "wonder", "wood", "wool", "word", "work", "world", "worm",
    "yard", "yarn", "yawn", "year", "yellow", "yesterday", "yield", "yogurt", "young",
    "zip", "zebra", "zero", "zone", "zoo", "zoom", "zeal", "zenith", "zest"
};


// Function to test inserting words into the Trie
void test_insert(Trie& trie, vector<string> trie_test_words) {
    cout << endl;
    cout << "Testing insert functionality..." << endl;
    cout << "----------------------------------" << endl;
    cout << "Inserted word: ";
    for (const string& word : trie_test_words) {
        trie.insert(word);
        cout << word <<", ";
    }
}

// Function to test searching for words that should be found in the Trie
void test_search_positive(Trie& trie, vector<string> trie_test_words) {
    cout << endl;
    cout << "Testing search for words in trie (positive matches)..." << endl;
    cout << "-------------------------------------------------------" << endl;
    for (string word : trie_test_words) {
        if (!trie.search(word)) {
            cout << "Failed to find word: " << word << endl;
        } else {
            cout << "Successfully found word: " << word << endl;
            cout << endl;
        }
    }
}

// Function to test searching for words that should NOT be found in the Trie
void test_search_negative(Trie& trie, vector<string> trie_negative_test_words) {
    cout << endl;
    cout << "Testing search for words NOT in trie (negative matches)..." << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (string word : trie_negative_test_words) {
        if (!trie.search(word)) {
            cout << "Failed to find word: " << word << endl;
        } else {
            cout << "Successfully found word: " << word << endl;
        }
    }
}

// Function to test removing a word from the Trie
void test_remove_word(Trie& trie, string word) {
    cout << endl;
    cout << "Testing removal of word: " << word << endl;
    cout << "----------------------------------" << endl;
    if (trie.search(word)) {
        trie.remove(word);
        if (!trie.search(word)) {
            cout << "Successfully removed word: " << word << endl;
        } else {
            cout << "Failed to remove word: " << word << endl;
        }
    } else {
        cout << "Word not found in trie: " << word << endl;
    }
}

void test_functions() {
    Trie trie;
    // Test the insert functionality
    test_insert(trie, trie_test_words);

    // Test the search functionality (positive and negative matches)
    test_search_positive(trie, trie_test_words);
    test_search_negative(trie, trie_negative_test_words);

    // Test removing words from the trie
    vector<string> removeWords = {"cat", "dog", "apple", "bat", "car"};
    for (string word : removeWords) {
        test_remove_word(trie, word);
    }

    // Verify that the words are removed
    test_search_positive(trie, trie_test_words);
    return;
}


int main() {
    test_functions();
    cout << "All tests completed" << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    // Create a Trie instance and fill with common words with similar prefixes
    Trie trie;
    test_insert(trie, trie_words);
    cout << endl;
    cout << endl;
    string input = "";

    // Prompt user for a prefix to search in the trie, Ensures input is valid
    do {
        cout << "Enter a prefix to search in the trie: ";
        cin >> input;
        bool valid = true;
        for (char c : input) {
            if (!isalpha(c)) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Invalid input! Please try again. Letters only" << endl;
        } 
        else {
            break;
        }
    } while (true);

    vector<string> results;
    trie.autoComplete(input, results);

    cout << "Autocomplete results for prefix '" << input << "':" << endl;
    if (results.empty()) {
        cout << "No results found." << endl;
    } else {
        for (const string& result : results) {
            cout << result << endl;
        }
    }

    return 0;
}