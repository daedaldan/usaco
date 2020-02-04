#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct block {
    int sorted[316];
    int numWalruses = 0;
    int young = -1;
};

int N, A[100000];
int blockSize = -1, numBlocks = 0;
block blocks[317];
int solution[100000];

void printBlockStuff() {
    // print A
    for (int i = 0; i < N; i++) {
        if ((i + 2) % blockSize != 0 || i == 0) {
            cout << A[i] << " ";
        } else {
            cout << "| " << A[i] << " ";
        }
    }
    cout << endl;

    // print A with sorted blocks
    for (int i = 0; i < numBlocks; i++) {
        for (int j = 0; j < blocks[i].numWalruses; j++) {
            cout << blocks[i].sorted[j] << " ";
        }
        if (i != numBlocks - 1)
            cout << "| ";
    }
    cout << endl;

    // print youngest walrus in each block
    for (int i = 0; i < numBlocks; i++) {
        cout << "block " << i + 1 << " min: " << blocks[i].young << endl;
    }
}

void readFin() {
    ifstream fin("queue.in");
    if (fin.is_open()) {
        fin >> N;
        blockSize = floor(sqrt(N));
        int blockI = 0;
        for (int i = 0; i < N; i++) {
            fin >> A[i];
            // create blocks
            if ((i + 2) % blockSize != 0 || i == 0) { // in a block
                blocks[blockI].sorted[blocks[blockI].numWalruses] = A[i];
                blocks[blockI].numWalruses++;
            } else { // end of block
                sort(blocks[blockI].sorted, blocks[blockI].sorted + blocks[blockI].numWalruses);
                blocks[blockI].young = blocks[blockI].sorted[0];
                numBlocks++;
                blockI++;
                blocks[blockI].sorted[blocks[blockI].numWalruses] = A[i];
                blocks[blockI].numWalruses++;

            }
        }
        // sort last block
        if (N % blockSize == 0)
            sort(blocks[blockI].sorted, blocks[blockI].sorted + blockSize);
        else
            sort(blocks[blockI].sorted, blocks[blockI].sorted + (N % blockSize));
        blocks[blockI].young = blocks[blockI].sorted[0];

        numBlocks += 1;
    } else cout << "error opening input file" << endl;
    fin.close();
}

void printFout() {
    ofstream fout("queue.out");
    if (fout.is_open()) {
        for (int i = 0; i < N; i++) {
            if (i != N - 1) {
                fout << solution[i] << " ";
            } else {
                fout << solution[i] << "\n";
            }
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}

void readCin() {
    cin >> N;
    blockSize = floor(sqrt(N));
    int blockI = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        // create blocks
        if ((i + 2) % blockSize != 0 || i == 0) { // in a block
            blocks[blockI].sorted[blocks[blockI].numWalruses] = A[i];
            blocks[blockI].numWalruses++;
        } else { // end of block
            sort(blocks[blockI].sorted, blocks[blockI].sorted + blocks[blockI].numWalruses);
            blocks[blockI].young = blocks[blockI].sorted[0];
            numBlocks++;
            blockI++;
            blocks[blockI].sorted[blocks[blockI].numWalruses] = A[i];
            blocks[blockI].numWalruses++;

        }
    }
    // sort last block
    if (N % blockSize == 0)
        sort(blocks[blockI].sorted, blocks[blockI].sorted + blockSize);
    else
        sort(blocks[blockI].sorted, blocks[blockI].sorted + (N % blockSize));
    blocks[blockI].young = blocks[blockI].sorted[0];

    numBlocks += 1;
}

void printCout() {
    for (int i = 0; i < N; i++) {
        if (i != N - 1) {
            cout << solution[i] << " ";
        } else {
            cout << solution[i] << "\n";
        }
    }
}

void generateRandomInput() {
    ofstream fout("queue.in");
    if (fout.is_open()) {
        srand(time(NULL));
        int randN = rand() % 100000 + 1;
        fout << randN << "\n";
        for (int i = 0; i < randN; i++) {
            fout << rand() % 1000000 + 1 << " ";
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}

int main() {
    generateRandomInput();
    // reading input
    readFin();
//    readCin();

    for (int i = 0; i < N; i++) {
        // find block that current walrus is in
        int currentBlock = 0;
        while (currentBlock <= i) {
            currentBlock += blockSize;
        }
        currentBlock /= blockSize;
        currentBlock -= 1;

        // find block closest to front of queue with walrus younger than current one
        int j = numBlocks - 1;
        while (blocks[j].young > blocks[currentBlock].young)
            j--;

        // find index of younger walrus
        if (j == currentBlock) { // younger walrus is in same block or does not exist
            int youngest = -1;
            for (int k = j * blockSize; k < (j + 1) * blockSize; k++) {
                if (A[k] < A[i] && k > i && k < N) {
                    youngest = k;
                }
            }
            if (youngest == -1) {
                solution[i] = -1;
            } else {
                solution[i] = youngest - i - 1;
            }
        } else { // younger walrus is in different block
            int youngest = -1;
            for (int k = j * blockSize; k < (j + 1) * blockSize; k++) {
                if (A[k] < A[i]) {
                    youngest = k;
                }
            }
            solution[i] = youngest - i - 1;
        }
    }

    // writing output
    printFout();
//    printCout();

    return 0;
}