#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct split {
    int sum;
    int baskets[1000];
    bool solutionExists = true;
};

int N, K;
int trees[1000];
int baskets[1000];
int bottomSum = 1000001;

/* try each possible split and return array and sum of optimal split */
split checkOptions(int i) {
    split s;
    s.sum = 5;

    return s;
}

int highLow() {
    return 1;
}

int bothSame() {
    return 1;
}

int bothHigh() {
    return 1;
}

int bothLow() {
    return 1;
}

int sameHigh() {
    return 1;
}

int sameLow() {
    return 1;
}

int copyArray(int original[], int copy[], int size) {
    for (int i = 0; i < size; i++)
        copy[i] = original[i];
}

int main() {
    // reading input
    ifstream fin("berries.in");
    if (fin.is_open()) {
        fin >> N >> K;
        for (int i = 0; i < N; i++) {
            fin >> trees[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    sort(trees, trees+N);

    // fill baskets
    if (N > K) { // more trees than baskets
        int difference = N - K;
        for (int i = difference; i < N; i++) {
            baskets[i - difference] = trees[i];
        }
    } else if (N < K) { // less trees than baskets
        int difference = K - N;
        for (int i = difference; i < K; i++) {
            baskets[i] = trees[i - difference];
        }
    } else if (N == K) { // num trees equals num baskets
        for (int i = 0; i < N; i++)
            baskets[i] = trees[i];
    }

//    bool done = false;
//    while (!done) {
//        done = true;
//        int copyBaskets[1000];
//        copyArray(baskets, copyBaskets, K);
//
//        int optimalSum = -1;
//        int optimalBaskets[1000];
//        for (int i = K/2; i < K; i++) {
//            split result = checkOptions(i);
//            if (result.solutionExists) {
//                if (result.sum > optimalSum) {
//                    optimalSum = result.sum;
//                    copyArray(optimalBaskets, result.baskets, K);
//                    done = false;
//                }
//            }
//        }
//
//        copyArray(optimalBaskets, baskets, K);
//    }

    // writing output
    ofstream fout("berries.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}