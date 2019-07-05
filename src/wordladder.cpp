// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include "console.h"
using namespace std;

void printIntroduction();

int main() {
    printIntroduction();

    cout << "Have a nice day." << endl;
    return 0;
}

void printIntroduction() {
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time.\n" << endl;
}
