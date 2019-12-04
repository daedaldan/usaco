#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct box {
    int row;
    int col;
};

struct component {
    box boxes[1000];
    int numBoxes = 0;
};

int N, K;
int board[100][10];
component components[1000];
int numComponents;

void printBoard() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < 10; col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void gravity() {

};

void findComponents() {
    numComponents = 0;
};

bool destroyComponentsOfK() {
    bool destroyed = false;


    return destroyed;
};

int main() {
    // reading input
    ifstream fin("mooyomooyo.in");
    if (fin.is_open()) {
        fin >> N;
        fin >> K;
        for (int row = 0; row < N; row++) {
            string strRow;
            fin >> strRow;
            for (int col = 0; col < 10; col++) {
                board[row][col] = strRow[col] - 48;
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    printBoard();

    gravity();
    bool destroyed = true;
    while (destroyed) {
        findComponents();
        destroyed = destroyComponentsOfK();
        gravity();
    }

    // writing output
    ofstream fout("mooyomooyo.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}