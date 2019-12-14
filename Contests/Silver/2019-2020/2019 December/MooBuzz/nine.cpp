#include <iostream>
#include <string>
#include <fstream>

using namespace std;

long double N;

long double numIndex(long double a) {
    long long n = static_cast<long long>(a);
    return static_cast<long double>(n - (n - n % 3) /3 - (n - n % 5) / 5 + (n - n % 15) / 15);
}

long double binarySearch(long double low, long double high) {
    long double mid = (low + high) / 2;
    if (static_cast<long long>(numIndex(mid)) == N) {
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
        fout << static_cast<int>(binarySearch(0, 100000000000)) << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}