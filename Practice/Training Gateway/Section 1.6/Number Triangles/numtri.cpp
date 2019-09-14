/*
ID: daniel25
TASK: numtri
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int R;
int rows[1000][1000];
int largest = -1;
int solves = 0;

void solve(int i, int r, int sum) {
    solves += 1;
    sum += rows[r][i];

    if (sum > largest)
        largest = sum;

    if (r == R-1)
        return;

    int arrMaxI = sizeof(rows[r])/sizeof(rows[r][0]) - 1;
//    if (i > 0 && r >= 200) {
//        if (rows[r+1][i] != 0) {
//            if (i == 0) {
//                // check right child if on left edge
//                if (rows[r][0] + rows[r+1][1] >= rows[r][1] + rows[r+1][1])
//                    solve(i, r+1, sum);
//            } else if (i == arrMaxI) {
//                // check left child if on right edge
//                if (rows[r][i] + rows[r+1][i] >= rows[r][i-1] + rows[r+1][i])
//                    solve(i, r+1, sum);
//            } else {
//                // check both children if in middle
//                if (rows[r][i] + rows[r+1][i] >= rows[r][i-1] + rows[r+1][i])
//                    solve(i, r+1, sum);
//                if (rows[r][i] + rows[r+1][i+1] >= rows[r][i+1] + rows[r+1][i+1])
//                    solve(i, r+1, sum);
//            }
//        }
//        if (rows[r+1][i+1] != 0)
//                solve(i+1, r+1, sum);

//        else {
            if (rows[r+1][i] != 0)
                solve(i, r+1, sum);
            if (rows[r+1][i+1] != 0)
                solve(i+1, r+1, sum);
//        }
//    } else {
//        if (rows[r+1][i] != 0)
//            solve(i, r+1, sum);
//        if (rows[r+1][i+1] != 0)
//            solve(i+1, r+1, sum);
//    }



}

int main() {
    ifstream fin("numtri.in");
    string line;
    int rowsIndex = 1;
    if (fin.is_open()) {
        getline(fin, line);
        R = stoi(line);
        for (rowsIndex; rowsIndex <= R; rowsIndex++) {
            for (int i = 0; i < rowsIndex; i++)
                fin >> rows[rowsIndex-1][i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    solve(0, 0, 0);

    cout << solves << endl;

    ofstream fout("numtri.out");
    if (fout.is_open()) {
        fout << largest << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
}