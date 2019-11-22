#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int test1[] = {1, 3, 6, 8, 9, 11, 14, 17, 20, 42};
int array_size = 10;

int binarySearch(int arr[], int find, int start, int end) {
    int mid = -1;
    while (start <= end) {
        mid = (start + end) / 2;
        cout << start << " " << end << " " << mid << endl;
        if (arr[mid] < find) {
            start = mid + 1;
        } else if (arr[mid] > find) {
            end = mid - 1;
        } else {
            return mid;
        }
    }

    if (arr[mid] == find) {
        return mid;
    } else {
        return -1;
    }
}

int main() {
    cout << binarySearch(test1, 20, 0, array_size-1) << endl;

    return 0;
}