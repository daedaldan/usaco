/*
ID: daniel25
TASK: holstein
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct state {
    int size = 0;
    int feedTypes[15];
};

int V, G;
int vitaminNeeds[25];
int feeds[15][25];
int minScoops = 16;
state solution;

bool overlap(int i, state f) {
    for (int a = 0; a < f.size; a++)
        if (f.feedTypes[a] == i)
            return true;
    return false;
}

bool satisfiesNeeds(state f) {
    int vitaminCount[25];
    for (int i = 0; i < V; i++)
        vitaminCount[i] = 0;
    // feed types in state
    for (int i = 0; i < f.size; i++) {
        // vitamins in each feed type
        for (int j = 0; j < V; j++) {
            vitaminCount[j] += feeds[f.feedTypes[i]][j];
        }
    }

    for (int i = 0; i < V; i++)
        if (vitaminCount[i] < vitaminNeeds[i])
            return false;

    return true;
}

bool smallerFeedTypes(state f, state sol) {
    if (sol.size == 0)
        return true;
    int solCount = 0;
    int fCount = 0;
    for (int i = 0; i < f.size; i++)
        fCount += f.feedTypes[i];
    for (int i = 0; i < sol.size; i++)
        solCount += sol.feedTypes[i];

    return fCount < solCount;
}

bool isOptimal(state f) {
    if (f.size < minScoops && satisfiesNeeds(f))
        return true;
    if (f.size == minScoops && smallerFeedTypes(f, solution) && satisfiesNeeds(f))
        return true;
    return false;
}

int process(state f, queue<state> & unprocessed) {
    // if an optimal solution is found, return to avoid processing unnecessary states
    if (f.size > minScoops)
        return 1;

    // check is state is optimal
    if (isOptimal(f)) {
        minScoops = f.size;
        solution = f;
    }
    // enqueue next state
    for (int i = 0; i < G; i++) {
        state fCopy = f;
        if (!overlap(i, f)) {
            fCopy.feedTypes[f.size] = i;
            fCopy.size++;
            unprocessed.push(fCopy);
        }
    }

    return 0;
}

void bfs() {
    queue<state> unprocessedStates;
    // enqueue initial states
    for (int i = 0; i < G; i++) {
        state s = state();
        s.feedTypes[0] = i;
        s.size++;
        unprocessedStates.push(s);
    }

    // process states in bfs order
    while(!unprocessedStates.empty()) {
        state f = unprocessedStates.front();
        unprocessedStates.pop();
        if (process(f, unprocessedStates) == 1)
            return;
    }
}

int main() {
    // reading input
    ifstream fin("holstein.in");
    if (fin.is_open()) {
        fin >> V;
        for (int i = 0; i < V; i++)
            fin >> vitaminNeeds[i];
        fin >> G;
        for (int i = 0; i < G; i++)
            for (int j = 0; j < V; j++)
                fin >> feeds[i][j];
    } else cout << "error opening input file" << endl;
    fin.close();

    bfs();
    for (int i = 0; i < minScoops; i++)
        solution.feedTypes[i]++;

    sort(solution.feedTypes, solution.feedTypes+15);
    // writing output
    ofstream fout("holstein.out");
    if (fout.is_open()) {
        fout << minScoops << " ";
        for (int i = 0; i < 15; i++) {
            if (solution.feedTypes[i] != 0) {
                if (i != 14)
                    fout << solution.feedTypes[i] << " ";
                else
                    fout << solution.feedTypes[i] << "\n";
            }
        }
    } else cout << "error opening output file" << endl;
    fout.close();
}