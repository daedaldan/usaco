/*
ID: daniel25
TASK: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int A, B, C = 0;
vector<int> possible_amounts;

int main() {
    ifstream fin("milk3.in");
    string hi;
    if (fin.is_open()) {
        fin >> A;
        fin >> B;
        fin >> C;
    } else cout << "error opening input file" << endl;
    fin.close();



    ofstream fout("milk3.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();
}