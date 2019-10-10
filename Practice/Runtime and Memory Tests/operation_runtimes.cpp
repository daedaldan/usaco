/*
ID: daniel25
TASK: test
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
    chrono::time_point<std::chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();
    while (i < 100000000) {
        i += 1;
        int arr[1000000];
    }
    chrono::time_point<std::chrono::high_resolution_clock> stop = chrono::high_resolution_clock::now();
    cout << ((chrono::duration_cast<chrono::microseconds>(stop - start)).count() / 1000000.0) -  0.2724706 << " seconds" << endl;
}