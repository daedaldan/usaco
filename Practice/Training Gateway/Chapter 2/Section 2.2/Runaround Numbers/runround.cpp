/*
ID: daniel25
TASK: runround
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

struct num {
    int size = 0;
    int digits[9];
};

unsigned long int M;

int numDigits(unsigned long int i) {
    int length = 1;
    while (i /= 10)
        length++;

    return length;
}

int nextIndex(num n, unsigned long int i) {
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
        // catalog # of each digit
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
    // check that all digits were touched and are unique
    for (int i = 0; i < n.size; i++) {
        if (touched[i] != 1 || digitUniqueness[n.digits[i]] > 1)
            return false;
    }

    return true;
}

num intToNum(int i) {
    num n;
    int length = numDigits(i);
    n.size = length;
    int index = length-1;
    while (i > 0) {
        int digit = i % 10;
        i /= 10;
        n.digits[index] = digit;
        index -= 1;
    }

    return n;
}

int main() {
    // reading input
    ifstream fin("runround.in");
    if (fin.is_open()) {
        fin >> M;
    } else cout << "error opening input file" << endl;
    fin.close();

    unsigned long int i = M+1;
    while (!isRunaround(intToNum(i))) {
        cout << i << endl;
        i++;
    }

    // writing output
    ofstream fout("runround.out");
    if (fout.is_open()) {
        fout << i << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}