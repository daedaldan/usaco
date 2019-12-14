#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>

using namespace std;

int N;
string road;
int solution;

int main() {
    // reading input
    ifstream fin("whereami.in");
    if (fin.is_open()) {
        fin >> N;
        fin >> road;
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int K = 1; K <= N; K++) {
        unordered_set<string> substrings;
        bool works = true;
        for (int i = 0; i <= N-K; i++) {
            string segment = road.substr(i, K);
            if (substrings.find(segment) != substrings.end()) {
                works = false;
                break;
            }
            substrings.insert(segment);
        }
        if (works) {
            solution = K;
            break;
        }
    }
    // writing output
    ofstream fout("whereami.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}