/*
ID: daniel25
TASK: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int A, B;
int numPalindromes;
int palindromes[11200];
int solutions[500];
int numSolutions;

bool is_prime(int a) {
    if (a < 5)
        return false;
    else if (a % 2 == 0 || a % 3 == 0)
        return false;

    int i = 5;
    while (i*i <= a) {
        if (a % i == 0 || a % (i+2) == 0)
            return false;
        i += 6;
    }

    return true;
}

bool is_palindrome(string s) {
    if (s.size() == 1 || s.size() == 0)
        return true;
    else if (s[0] == s[s.size()-1])
        return is_palindrome(s.substr(1, s.size()-2));
    else
        return false;
}

void generate_palindromes() {
    for (int d1 = 1; d1 <= 9; d1 += 2) {
        palindromes[numPalindromes] = d1;
        numPalindromes++;
        palindromes[numPalindromes] = d1 * 10 + d1;
        numPalindromes++;
        for (int d2 = 0; d2 <= 9; d2++) {
            palindromes[numPalindromes] = d1 * 100 + d2 * 10 + d1;
            numPalindromes++;
            palindromes[numPalindromes] = d1 * 1000 + d2 * 100 + d2 * 10 + d1;
            numPalindromes++;
            for (int d3 = 0; d3 <= 9; d3++) {
                palindromes[numPalindromes] = d1 * 10000 + d2 * 1000 + d3 * 100 + d2 * 10 + d1;
                numPalindromes++;
                palindromes[numPalindromes] = d1 * 100000 + d2 * 10000 + d3 * 1000 + d3 * 100 + d2 * 10 + d1;
                numPalindromes++;
                for (int d4 = 0; d4 <= 9; d4++) {
                    palindromes[numPalindromes] = d1 * 1000000 + d2 * 100000 + d3 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 + d1;
                    numPalindromes++;
                    palindromes[numPalindromes] = d1 * 10000000 + d2 * 1000000 + d3 * 100000 + d4 * 10000 + d4 * 1000 + d3 * 100 + d2 * 10 + d1;
                    numPalindromes++;
                }
            }
        }
    }
}

int main() {
//    cout << "1" << endl;
    ifstream fin("pprime.in");
    if (fin.is_open()) {
        fin >> A;
        fin >> B;
    } else cout << "error opening input file" << endl;
    fin.close();

//    cout << "2" << endl;

    generate_palindromes();
//    cout << "3" << endl;
    for (int i = 0; i < numPalindromes; i++)
        if (is_prime(palindromes[i]) && palindromes[i] <= B && palindromes[i] >= A) {
            solutions[numSolutions] = palindromes[i];
            numSolutions++;
        }
//    cout << "4" << endl;

//    cout << numPalindromes << endl;

    sort(solutions, solutions + numSolutions);
//    cout << "5" << endl;
    ofstream fout("pprime.out");
    if (fout.is_open()) {
        for (int i = 0; i < numSolutions; i++)
            fout << solutions[i] << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();
//    cout << "6" << endl;
    return 0;
}

