#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct peak {
    long x;
    long y;
    long double leftM = 1.0;
    long double leftB;
    long double rightM = -1.0;
    long double rightB;
};

int N;
bool visiblePeaks[100000];
peak peaks[100000];
int numVisiblePeaks = 0;

long double findLinearX(long double y, long double m, long double b) {
    return (y - b) / m;
}

// checks if peak a is inside peak b
bool inside(long a, long b) {
    if (static_cast<long double>(peaks[a].x) > findLinearX(static_cast<long double>(peaks[a].y), peaks[b].leftM, peaks[b].leftB) &&
        static_cast<long double>(peaks[a].x) < findLinearX(static_cast<long double>(peaks[a].y), peaks[b].rightM, peaks[b].rightB)) {
        return true;
    } else if (static_cast<long double>(peaks[a].x) == findLinearX(static_cast<long double>(peaks[a].y), peaks[b].leftM, peaks[b].leftB) ||
               static_cast<long double>(peaks[a].x) == findLinearX(static_cast<long double>(peaks[a].y), peaks[b].rightM, peaks[b].rightB)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // reading input
    ifstream fin("mountains.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N; i++) {
            visiblePeaks[i] = true;
            peak p;
            fin >> p.x >> p.y;
            p.x += 1000000000;
            p.leftB = static_cast<long double>(p.y - p.x);
            p.rightB = static_cast<long double>(p.y + p.x);
            peaks[i] = p;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // check if peak i is inside peak j
            if (i != j && peaks[i].y <= peaks[j].y) {
                if (inside(i, j)) {
                    visiblePeaks[i] = false;
                    break;
                }
            }
        }
    }

    // writing output
    ofstream fout("mountains.out");
    if (fout.is_open()) {
        for (int i = 0; i < N; i++) {
            if (visiblePeaks[i])
                numVisiblePeaks++;
        }
        fout << numVisiblePeaks << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}