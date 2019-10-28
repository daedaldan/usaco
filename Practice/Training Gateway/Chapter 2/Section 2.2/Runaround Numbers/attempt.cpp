/*
ID: daniel25
TASK: runround
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <unordered_set>

using namespace std;

struct num {
    int size = 0;
    int falseSize = 0;
    int digits[9];
};

unsigned long int M;
string solution;

int numDigits(unsigned long int i) {
    int length = 1;
    while (i /= 10)
        length++;

    return length;
}

num intToNum(unsigned long int i) {
    num n;
    int length = numDigits(i);
    n.size = length;
    n.falseSize = length;
    int index = length-1;
    while (i > 0) {
        int digit = i % 10;
        i /= 10;
        n.digits[index] = digit;
        index -= 1;
    }

    return n;
}

unsigned long numToInt(num n) {
    unsigned long a = 0;
    int powerTen = n.size-1;
    for (int i = 0; i < n.size; i++) {
        a += n.digits[i] * pow(10, powerTen);
        powerTen--;
    }

    return a;
}

int nextIndex(num n, int i) {
    if (n.digits[i] == n.size) {
        return i;
    } else if (i+n.digits[i] <= n.size-1) {
        return i + n.digits[i];
    } else {
        i = (i + n.digits[i]) - n.size;
        while (i > n.size-1)
            i -= n.size;
        return i;
    }
}

bool isRunaround(num n) {
    int a = 0;
    int touched[9];
    int digitUniqueness[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < n.size; i++) {
        // check that no digits are equal to zero
        if (n.digits[i] == 0)
            return false;
        // catalog # of times each digit was checked
        digitUniqueness[n.digits[a]] += 1;
        // catalog which digits were checked
        touched[a] = 1;
        // advance index
        a = nextIndex(n, a);
    }
    touched[a] = 1;
    // check that last landed on digit is first one
    if (a != 0)
        return false;
    // check that all digits were checked and checked only once
    for (int i = 0; i < n.size; i++) {
        if (touched[i] != 1 || digitUniqueness[n.digits[i]] > 1)
            return false;
    }

    return true;
}

int solveNDigits(num & start, num & end, int availableDigits[]) {
    if (end.size >= start.falseSize) {
        if (isRunaround(end)) {
            if (numToInt(end) > numToInt(start)) {
                return 1;
            } else {
                if (numToInt(end) == numToInt(start)-1)
                    start.size++;
                return -1;
            }
        } else {
            return -1;
        }
    } else {
        int originalDigits[9];
        for (int i = 0; i < 9; i++)
            originalDigits[i] = availableDigits[i];
        num originalEnd;
        originalEnd.size = end.size;
        for (int i = 0; i < originalEnd.size; i++)
            originalEnd.digits[i] = end.digits[i];
        for (int i = 0; i < 9; i++) {
            if (availableDigits[i] != -1) {
                end.digits[end.size] = availableDigits[i];
                end.size++;
                availableDigits[i] = -1;
                // try solving with this value
                if (solveNDigits(start, end, availableDigits) == 1) {
                    return 1;
                } else {
                    // reset variables to original
                    for (int i = 0; i < 9; i++)
                        availableDigits[i] = originalDigits[i];
                    for (int i = 0; i < originalEnd.size; i++)
                        end.digits[i] = originalEnd.digits[i];
                    end.size = originalEnd.size;
                }
            }
        }
    }

    return -1;
}

int main() {
    // reading input
    ifstream fin("runround.in");
    if (fin.is_open()) {
        fin >> M;
    } else cout << "error opening input file" << endl;
    fin.close();

    num numM = intToNum(M);
    num empty;
    int availableDigits[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int output = solveNDigits(numM, empty, availableDigits);
    while (output == -1) {
        numM.falseSize++;
        output = solveNDigits(numM, empty, availableDigits);
    }
    solution = to_string(numToInt(empty));

    // writing output
    ofstream fout("runround.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}