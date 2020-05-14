#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    // reading input
    ifstream fin("problem3.in");
    if (fin.is_open()) {

    } else cout << "error opening input file" << endl;
    fin.close();

    // writing output
    ofstream fout("problem3.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}