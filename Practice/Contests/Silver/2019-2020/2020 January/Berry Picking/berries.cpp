/*
 * NOTE: This code is unfinished.
 * */

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct split {
    int sum = -1;
    int baskets[1000];
    bool solutionExists = true;
};

int N, K;
int trees[1000];
int baskets[1000];

int copyArray(int original[], int copy[], int size) {
    for (int i = 0; i < size; i++)
        copy[i] = original[i];
}

/* one higher, one lower (but higher than lowest) */
/* MULTIPLE POSSIBILITIES */
split highLow(int i) {
    split s;

//    if () {
//
//    } else {
//        s.solutionExists = false;
//    }

    s.solutionExists = false;

    return s;
}

/* both equal to bound and greater than lowest */
split bothSame(int i) {
    split s;

    if (baskets[i] / 2 == baskets[K/2 - 1] && baskets[i] / 2 > baskets[0]) {
        int bound = baskets[K/2 - 1];
        for (int i = K - 1; i > K/2; i--)
            s.baskets[i] = baskets[i - 1];
        for (int i = K/2 - 1; i > 0; i--)
            s.baskets[i - 1] = baskets[i];
        s.baskets[K/2 - 1] = bound;
        s.baskets[K/2] = bound;

        s.sum += 1;
        for (int i = 0; i < K /2 ; i++)
            s.sum += s.baskets[i];
    } else {
        s.solutionExists = false;
    }

    return s;
}

/* both higher than bound */
/* MULTIPLE POSSIBILITIES */
split bothHigh(int i) {
    split s;

//    if () {
//        ;
//    } else {
//        s.solutionExists = false;
//    }

    s.solutionExists = false;

    return s;
}

/* both lower than bound but one is greater than lowest and sum is greater than lowest + bound */
/* MULTIPLE POSSIBILITIES */
split bothLow(int i) {
    split s;

//    if () {
//
//    } else {
//        s.solutionExists = false;
//    }

    s.solutionExists = false;

    return s;
}

/* one same one higher and same is greater than min */
split sameHigh(int i) {
    split s;

    if (baskets[K/2 - 1] > baskets[0] && baskets[i] > 2 * baskets[K/2 - 1]) {
        int higher = baskets[i] - baskets[K/2 - 1];
        s.baskets[i] = higher;
        s.baskets[0] = baskets[K/2 - 1];
        sort(s.baskets, s.baskets + K);
    } else {
        s.solutionExists = false;
    }

    return s;
}

/* one same one lower and lower is greater than min */
split sameLow(int i) {
    split s;

    if (baskets[i] - baskets[K/2 - 1] > baskets[0]) {
        int lower = baskets[i] - baskets[K/2 - 1];
        s.baskets[0] = lower;
        s.baskets[i] = baskets[K/2 - 1];
        sort(s.baskets, s.baskets + K);
    } else {
        s.solutionExists = false;
    }

    return s;
}

/* try each possible split and return array and sum of optimal split */
split checkOptions(int i) {
    split s;

    split hl = highLow(i);
    if (hl.solutionExists && hl.sum > s.sum) {
        s.sum = hl.sum;
        copyArray(hl.baskets, s.baskets, K);
    }

    split bs = bothSame(i);
    if (bs.solutionExists && bs.sum > s.sum) {
        s.sum = bs.sum;
        copyArray(bs.baskets, s.baskets, K);
    }

    split bh = bothHigh(i);
    if (bh.solutionExists && bh.sum > s.sum) {
        s.sum = bh.sum;
        copyArray(bh.baskets, s.baskets, K);
    }

    split bl = bothLow(i);
    if (bl.solutionExists && bl.sum > s.sum) {
        s.sum = bl.sum;
        copyArray(bl.baskets, s.baskets, K);
    }

    split sh = sameHigh(i);
    if (sh.solutionExists && sh.sum > s.sum) {
        s.sum = sh.sum;
        copyArray(sh.baskets, s.baskets, K);
    }

    split sl = sameLow(i);
    if (sl.solutionExists && sl.sum > s.sum) {
        s.sum = sl.sum;
        copyArray(sl.baskets, s.baskets, K);
    }

    return s;
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

    bool done = false;
    int optimalSum = 0;
    for (int i = 0; i < K/2; i++)
        optimalSum += baskets[i];

    while (!done) {
        for (int i = 0; i < K; i++) {
            if (i != K - 1)
                cout << baskets[i] << ", ";
            else
                cout << baskets[i] << endl;
        }
        cout << optimalSum << endl;

        done = true;
        int copyBaskets[1000];
        copyArray(baskets, copyBaskets, K);

        int optimalBaskets[1000];
        for (int i = K/2; i < K; i++) {
            split result = checkOptions(i);
            if (result.solutionExists) {
                if (result.sum > optimalSum) {
                    optimalSum = result.sum;
                    copyArray(result.baskets, optimalBaskets, K);
                    done = false;
                }
            }
        }

        copyArray(optimalBaskets, baskets, K);
    }

    // writing output
    ofstream fout("berries.out");
    if (fout.is_open()) {
        fout << optimalSum << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}