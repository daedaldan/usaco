#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct sellMilk {
    int gallons;
    int price;
    // in decreasing order
    bool operator<(const sellMilk & rhs) const {
        return price > rhs.price;
    }
};

int N, M, R;
int production[100000];
sellMilk sell[100000];
int rent[100000];
int maxProfit[100000];

bool decreaseCmp(int a, int b) {
    return a > b;
}

int main() {
    // reading input
    ifstream fin("rental.in");
    if (fin.is_open()) {
        fin >> N >> M >> R;
        // cow production
        for (int i = 0; i < N; i++) {
            fin >> production[i];
        }
        sort(production, production+N);
        // selling milk
        for (int i = 0; i < M; i++) {
            fin >> sell[i].gallons >> sell[i].price;
        }
        sort(sell, sell+M);
        // renting cows
        for (int i = 0; i < R; i++) {
            fin >> rent[i];
        }
        sort(rent, rent+R, decreaseCmp);
    } else cout << "error opening input file" << endl;
    fin.close();

    int index = 0;
    for (int i = 1; i < R; i++) {
        maxProfit[i+1] = maxProfit[i];
        while (index < M || production[i] > 0) {
            if (production[i] > sell[index].gallons) {
                production[i] -= sell[index].gallons;
                maxProfit[i+1];
                sell[index].gallons = 0;

            }
            if (sell[i].gallons > 0) {
                index++;
            }
        }
    }

    // writing output
    ofstream fout("rental.out");
    if (fout.is_open()) {

    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}