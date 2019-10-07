/*
ID: daniel25
TASK: ride
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

int main() {
    int i = 0;
    int test = 0;
    auto start = chrono::high_resolution_clock::now();
    while (i < 2000000000) {
        i += 1;
        test += 1*200;
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << duration.count() << endl;
}