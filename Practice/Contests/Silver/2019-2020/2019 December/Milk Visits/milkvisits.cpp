#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <unordered_set>

using namespace std;

struct farm {
    char cow;
    list<int> neighbors;
    bool visited = false;
    int component;
};

struct f {
    char prefer;
    int A;
    int B;
};

struct component {
    char cow;
    list<int> farms;
    int size = 0;
};

int N, M;
farm farms[100000];
f friends[100000];
component components[100000];
int numComponents = 0;
string solution;

void dfs(int source) {
    // update farm's info
    farms[source-1].component = numComponents;
    farms[source-1].visited = true;
    // update current component
    components[numComponents].farms.push_back(source);
    components[numComponents].size++;
    // loop through farm's neighbors to check which ones can be added to current component
    list<int>::iterator it;
    for (it = farms[source-1].neighbors.begin(); it != farms[source-1].neighbors.end(); ++it) {
        if (farms[*it-1].cow == farms[source-1].cow && !farms[*it-1].visited) {
            // add to current component
            dfs(*it);
        }
    }
}

void floodFill() {
    for (int i = 1; i <= N; i++) {
        if (!farms[i-1].visited) {
            components[numComponents].cow = farms[i-1].cow;
            dfs(i);
            numComponents++;
        }
    }
}

int main() {
    // reading input
    ifstream fin("milkvisits.in");
    if (fin.is_open()) {
        fin >> N >> M;
        string cowTypes;
        fin >> cowTypes;
        // cows on farms
        for (int i = 0; i < N; i++) {
            farms[i].cow = cowTypes[i];
        }
        // farm paths
        for (int i = 0; i < N-1; i++) {
            int a, b;
            fin >> a >> b;
            farms[a-1].neighbors.push_back(b);
            farms[b-1].neighbors.push_back(a);
        }
        // friends
        for (int i = 0; i < M; i++) {
            f a;
            fin >> a.A >> a.B >> a.prefer;
            friends[i] = a;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    floodFill();

    for (int i = 0; i < M; i++) {
        // path consists of one type of cow; check source to see whether it is friend's preference
        if (farms[friends[i].A-1].component == farms[friends[i].B-1].component) {
            if (farms[friends[i].A-1].cow == friends[i].prefer) {
                solution += "1";
            } else {
                solution += "0";
            }
        } // path includes farms from >1 component, which means that both types of cows will be present
        else {
            solution += "1";
        }
    }

    // writing output
    ofstream fout("milkvisits.out");
    if (fout.is_open()) {
        fout << solution << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}