#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct word {
    string word;
    int length;
};

int N, K;
word words[100];
string text;
int wordCount = 0;
string output;


int main() {
    // reading input
    ifstream fin("word.in");
    if (fin.is_open()) {
        fin >> N >> K;
        for (int i = 0; i < N; i++) {
            string word;
            fin >> word;
            if (i == N - 1) {
                text += word;
            } else {
                text += word + " ";
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    string currentWord;

    for (int i = 0; i <= text.length(); i++) {
        if (text[i] != ' ' && i != text.length()) {
            currentWord += text[i];
        } else {
            words[wordCount].word = currentWord;
            words[wordCount].length = currentWord.length();

            wordCount++;
            currentWord = "";
        }
    }

    int currentLineLength = 0;
    int i = 0;

    while (i < N) {
        if (currentLineLength + words[i].length <= K) {
            if (i != 0)
                output += " " + words[i].word;
            else
                output += words[i].word;
            currentLineLength += words[i].length;
        } else {
            output += "\n" + words[i].word;
            currentLineLength = words[i].length;
        }
        i++;
    }

    // writing output
    ofstream fout("word.out");
    if (fout.is_open()) {
        fout << output << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}