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
bool found[100][10];
component components[1000];
int numComponents = 0;

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
    for (int col = 0; col < 10; col++) {
        int row = N-1;
        while (board[row][col] != 0) {
            row--;
        }
        int lastZeroRow = row;
        for (int r = row; r >= 0; r--) {
//            for (int i = 0; i < N; i++)
//                cout << board[i][col] << " " << endl;
//            cout << r << " " << lastZeroRow << endl;
            if (board[r][col] != 0) {
                board[lastZeroRow][col] = board[r][col];
                board[r][col] = 0;
                lastZeroRow--;
            }
        }
    }
};

bool withinBounds(int row, int col) {
    if (row < 0 || row > N-1)
        return false;
    if (col < 0 || col > 9)
        return false;

    return true;
}

void findComponentsSub(int row, int col) {
    found[row][col] = true;
    box b;
    b.row = row;
    b.col = col;
    components[numComponents].boxes[components[numComponents].numBoxes] = b;
    components[numComponents].numBoxes++;
    if (withinBounds(row-1, col)) {
        if (board[row-1][col] == board[row][col] && !found[row-1][col]) {
            findComponentsSub(row-1, col);
        }
    }
    if (withinBounds(row+1, col)) {
        if (board[row+1][col] == board[row][col] && !found[row+1][col]) {
            findComponentsSub(row+1, col);
        }
    }
    if (withinBounds(row, col-1)) {
        if (board[row][col-1] == board[row][col] && !found[row][col-1]) {
            findComponentsSub(row, col-1);
        }
    }
    if (withinBounds(row, col+1)) {
        if (board[row][col+1] == board[row][col] && !found[row][col+1]) {
            findComponentsSub(row, col+1);
        }
    }
}

void findComponents() {
    for (int i = 0; i < numComponents; i++) {
        components[i].numBoxes = 0;
    }
    numComponents = 0;
    // resetting board to check whether boxes were already visited
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < 10; col++) {
            found[row][col] = false;
        }
    }
    // flood fill
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < 10; col++) {
            if (!found[row][col] && board[row][col] != 0) {
                findComponentsSub(row, col);
                numComponents++;
            }
        }
    }
};

bool destroyComponentsOfK() {
    bool destroyed = false;
    for (int i = 0; i < numComponents; i++) {
        if (components[i].numBoxes >= K) {
            destroyed = true;
            for (int j = 0; j < components[i].numBoxes; j++) {
                board[components[i].boxes[j].row][components[i].boxes[j].col] = 0;
            }
        }
    }

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
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < 10; col++) {
                fout << board[row][col];
            }
            fout << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}