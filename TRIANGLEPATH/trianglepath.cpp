#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_TRIANGLE_SIZE = 100;

int triangle[MAX_TRIANGLE_SIZE][MAX_TRIANGLE_SIZE];
int cache[MAX_TRIANGLE_SIZE][MAX_TRIANGLE_SIZE];
int triangleSize;

int maxPath(int row, int col) {
    if (row + 1 == triangleSize) return triangle[row][col];
    int & ret = cache[row][col];
    if (ret != 0) return ret;
    ret = max(maxPath(row + 1, col), maxPath(row + 1, col + 1)) + triangle[row][col];
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;

    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        cin >> triangleSize;
        for (int i = 0; i < triangleSize; i++) {
            for (int j = 0; j <= i; j++) {
                cin >> triangle[i][j];
            }
        }
        memset(cache, 0, sizeof(cache));
        cout << maxPath(0, 0) << '\n';
    }


    return 0;
}