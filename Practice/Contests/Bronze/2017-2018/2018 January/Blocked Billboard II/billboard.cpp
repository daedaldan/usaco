#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct point {
    int x;
    int y;
};

struct billboard {
    point upperRight;
    point lowerLeft;
};

billboard lawnmower;
billboard cow;
long minArea;

int main() {
    // reading input
    ifstream fin("billboard.in");
    if (fin.is_open()) {
        int x;
        int y;
        // coordinates for lawnmower billboard
        fin >> x;
        fin >> y;
        lawnmower.lowerLeft.x = x + 1000;
        lawnmower.lowerLeft.y = y + 1000;
        fin >> x;
        fin >> y;
        lawnmower.upperRight.x = x + 1000;
        lawnmower.upperRight.y = y + 1000;
        // coordinates for cow feed billboard
        fin >> x;
        fin >> y;
        cow.lowerLeft.x = x + 1000;
        cow.lowerLeft.y = y + 1000;
        fin >> x;
        fin >> y;
        cow.upperRight.x = x + 1000;
        cow.upperRight.y = y + 1000;
    } else cout << "error opening input file" << endl;
    fin.close();

    long width = lawnmower.upperRight.x - lawnmower.lowerLeft.x;
    long height = lawnmower.upperRight.y - lawnmower.lowerLeft.y;
    if (cow.lowerLeft.x <= lawnmower.lowerLeft.x && cow.upperRight.x >= lawnmower.upperRight.x
        && cow.lowerLeft.y <= lawnmower.lowerLeft.y && cow.upperRight.y >= lawnmower.upperRight.y) {
        // cow billboard covers all of lawnmower billboard
        width = 0;
        height = 0;
    } else if ((cow.upperRight.y < lawnmower.upperRight.y && cow.lowerLeft.y > lawnmower.lowerLeft.y)
               || (cow.lowerLeft.x > lawnmower.lowerLeft.x && cow.upperRight.x < lawnmower.lowerLeft.x)) {
        // cow billboard is in middle of lawnmower billboard
        ;
    } else if (cow.lowerLeft.x <= lawnmower.lowerLeft.x && cow.upperRight.x >= lawnmower.upperRight.x) {
            cout << "herasdfe" << endl;
            // cow billboard covers lawnmower billboard vertically
            if (cow.lowerLeft.y < lawnmower.upperRight.y && cow.lowerLeft.y > lawnmower.lowerLeft.y) {
                // overlap on top
                cout << "heare" << endl;
                height -= (lawnmower.upperRight.y - cow.lowerLeft.y);
            } else if (cow.upperRight.y > lawnmower.lowerLeft.y && cow.upperRight.y < lawnmower.upperRight.y) {
                // overlap on bottom
                cout << "here" << endl;
                height -= (cow.upperRight.y - lawnmower.lowerLeft.y);
            }
    } else if (cow.lowerLeft.y <= lawnmower.lowerLeft.y && cow.upperRight.y >= lawnmower.upperRight.y) {
        // cow billboard covers lawnmower billboard horizontally
        if (cow.lowerLeft.x > lawnmower.lowerLeft.x && cow.lowerLeft.x < lawnmower.upperRight.x) {
            // overlap on right
            width -= (lawnmower.upperRight.x - cow.lowerLeft.x);
        } else if (cow.upperRight.x > lawnmower.lowerLeft.x && cow.upperRight.x < lawnmower.upperRight.x) {
            // overlap on left
            width -= (cow.upperRight.x - lawnmower.lowerLeft.x);
        }
    }

    minArea = width * height;

    cout << minArea << endl;

    // writing output
    ofstream fout("billboard.out");
    if (fout.is_open()) {
        fout << minArea << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}