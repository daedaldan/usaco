#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

struct block {
    int sorted[316];
    int numWalruses = 0;
    int young = -1;
};

int N, A[100000];
int blockSize = -1, numBlocks = 0;
block blocks[317];

void printBlockStuff() {
    // print A
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
        if ((i + 2) % blockSize == 0  i != 0)
            cout << "| ";
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

int main() {
    // reading input
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
                cout << A[i] << " ";
                blocks[blockI].numWalruses++;
            } else { // end of block
                sort(blocks[blockI].sorted, blocks[blockI].sorted + blocks[blockI].numWalruses);
                blocks[blockI].young = blocks[blockI].sorted[0];
                numBlocks++;
                blockI++;
                cout << "| ";
                blocks[blockI].sorted[blocks[blockI].numWalruses] = A[i];
                cout << A[i] << " ";
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

    cout << endl;

    printBlockStuff();

    // writing output
    ofstream fout("queue.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}