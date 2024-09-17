#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

bool isWord(string word) {
    ifstream fin;
    fin.open("words_alpha.txt");
    string fileWord = "";
    if (!fin.is_open()) {
        cout << "Error opening file!" << endl;
        return false;
    }
    while(fin >> fileWord) {
        if(fileWord == word) {
            return true;
        } 
    }
    fin.close();
    return false;
}

string isCloser(bool isA, string target, string guess, string prevClosest) {
    bool letterCorrect = true;
    int guess_dist = -1;
    int prev_dist = -1;
    char tLetter = '@';
    char gLetter = '@';
    char pLetter = '@';
    for(int i = 0; i < target.size(); i++) {
        tLetter = target[i];
        if (guess.size() >= i) {
            gLetter = guess[i];
        } else {
            gLetter = '@';
        }
        if (prevClosest.size() >= i) {
            pLetter = prevClosest[i];
        } else {
            pLetter = '@';
        }

        if(letterCorrect) {
            guess_dist = tLetter - gLetter;
            prev_dist = tLetter - pLetter;
            if(abs(guess_dist) < abs(prev_dist)) {
                return guess;
            }
            else if(abs(guess_dist) > abs(prev_dist)) {
                return prevClosest;
            }
        } else {
            if(isA) {
                if(gLetter > pLetter) {
                    return guess;
                }
                else if ((gLetter < pLetter) ) {
                    return prevClosest;
                }
            } else {
                if(gLetter < pLetter) {
                    return guess;
                }
                else if ((gLetter > pLetter) ) {
                    return prevClosest;
                }
            }
        }
        if (gLetter != tLetter) {
            letterCorrect = false;
        }

    }
    return prevClosest; 

}

int isBefore(string target, string guess) {
    for(int i = 0; i < target.size(); i++) {
        if (target[i] - guess[i] > 0) {
            return true;
        }
        else if (target[i] - guess[i] < 0) {
            return false;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    cout << "Welcome to Alphaseek! You must find a target word by guessing words and seeing how alphabetically close your guesses are from the target. Good luck!" << endl;
    string word = "infinite";
    string aclosest = "aaaa";
    string zclosest = "zzzz";
    string guess = "";
    do {
        cout << "Based on your guesses, the target word is between " << aclosest << " and " << zclosest << "." << endl;
        cout << "Guess a word: ";       
        cin >> guess;
        for(int i = 0; i < guess.size(); i++) {
            guess[i] = tolower(guess[i]);
        }
        bool validGuess = isWord(guess);
        while (!validGuess) {
            cout << "That is not a word. guess again: ";
            cin >> guess;
            validGuess = isWord(guess);
        }
        bool before = isBefore(word, guess);
        if(before) {
            aclosest = isCloser(true, word, guess, aclosest);
        } else {
            zclosest = isCloser(false, word, guess, zclosest);
        }

    } while (guess != word);
    cout << "Congratulations! You guessed the word!" << endl;
}