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
void promptUser(Lexicon& dict, string& word1, string& word2);
void promptForDictionary(Lexicon& dict);
void promptWords(const Lexicon& dict, string& word1, string& word2);
void loadDictionary(ifstream& dictFile, Lexicon& dict);
void formLadder(string& word1, string& word2, const Lexicon& dict);
void printWordLadder(Queue<Stack<string> > queue);
bool findNeighboringWords(string word, string targetWord, const Lexicon& dict, const Stack<string>& first, Set<string>& appearedWords, Queue<Stack<string> >& queue);
void copyStack(Stack<string> stack, Stack<string>& copy);

int main() {
    printIntroduction();
    runGame();
    cout << "Have a nice day." << endl;
    return 0;
}

void runGame() {
    Lexicon dict;
    promptForDictionary(dict);

    string word1;
    string word2;
    promptWords(dict, word1, word2);
}

void formLadder(string& word1, string& word2, const Lexicon& dict) {
//    create a queue of stacks, initially containing only a single stack storing {w1}.
//    repeat until queue is empty or w2 is found:
//        dequeue a stack s.
//        for each valid unused English word w
//                that is a "neighbor" (differs by 1 letter)
//                of the word on top of s:
//            create a new stack s2 whose contents are the same as s,
//                    but with w added on top,
//            and add s2 to the queue.
    cout << "A ladder from " << word2 << " back to " << word1 << ": " << endl;
    Queue<Stack<string> > queue;
    Stack<string> firstStack;
    firstStack.push(word1);
    Set<string> appearedWords;
    appearedWords.add(word1);
    queue.enqueue(firstStack);

    while (!queue.isEmpty()) {
//        cout << queue.toString() << endl;
        Stack<string> first = queue.dequeue();
        if (findNeighboringWords(first.peek(), word2, dict, first, appearedWords, queue)) {
            break;
        }
    }
    printWordLadder(queue);
}

void printWordLadder(Queue<Stack<string> > queue) {
    Stack<string> wordLadder;
    while (!queue.isEmpty()) {
        wordLadder = queue.dequeue();
    }
    string result = "";
    while (!wordLadder.isEmpty()) {
        result += wordLadder.pop() + " ";
    }
    cout << result << endl;
}

bool findNeighboringWords(string word, string targetWord, const Lexicon& dict, const Stack<string>& first, Set<string>& appearedWords, Queue<Stack<string> >& queue) {
    for (int i = 0; i < word.length(); i++) {
        char currentChar = word[i];
        for (char ch = 'a'; ch <= 'z'; ch++) {
            string newWord = word.substr(0, i) + ch + word.substr(i + 1, string::npos);
            if (ch != currentChar && dict.contains(newWord) && !appearedWords.contains(newWord)) {
                Stack<string> copyOfFirst;
                copyStack(first, copyOfFirst);
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

void copyStack(Stack<string> stack, Stack<string>& copy) {
//    while (!stack.isEmpty()) {
//        copy.push(stack.pop());
//    }
    copy = stack;
}

void printIntroduction() {
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time.\n" << endl;
}

void promptForDictionary(Lexicon& dict) {
    ifstream dictFile;
    promptUserForFile(dictFile, "Dictionary file name: ");
    loadDictionary(dictFile, dict);
}

void promptWords(const Lexicon& dict, string& word1, string& word2) {
    cout << endl;
    word1 = toLowerCase(getLine("Word 1 (or Enter to quit): "));
    if (word1 == "") { // ENTER to quit
        return;
    }
    word2 = toLowerCase(getLine("Word 2 (or Enter to quit): "));
    if (word2 == "") { // ENTER to quit
        return;
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
    promptWords(dict, word1, word2);
}

void loadDictionary(ifstream& dictFile, Lexicon& dict) {
    dict.addWordsFromFile(dictFile);
}
