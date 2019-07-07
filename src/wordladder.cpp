/**
 * The Word Ladder game written in C++ as an assignment for CS106B at Stanford Summer Session.
 * Author: Kevin Li
 * Description:  This program converts one English word to another by modifying one letter at a time.
 */
#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "lexicon.h"
#include "stack.h"
#include "queue.h"
#include "set.h"
using namespace std;

void printIntroduction();
void runGame();
void promptUser(Lexicon& dict, string word1, string word2);
void promptForDictionary(Lexicon& dict);
bool promptWords(const Lexicon& dict, string& word1, string& word2);
void loadDictionary(ifstream& dictFile, Lexicon& dict);
void formLadder(string word1, string word2, const Lexicon& dict);
void printWordLadder(Queue<Stack<string> > queue, string word1, string word2);
bool findNeighboringWords(string word, string targetWord, const Lexicon& dict, const Stack<string>& first, Set<string>& appearedWords, Queue<Stack<string> >& queue);
void copyStack(Stack<string> stack, Stack<string>& copy);

int main() {
    printIntroduction();
    runGame();
    cout << "Have a nice day." << endl;
    return 0;
}

/**
 * Run the game
 */
void runGame() {
    Lexicon dict;
    promptForDictionary(dict);

    string word1;
    string word2;
    bool keepRunning = true;
    while (keepRunning) {
        keepRunning = promptWords(dict, word1, word2);
    }
}

/**
 * @brief Form a word ladder from word2 back to word1
 * @param word1 the first word
 * @param word2 the second word
 * @param dict the dictionary which contains all words to search for
 */
void formLadder(string word1, string word2, const Lexicon& dict) {
    Queue<Stack<string> > queue;
    Stack<string> firstStack;
    firstStack.push(word1);
    Set<string> appearedWords;
    appearedWords.add(word1);
    queue.enqueue(firstStack);

    while (!queue.isEmpty()) {
        Stack<string> first = queue.dequeue();
        if (findNeighboringWords(first.peek(), word2, dict, first, appearedWords, queue)) {
            break;
        }
    }
    printWordLadder(queue, word1, word2);
}

/**
 * @brief Print the word ladder
 * @param queue the queue containing all Breadth-first search histories
 * @param word1 the first word
 * @param word2 the second word
 */
void printWordLadder(Queue<Stack<string> > queue, string word1, string word2) {
    Stack<string> wordLadder;
    if (queue.isEmpty()) { // no word ladder found
        cout << "No word ladder found from " << word2 << " back to " << word1 << "." << endl;
    } else {
        while (!queue.isEmpty()) {
            wordLadder = queue.dequeue();
        }
        string result = "";
        while (!wordLadder.isEmpty()) {
            result += wordLadder.pop() + " ";
        }
        cout << "A ladder from " << word2 << " back to " << word1 << ": " << endl;
        cout << result << endl;
    }
}

/**
 * @brief Find all neighboring words of a word and search until the target word is found.
 *
 * Neighboring words are all words which have the same length and
 * are only one character different from the original word.
 *
 * @param word
 * @param targetWord
 * @param dict
 * @param first
 * @param appearedWords
 * @param queue
 * @return true if targetWord is found, false otherwise.
 */
bool findNeighboringWords(string word, string targetWord, const Lexicon& dict, const Stack<string>& first, Set<string>& appearedWords, Queue<Stack<string> >& queue) {
    for (int i = 0; i < word.length(); i++) {
        char currentChar = word[i];
        for (char ch = 'a'; ch <= 'z'; ch++) {
            string newWord = word.substr(0, i) + ch + word.substr(i + 1, string::npos);
            if (ch != currentChar && dict.contains(newWord) && !appearedWords.contains(newWord)) {
                Stack<string> copyOfFirst = first;
                copyOfFirst.push(newWord);
                queue.enqueue(copyOfFirst);
                appearedWords.add(newWord);
                if (newWord == targetWord) {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Print introduction texts for the game.
 */
void printIntroduction() {
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time.\n" << endl;
}

/**
 * @brief Prompt user for name for dictionary file.
 * @param dict Lexicon to store the dictionary
 */
void promptForDictionary(Lexicon& dict) {
    ifstream dictFile;
    promptUserForFile(dictFile, "Dictionary file name: ");
    dict.addWordsFromFile(dictFile);
}

/**
 * @brief Prompt user for two words to form a word ladder
 * @param dict the dictionary which contains all words to search for
 * @param word1 the first word
 * @param word2 the second word
 * @return
 */
bool promptWords(const Lexicon& dict, string& word1, string& word2) {
    cout << endl;
    word1 = toLowerCase(getLine("Word 1 (or Enter to quit): "));
    if (word1 == "") { // ENTER to quit
        return false;
    }
    word2 = toLowerCase(getLine("Word 2 (or Enter to quit): "));
    if (word2 == "") { // ENTER to quit
        return false;
    }

    if (word1.length() != word2.length()) {
        cout << "The two words must be the same length." << endl;
    } else if (word1 == word2) {
        cout << "The two words must be different." << endl;
    } else if (!dict.contains(word1) || !dict.contains(word2)) {
        cout << "The two words must be found in the dictionary." << endl;
    } else {
        formLadder(word1, word2, dict);
    }
    return true;
}
