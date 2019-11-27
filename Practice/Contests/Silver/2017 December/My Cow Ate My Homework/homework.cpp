#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int N;
int scores[100000];
int scoreSums[100000];
int lowestScores[100000];
double highestAverage = -1;
int bestKs[100000];
int numBestKs = 0;
int bestK = -1;

int main() {
    // reading input
    ifstream fin("homework.in");
    if (fin.is_open()) {
        fin >> N;
        // read in scores
        for (int i = 0; i < N; i++) {
            fin >> scores[i];
        }
        // calculate prefix sums
        scoreSums[0] = scores[0];
        for (int i = 1; i < N; i++) {
            scoreSums[i] = scores[i] + scoreSums[i-1];
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // find lowest score for each interval
    int lowestInInterval = 1000000000;
    for (int i = N-1; i >= 0; i--) {
        if (scores[i] < lowestInInterval) {
            lowestInInterval = scores[i];
        }
        lowestScores[i] = lowestInInterval;
    }

    for (int k = 1; k <= N-2; k++) {
        double intervalScoreAverage = (scoreSums[N-1] - scoreSums[k-1] - lowestScores[k]) / static_cast<double>(N-k-1);
        if (intervalScoreAverage > highestAverage) {
            highestAverage = intervalScoreAverage;
            bestKs[0] = k;
            numBestKs = 1;
        } else if (intervalScoreAverage == highestAverage) {
            bestKs[numBestKs] = k;
            numBestKs++;
        }
    }

    // writing output
    ofstream fout("homework.out");
    if (fout.is_open()) {
        for (int i = 0; i < numBestKs; i++)
            fout << bestKs[i] << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}