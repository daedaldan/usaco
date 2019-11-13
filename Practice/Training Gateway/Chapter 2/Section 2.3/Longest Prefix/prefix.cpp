/*
ID: daniel25
TASK: prefix
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;

string primitives[200];
int numP = 0;
int maxP = -1;
unordered_set<string> primCheck;
char S[200000];
int lengthS = 0;
// lengths[i] is longest prefix that can be built from index i of S
int lengths[200000];
int solution = -1;

string subS(int start, int end) {
    string slice;
    for (int i = start; i < end; i++)
        slice += S[i];

    return slice;
}

int maxPrefix(int len) {
    if (lengths[len] != 0) {
        return lengths[len];
    } else {
        bool found = false;
        int max = -1;
        for (int i = 1; i <= maxP; i++) {
            string a = subS(len, len+i);
            if (primCheck.find(a) != primCheck.end()) {
                found = true;
                lengths[len+i] = maxPrefix(len+i);
                // update maximum possible prefix from given index
                if (lengths[len+i] > max)
                    max = lengths[len+i];
            }
        }

        if (!found) {
            return len;
        } else {
            return *max_element(lengths, lengths + lengthS + 1);
        }
    }
}

int main() {
    // reading input
    ifstream fin("prefix.in");
    if (fin.is_open()) {
        // read primitives
        string line;
        while (getline(fin, line) && line != ".") {
            stringstream lineStream(line);
            string prim;
            while (getline(lineStream, prim, ' ')) {
                primitives[numP] = prim;
                numP++;
                if (static_cast<int>(prim.length()) > maxP) {
                    maxP = prim.length();
                }

                primCheck.insert(prim);
            }
        }

        // read S
        while (getline(fin, line)) {
            for (int i = 0; i < line.length(); i++) {
                S[lengthS] = line[i];
                lengthS++;
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    cout << numP << endl;

    int solution = maxPrefix(0);

    // writing output
    ofstream fout("prefix.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}