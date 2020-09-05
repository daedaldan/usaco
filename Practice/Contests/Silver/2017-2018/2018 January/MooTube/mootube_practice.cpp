#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct neighbor {
    int neighbor;
    int relevance;
};

struct video {
    vector<neighbor> neighbors;
    bool visited = false;
};

struct question {
    int video;
    int k;
};

int N, Q;
video videos[5001];
question questions[5001];
int answers[5001];

void process(queue<int> & states, int state, int k, int answer) {
    for (int i = 0; i < videos[state].neighbors.size(); i++) {
        if (videos[state].neighbors[i].relevance < k || videos[videos[state].neighbors[i].neighbor].visited) {
            continue;
        } else {
            videos[videos[state].neighbors[i].neighbor].visited = true;
            answers[answer] += 1;
            states.push(videos[state].neighbors[i].neighbor);
        }
    }
}

void bfs(int source, int k, int answer) {
    queue<int> states;
    states.push(source);
    while (!states.empty()) {
        int state = states.front();
        videos[state].visited = true;
        states.pop();
        process(states, state, k, answer);
    }
}

int main() {
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

    for (int i = 0; i < Q; i++) {
        bfs(questions[i].video, questions[i].k, i);
        for (int i = 1; i <= N; i++) {
            videos[i].visited = false;
        }
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