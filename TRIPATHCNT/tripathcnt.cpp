#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_TRIANGLE_SIZE = 100;

int triangle[MAX_TRIANGLE_SIZE][MAX_TRIANGLE_SIZE];
int pathCache[MAX_TRIANGLE_SIZE][MAX_TRIANGLE_SIZE];
int cntCache[MAX_TRIANGLE_SIZE][MAX_TRIANGLE_SIZE];
int triangleSize;

int maxPathCnt(int row, int col) {
    if (row + 1 == triangleSize) return triangle[row][col];
    int & path = pathCache[row][col];
    int & cnt = cntCache[row][col];
    if (path != 0) return path;
    int maxPath1 = maxPathCnt(row + 1, col); 
    int maxPath2 = maxPathCnt(row + 1, col + 1);
    if (maxPath1 == maxPath2) {
        path = maxPath1 + triangle[row][col];
        cnt = cntCache[row + 1][col] + cntCache[row + 1][col + 1];
    } else {
        path = max(maxPathCnt(row + 1, col), maxPathCnt(row + 1, col + 1)) + triangle[row][col];
        cnt = maxPath1 > maxPath2 ? cntCache[row + 1][col] : cntCache[row + 1][col + 1];       
    }
    
    return path;
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
        for (int i = 0; i < triangleSize; ++i) {
            cntCache[triangleSize - 1][i] = 1;
        }
        memset(pathCache, 0, sizeof(pathCache));
        maxPathCnt(0, 0);
        cout << cntCache[0][0] << '\n';
    }


    return 0;
}