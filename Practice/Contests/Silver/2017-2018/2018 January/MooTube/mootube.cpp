#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

struct neighbor {
    int neighbor;
    int relevance;
};

struct video {
    vector<neighbor> neighbors;
    bool visited;
};

struct question {
    int video;
    int k;
};

int N, Q;
video videos[5001];
int allKs[5001][5001];
question questions[5001];
int answers[5001];

void dfs(int source, int current, int min) {
    int originalMin = min;
    for (int i = 0; i < videos[current].neighbors.size(); i++) {
        if (videos[current].neighbors[i].neighbor != source && !videos[videos[current].neighbors[i].neighbor].visited) {
            videos[videos[current].neighbors[i].neighbor].visited = true;

            // check if relevance of this pair is < overall min
            if (videos[current].neighbors[i].relevance < min) {
                min = videos[current].neighbors[i].relevance;
            }

            // set relevance of this pair
            allKs[videos[current].neighbors[i].neighbor][source] = min;
            allKs[source][videos[current].neighbors[i].neighbor] = min;

            dfs(source, videos[current].neighbors[i].neighbor, min);
//            min = originalMin;
        }
    }
}

void randomInput() {
    ofstream fout("mootube.in");
    if (fout.is_open()) {
        srand(time(NULL));
        int randN = (rand() % 10 + 1), randQ = (rand() % 10 + 1);
        fout << randN << " " << randQ << "\n";
        for (int i = 0; i < randN; i++) {
            unordered_map<int, int> used;
            for (int j = 1; j <= N; j++)
                used[j] = 0;
            int a = -1, b = -1;
            while (!(a > 0 && a <= randN) && !(b > 0 && b <= randN) && (used[a] < 2) && (used[b] < 2)) {
                a = (rand() % 10 + 1);
                b = (rand() % 10 + 1);
            }
            fout << a << " " << b << " " << (rand() % 10 + 1) << "\n";
            used[a] += 1;
            used[b] += 1;
        }
        for (int i = 0; i < randQ; i++) {
            fout << (rand() % 10 + 1) << " " << (rand() % 10 + 1) << "\n";
        }
    } else cout << "error in opening random input file" << endl;
}

int main() {
//    randomInput();
    // reading input
    ifstream fin("mootube.in");
    if (fin.is_open()) {
        fin >> N >> Q;
        for (int i = 0; i < N-1; i++) {
            int a, b, relevance;
            fin >> a >> b >> relevance;
            neighbor aN;
            aN.neighbor = b;
            aN.relevance = relevance;
            neighbor bN;
            bN.neighbor = a;
            bN.relevance = relevance;
            videos[a].neighbors.push_back(aN);
            videos[b].neighbors.push_back(bN);
        }
        for (int i = 0; i < Q; i++) {
            fin >> questions[i].k >> questions[i].video;
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // find relevance of all pairs with DFS
    for (int i = 1; i <= N; i++) {
        videos[i].visited = true;
        dfs(i, i, 1000000001);
        for (int j = 1; j <= N; j++) {
            videos[j].visited = false;
        }
    }

    // answer questions
    for (int i = 0; i < Q; i++) {
        int numVideos = 0;
        int video = questions[i].video;
        int k = questions[i].k;
        for (int j = 1; j <= N; j++) {
            if (video != j && allKs[video][j] >= k) {
                numVideos++;
            }
        }
        answers[i] = numVideos;
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