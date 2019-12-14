#include <iostream>
#include <string>
#include <fstream>

using namespace std;

long long N;

long long numIndex(long long n) {
    return n - (n - n % 3) /3 - (n - n % 5) / 5 + (n - n % 15) / 15;
}

long long binarySearch(long long low, long long high) {
    long long mid = (low + high) / 2;
    if (numIndex(mid) == N) {
        return mid;
    } else if (numIndex(low + 1) == (high)) {
        if (numIndex(low)) return low;
        else return high;
    } else if (numIndex(mid) < N) {
        binarySearch(mid, high);
    } else {
        binarySearch(low, mid);
    }
}

int main() {
    // reading input
    ifstream fin("moobuzz.in");
    if (fin.is_open()) {
        fin >> N;
    } else cout << "error opening input file" << endl;
    fin.close();

    // writing output
    ofstream fout("moobuzz.out");
    if (fout.is_open()) {
        fout << binarySearch(0, 1000000000000) << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}

