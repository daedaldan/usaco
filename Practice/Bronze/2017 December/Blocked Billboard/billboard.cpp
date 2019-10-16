#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct coord {
    int x;
    int y;
};

struct rect {
    coord lowerLeft;
    coord upperRight;
};

rect b1;
rect b2;
rect t;
int covered[2000][2000];

void cover(rect a) {
    for (int i = a.lowerLeft.x; i < a.upperRight.x; i++) {
        for (int j = a.lowerLeft.y; j < a.upperRight.y; j++) {
            covered[i][j]++;
        }
    }
}

int main() {
    // reading input
    ifstream fin("billboard.in");
    if (fin.is_open()) {
        fin >> b1.lowerLeft.x;
        fin >> b1.lowerLeft.y;
        fin >> b1.upperRight.x;
        fin >> b1.upperRight.y;
        fin >> b2.lowerLeft.x;
        fin >> b2.lowerLeft.y;
        fin >> b2.upperRight.x;
        fin >> b2.upperRight.y;
        fin >> t.lowerLeft.x;
        fin >> t.lowerLeft.y;
        fin >> t.upperRight.x;
        fin >> t.upperRight.y;
        b1.lowerLeft.x += 1000;
        b1.lowerLeft.y += 1000;
        b1.upperRight.x += 1000;
        b1.upperRight.y += 1000;
        b2.lowerLeft.x += 1000;
        b2.lowerLeft.y += 1000;
        b2.upperRight.x += 1000;
        b2.upperRight.y += 1000;
        t.lowerLeft.x += 1000;
        t.lowerLeft.y += 1000;
        t.upperRight.x += 1000;
        t.upperRight.y += 1000;
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < 2000; i++)
        for (int j = 0; j < 2000; j++)
            covered[i][j] = 0;

    int billboardArea = (b1.upperRight.x - b1.lowerLeft.x) * (b1.upperRight.y - b1.lowerLeft.y)
            + (b2.upperRight.x - b2.lowerLeft.x) * (b2.upperRight.y - b2.lowerLeft.y);
    int areaBlocked = 0;

    cover(b1);
    cover(b2);
    cover(t);

    for (int i = 0; i < 2000; i++)
        for (int j = 0; j < 2000; j++)
            if (covered[i][j] == 2) areaBlocked++;

    // writing output
    ofstream fout("billboard.out");
    if (fout.is_open()) {
        fout << billboardArea - areaBlocked << endl;
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}