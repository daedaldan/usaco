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

struct point {
    bool reachable = false;
    int numNextReachable = 0;
    int nextReachable[7];
    int nextReachableI = 0;
};

string primitives[200];
int numP = 0;
int maxP = -1;
unordered_set<string> primCheck;
char S[200000];
int lengthS = 0;
// lengths[i] indicates whether S at i can be reachable through addition of primitives
bool lengths[200000];

string subS(int start, int end) {
    string slice;
    for (int i = start; i < end; i++)
        slice += S[i];

    return slice;
}

int findNextPoint(int a)  {
    for (int i = 1; i <= maxP; i++) {
        if (lengths[a+i])
            return a + i;
    }

    return lengthS;
}

int iterMaxPrefix() {
    int max = 0;
    lengths[0] = true;
    int lastI = 0;
    for (int i = 0; i < lengthS; i = findNextPoint(i)) {
        // make sure that index is reachable
        if (lengths[i]) {
            bool found = false;
            // find reachable indexes
            for (int j = 1; j <= maxP; j++) {
                string a = subS(i, i + j);
                if (primCheck.find(a) != primCheck.end()) {
                    found = true;
                    // make sure primitive addition does not exceed S
                    if (i + a.length() <= lengthS) {
                        lengths[i + j] = true;
                        // update maximum possible prefix from current primitive addition
                        if (i + j > max) {
                            max = i + j;
                        }
                    }
                }
            }
        }
    }

    return max;
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

    int solution = iterMaxPrefix();

    // writing output
    ofstream fout("prefix.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}