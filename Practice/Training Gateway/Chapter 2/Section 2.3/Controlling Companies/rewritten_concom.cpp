/*
ID: daniel25
TASK: concom
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    // reading input
    ifstream fin("concom.in");
    if (fin.is_open()) {

    } else cout << "error opening input file" << endl;
    fin.close();

    // writing output
    ofstream fout("concom.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}