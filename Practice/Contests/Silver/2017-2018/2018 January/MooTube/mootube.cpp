#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

struct video {
    int num;
    bool visited;
};

struct question {
    int video;
    int k;
};

struct relevance {
    unordered_map<int, int> Ks;
};

int N, Q;
relevance initialKs[5001];
int allKs[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 3, 2, 3},
        {0, 3, 0, 2, 4},
        {0, 2, 2, 0, 2},
        {0, 3, 4, 2, 0}
};
question questions[5000];
int answers[5000];

int main() {
    // reading input
    ifstream fin("mootube.in");
    if (fin.is_open()) {
        fin >> N >> Q;
        for (int i = 0; i < N-1; i++) {
            int a, b, relevance;
            fin >> a >> b >> relevance;
            initialKs[a].Ks[b] = relevance;
            initialKs[b].Ks[a] = relevance;
        }
        for (int i = 0; i < Q; i++) {
            fin >> questions[i].k >> questions[i].video;
            cout << questions[i].k << " " << questions[i].video << endl;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // find relevance of all pairs with DFS
    

    // answer questions
    for (int i = 0; i < Q; i++) {
        int numVideos = 0;
        int video = questions[i].video;
        int k = questions[i].k;
        for (int j = 1; j <= N; j++) {
            if (video != j)
                cout << video << " " << j << " " << allKs[video][j] << endl;
            if (video != j && allKs[video][j] >= k)
                numVideos++;
        }
        answers[i] = numVideos;
        cout << endl;
    }

    // writing output
    ofstream fout("mootube.out");
    if (fout.is_open()) {
        for (int i = 0; i < Q; i++) {
            fout << answers[i] << "\n";
        }
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}