#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "lexicon.h"
using namespace std;

void printIntroduction();
void promptUser(Lexicon& dict);
void promptWords(const Lexicon& dict, string& word1, string& word2);
void loadDictionary(ifstream& dictFile, Lexicon& dict);

int main() {
    printIntroduction();
    Lexicon dict;
    promptUser(dict);
    cout << "Have a nice day." << endl;
    return 0;
}

void printIntroduction() {
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time.\n" << endl;
}

void promptUser(Lexicon& dict) {
    ifstream dictFile;
    promptUserForFile(dictFile, "Dictionary file name: ");
    loadDictionary(dictFile, dict);
    string word1;
    string word2;
    promptWords(dict, word1, word2);
}

void promptWords(const Lexicon& dict, string& word1, string& word2) {
    cout << endl;
    word1 = toLowerCase(getLine("Word 1 (or Enter to quit): "));
    word2 = toLowerCase(getLine("Word 2 (or Enter to quit): "));

    if (word1.length() != word2.length()) {
        cout << "The two words must be the same length." << endl;
    } else if (word1 == word2) {
        cout << "The two words must be different." << endl;
    } else if (!dict.contains(word1) || !dict.contains(word2)) {
        cout << "The two words must be found in the dictionary." << endl;
    } else {
        return;
    }
    promptWords(dict, word1, word2);
}

void loadDictionary(ifstream& dictFile, Lexicon& dict) {
    dict.addWordsFromFile(dictFile);
}
