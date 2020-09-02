#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int b[1000];
int possibleAs[500][1000];
int numPossibleAs;
int solution[5] = {3, 1, 5, 2, 4};

int main() {
    // reading input
    ifstream fin("photo.in");
    if (fin.is_open()) {
        fin >> N;
        for (int i = 0; i < N - 1; i++) {
            fin >> b[i];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // compute all possible As

    numPossibleAs = b[0] / 2 + 1;

    for (int i = 0; i < numPossibleAs; i++) {
        possibleAs[i][0] = i + 1;
        int j = 1;

        int usedDigits[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        bool cont = false;

        while (j < N) {
            possibleAs[i][j] = b[j - 1] - possibleAs[i][j-1];
            usedDigits[possibleAs[i][j]] += 1;

            if (usedDigits[possibleAs[i][j]] > 1 || possibleAs[i][j] > N) {
                cont = true;

                break;
            }

            j++;
        }

        if (!cont) {
            for (int a = 0; a < N; a++) {
                solution[a] = possibleAs[i][a];
            }

            break;
        }
    }

    // writing output
    ofstream fout("photo.out");
    if (fout.is_open()) {
        for (int i = 0; i < N; i++) {
            if (i == N - 1) {
                fout << solution[i];
            } else {
                fout << solution[i] << " ";
            }
        }

        fout << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}