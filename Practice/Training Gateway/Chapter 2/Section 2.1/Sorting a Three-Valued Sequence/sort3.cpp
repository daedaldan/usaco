/*
ID: daniel25
TASK: sort3
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int records[1000];
int minExchanges = 999;

int main() {
    // reading input
    ifstream fin("sort3.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++)
            fin >> records[i];
    } else cout << "error opening input file" << endl;
    fin.close();

    // writing output
    ofstream fout("sort3.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();
}