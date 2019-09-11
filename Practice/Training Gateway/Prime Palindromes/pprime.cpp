/*
ID: daniel25
TASK: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int A, B;
int numPalindromes;
int palindromes[100000000];
vector<int> solutions;

bool is_prime(int a) {
    if (a <= 3)
        return a > 1;
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
            for (int d2 = 0; d2 <= 9; d2++) {
                palindromes[numPalindromes] = d2*10 + d1;
                numPalindromes++;
                for (int d3 = 0; d3 <= 9; d3++) {
                    palindromes[numPalindromes] = d3* 100 + d2*10 + d1;
                    numPalindromes++;
                    for (int d4 = 0; d4 <= 9; d4++) {
                        palindromes[numPalindromes] = d4*1000 + d3* 100 + d2*10 + d1;
                        numPalindromes++;
                        for (int d5 = 0; d5 <= 9; d5++) {
                            palindromes[numPalindromes] = d5*10000 + d4*1000 + d3* 100 + d2*10 + d1;
                            numPalindromes++;
                            for (int d6 = 0; d6 <= 9; d6++) {
                                palindromes[numPalindromes] = d6*100000 + d5*10000 + d4*1000 + d3* 100 + d2*10 + d1;
                                numPalindromes++;
                                for (int d7 = 0; d7 <= 9; d7++) {
                                    palindromes[numPalindromes] = d7*1000000 + d6*100000 + d5*10000 + d4*1000 + d3* 100 + d2*10 + d1;
                                    numPalindromes++;
                                    for (int d8 = 0; d8 <= 9; d8++) {
                                        palindromes[numPalindromes] = d8*10000000 + d7*1000000 + d6*100000 + d5*10000 + d4*1000 + d3* 100 + d2*10 + d1;
                                        numPalindromes++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
}

int main() {
    ifstream fin("pprime.in");
    if (fin.is_open()) {
        fin >> A;
        fin >> B;
    } else cout << "error opening input file" << endl;
    fin.close();

//    for (A; A <= B; A++) {
//        if (is_prime(A) && is_palindrome(to_string(A))) solutions.push_back(A);
//    }

    generate_palindromes();
//    palindromes[numPalindromes] = 5;
//    numPalindromes++;
//    palindromes[numPalindromes] = 121;
//    numPalindromes++;
//    palindromes[numPalindromes] = 383;
//    numPalindromes++;
    for (int i = 0; i < numPalindromes; i++)
        if (is_prime(palindromes[i]))
            solutions.push_back(palindromes[i]);

    ofstream fout("pprime.out");
    if (fout.is_open()) {
        for (int i = 0; i < solutions.size(); i++)
            fout << solutions[i] << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}

