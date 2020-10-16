#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_BOARD_SIZE = 100;
const int MAX_HOP = 9;

int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int checkVisit[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

bool findRoute(int row, int col) {
    if (row == 0 && col == 0) return true;
    // check up side
    for (int i = 1; i <= MAX_HOP; ++i) {
        int rowIdx = row - i;
        if (rowIdx < 0) break;
        // if jump is available and cell has not been visited, execute findRoute
        if (board[rowIdx][col] == i && checkVisit[rowIdx][col] == 0) {
            checkVisit[rowIdx][col] = 1;
            if (findRoute(rowIdx, col)) return true;
        }
    }
    // check left side
    for (int i = 1; i <= MAX_HOP; ++i) {
        int colIdx = col - i;
        if (colIdx < 0) break;
        // if jump is available and cell has not been visited, execute findRoute
        if (board[row][colIdx] == i && checkVisit[row][colIdx] == 0) {
            checkVisit[row][colIdx] = 1;
            if (findRoute(row, colIdx)) return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int numOfTestCases;

    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        int boardSize;
        memset(checkVisit, 0, sizeof(checkVisit));
        cin >> boardSize;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                cin >> board[i][j];
            }
        }
        if (findRoute(boardSize - 1, boardSize - 1)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}