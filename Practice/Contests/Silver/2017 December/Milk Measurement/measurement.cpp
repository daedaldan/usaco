#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct cow {
    int id;
    int production;
};

struct change {
    int day;
    int id;
    int change;
};

struct myDisplay {
    int myDisplay[1000000];
    int numCows = 0;
};

int N, G;
change changes[100000];
unordered_map<int, cow> cows;
unordered_set<int> cowIDs;
int display[1000000];
int numCowsOnDisplay;
int highestProduction;
int displayChanges = 0;

bool changesCmp (change a, change b) { return a.day < b.day; }

int onDisplay(int cowID, int myDisplay[], int numOnDisplay) {
    for (int i = 0; i < numOnDisplay; i++) {
        if (myDisplay[i] == cowID)
            return i;
    }

    return -1;
}

myDisplay newTop() {
    int newDisplay[1000000];
    int numNewCows = 0;
    int topProduction = cows[display[0]].production;
    for (auto it = cows.begin(); it != cows.end(); ++it) {
        int currentID = it->first;
        if (cows[currentID].production > topProduction) {
            // cow's new production is higher than current highest
            newDisplay[0] = currentID;
            numNewCows = 1;
            topProduction = cows[currentID].production;
        } else if (cows[currentID].production == topProduction && onDisplay(currentID, newDisplay, numNewCows) == -1) {
            // cow's new production now matches current highest
            newDisplay[numNewCows] = currentID;
            numNewCows++;
        }
    }

    myDisplay d;
    for (int i = 0; i < numNewCows; i++) {
        d.myDisplay[i] = newDisplay[i];
    }
    d.numCows = numNewCows;

    return d;
}

int main() {
    // reading input
    ifstream fin("measurement.in");
    if (fin.is_open()) {
        fin >> N;
        fin >> G;
        highestProduction = G;
        for (int i = 0; i < N; i++) {
            change c;
            fin >> c.day;
            fin >> c.id;
            fin >> c.change;
            changes[i] = c;
            cowIDs.insert(c.id);
        }
        numCowsOnDisplay = cowIDs.size();
        int i = 0;
        for (auto itr = cowIDs.begin(); itr != cowIDs.end(); ++itr) {
            cow a;
            a.id = *itr;
            a.production = G;
            cows[*itr] = a;
            display[i] = *itr;
            i++;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // sort updates by date
    sort(changes, changes+N, changesCmp);

    // process updates
    for (int i = 0; i < N; i++) {
        // update cow
        int currentID = changes[i].id;
        cows[currentID].production += changes[i].change;
        // see if change to wall must be made
        if (cows[currentID].production > highestProduction) {
            // cow's new production is higher than current highest
            display[0] = currentID;
            numCowsOnDisplay = 1;
            highestProduction = cows[currentID].production;
            displayChanges++;
        } else if (cows[currentID].production == highestProduction &&
                   onDisplay(currentID, display, numCowsOnDisplay) == -1) {
            // cow's new production now matches current highest
            display[numCowsOnDisplay] = changes[i].id;
            numCowsOnDisplay++;
            displayChanges++;
        } else if (changes[i].change < 0) {
            // cow's new production is less than current highest
            int onDisplayIndex = onDisplay(currentID, display, numCowsOnDisplay);
            // cow is no longer on display
            if (onDisplayIndex != -1 && numCowsOnDisplay > 1) {
                // remove cow from display
                for (int i = onDisplayIndex; i < numCowsOnDisplay; i++) {
                    display[i] = display[i + 1];
                }
                numCowsOnDisplay--;
                displayChanges++;
            } else if (numCowsOnDisplay == 1) { // other cows are now on display
                myDisplay d = newTop();
                cout << "here" << endl;
                if (d.numCows != 0) {
                    for (int i = 0; i < d.numCows; i++) {
                        display[i] = d.myDisplay[i];
                        numCowsOnDisplay = d.numCows;
                    }
                    displayChanges++;
                }
            }
        }
        cout << currentID << " " << changes[i].change << " " << displayChanges << endl;
    }

    // writing output
    ofstream fout("measurement.out");
    if (fout.is_open()) {
        fout << displayChanges << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}