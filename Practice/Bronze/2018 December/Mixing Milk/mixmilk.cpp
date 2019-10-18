#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct bucket {
    int size;
    int milk;
};

bucket a;
bucket b;
bucket c;
int pours = 0;

void pour(bucket & a, bucket & b) {
    int space = b.size - b.milk;
    if (a.milk <= space) {
        b.milk += a.milk;
        a.milk = 0;
    } else {
        b.milk += space;
        a.milk -= space;
    }
}

int main() {
    // reading input
    ifstream fin("mixmilk.in");
    if (fin.is_open()) {
        fin >> a.size;
        fin >> a.milk;
        fin >> b.size;
        fin >> b.milk;
        fin >> c.size;
        fin >> c.milk;
    } else cout << "error opening input file" << endl;
    fin.close();

    while (pours < 100) {
        if (pours % 3 == 0)
            pour(a, b);
        else if (pours % 3 == 1)
            pour(b, c);
        else
            pour(c, a);

        pours++;
    }

    // writing output
    ofstream fout("mixmilk.out");
    if (fout.is_open()) {
        fout << a.milk << "\n";
        fout << b.milk << "\n";
        fout << c.milk << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}