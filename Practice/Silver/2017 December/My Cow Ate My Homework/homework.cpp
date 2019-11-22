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
    // slow (incorrect) algorithm
//    int maxScoreSlow = -1;
//    int bestKSlow = -1;
//    for (int k = 1; k <= N-2; k++) {
//        int count = 0;
//        int lowest = 1000000000;
//        int total = 0;
//        for (int i = k; i < N; i++) {
//            count++;
//            total += scores[i];
//            if (scores[i] < lowest)
//                lowest = scores[i];
//        }
//        if ((total-lowest)/(count-1) >= maxScoreSlow) {
//            maxScoreSlow = (total-lowest)/(count-1);
//            bestKSlow = k;
//        }
//        cout << k << " " << (total-lowest)/(count-1) << endl;
//    }
//    cout << bestKSlow << endl;

    // find lowest score for each interval
    int lowestInInterval = 1000000000;
    for (int i = N-1; i >= 0; i--) {
        if (scores[i] < lowestInInterval) {
            lowestInInterval = scores[i];
        }
        lowestScores[i] = lowestInInterval;
    }

    for (int k = 1; k <= N-2; k++) {
        int intervalScoreAverage = (scoreSums[N-1] - scoreSums[k-1] - lowestScores[k]) / (N-k-1);
        if (intervalScoreAverage > highestAverage) {
            highestAverage = intervalScoreAverage;
            bestKs[0] = k;
            numBestKs = 1;
        } else if (intervalScoreAverage == highestAverage) {
            bestKs[numBestKs] = k;
            numBestKs++;
        }
//        cout << k << " " << intervalScoreAverage << " " << lowestScores[k] << endl;
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