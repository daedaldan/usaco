/*
ID: daniel25
TASK: ttwo
LANG: C++
*/

#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

struct direction {
    int row;
    int col;
};

int farmerVisited[10][10][4];
int cowVisited[10][10][4];
char grid[10][10];
int farmerDirection = 0;
int cowDirection = 0;
int farmerLocation[2];
int cowLocation[2];
int minutes = 0;

void printGrid() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
direction directionXY(int i) {
    direction d;
    if (i == 0) {
        d.row = -1;
        d.col = 0;
    } else if (i == 1) {
        d.row = 0;
        d.col = 1;
    } else if (i == 2) {
        d.row = 1;
        d.col = 0;
    } else if (i == 3) {
        d.row = 0;
        d.col = -1;
    } else {
        cout << "invalid directionXY input" << endl;
        cout << i << endl;
    }

    return d;
}

bool obstacleOrWall(char entity) {
    if (entity == 'F') {
        if (grid[farmerLocation[0] + directionXY(farmerDirection).row][farmerLocation[1] + directionXY(farmerDirection).col] != '*'
           && farmerLocation[0] + directionXY(farmerDirection).row >= 0
           && farmerLocation[0] + directionXY(farmerDirection).row <= 9
           && farmerLocation[1] + directionXY(farmerDirection).col >= 0
           && farmerLocation[1] + directionXY(farmerDirection).col <= 9) {
            return false;
        }
    } else if (entity == 'C') {
        if (grid[cowLocation[0] + directionXY(cowDirection).row][cowLocation[1] + directionXY(cowDirection).col] != '*'
            && cowLocation[0] + directionXY(cowDirection).row >= 0
            && cowLocation[0] + directionXY(cowDirection).row <= 9
            && cowLocation[1] + directionXY(cowDirection).col >= 0
            && cowLocation[1] + directionXY(cowDirection).col <= 9) {
            return false;
        }
    } else {
        cout << "invalid input for obstacleOrWall" << endl;
    }

    return true;
}

void rotate(char entity) {
    if (entity == 'F') {
        if (farmerDirection < 3) {
            farmerDirection++;
        } else {
            farmerDirection = 0;
        }
    } else if (entity == 'C') {
        if (cowDirection < 3) {
            cowDirection++;
        } else {
            cowDirection = 0;
        }
    } else {
        cout << "invalid rotation input" << endl;
    }
}

int main() {
    // reading input
    ifstream fin("ttwo.in");
    if (fin.is_open()) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                fin >> grid[i][j];
                if (grid[i][j] == 'C') {
                    cowLocation[0] = i;
                    cowLocation[1] = j;
                } else if (grid[i][j] == 'F') {
                    farmerLocation[0] = i;
                    farmerLocation[1] = j;
                }
            }
        }
    } else cout << "error opening input file" << endl;
    fin.close();

    // simulating movement of farmer and cow
    while (cowLocation[0] != farmerLocation[0] || cowLocation[1] != farmerLocation[1]) {
        if (farmerDirection < 0 || farmerDirection > 3) {
            cout << farmerDirection << endl;
        }

        // check if cycle has occured
        if (farmerVisited[farmerLocation[0]][farmerLocation[1]][farmerDirection] > 2 && cowVisited[cowLocation[0]][cowLocation[1]][cowDirection] > 2) {
            cout << "cycle has occurred at minute " << minutes << " with farmer and cow at: " << endl;
            cout << "   farmer: " << farmerLocation[0] << ", " << farmerLocation[1] << endl;
            cout << "   cow: " << cowLocation[0] << ", " << cowLocation[1] << endl;
            minutes = 0;
            break;
        }

        // check if rotation for farmer is necessary
        if (obstacleOrWall('F')) {
            rotate('F');
        } else {
            // mark current spot as visited
            farmerVisited[farmerLocation[0]][farmerLocation[1]][farmerDirection]++;
            // move farmer in appropriate direction and update location
            direction d = directionXY(farmerDirection);
            int i = cowDirection;
            grid[farmerLocation[0]+d.row][farmerLocation[1]+d.col] = 'F';
            grid[farmerLocation[0]][farmerLocation[1]] = '.';
            farmerLocation[0] += d.row;
            farmerLocation[1] += d.col;
        }

        // check if rotation for cow is necessary
        if (obstacleOrWall('C')) {
            rotate('C');
        } else {
            // mark current spot as visited
            cowVisited[cowLocation[0]][cowLocation[1]][cowDirection]++;
            // move cow in appropriate direction and and update location
            direction d = directionXY(cowDirection);
            grid[cowLocation[0]+d.row][cowLocation[1]+d.col] = 'C';
            grid[cowLocation[0]][cowLocation[1]] = '.';
            cowLocation[0] += d.row;
            cowLocation[1] += d.col;
        }

//        printGrid();
        minutes++;
//        cout << minutes << endl;
    }

    // writing output
    ofstream fout("ttwo.out");
    if (fout.is_open()) {
        fout << minutes << "\n";
    } else cout << "error opening output file" << endl;
    fout.close();

    return 0;
}