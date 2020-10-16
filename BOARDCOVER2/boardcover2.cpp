#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_BOARD_SIZE = 10;
const int MAX_BLOCK_SIZE = 10;

int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int block[MAX_BLOCK_SIZE][MAX_BLOCK_SIZE];

int boardRow, boardCol;
int blockRow, blockCol;
int blockSize;
int best;

vector<vector<pair<int,int>>> rotations;

vector<string> rotate(const vector<string>& arr) {
    vector<string> ret(arr[0].size(), string(arr.size(), ' '));
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr[0].size(); ++j) {
            ret[j][arr.size()-i-1]= arr[i][j];
        }
    }
    return ret;    
}

void generateRotations(vector<string> block) {
    rotations.clear();
    rotations.resize(4);
    for(int rot = 0;  rot < 4; ++rot) {
        int originRow = -1, originCol = -1;
        for (int i= 0; i < blockRow; ++i) {
            for (int j = 0; j < blockCol; ++j) {
                if (block[i][j] == '#') {
                    if (originRow == -1) {
                        originRow = i;
                        originCol = j;
                    }
                    rotations[rot].push_back(make_pair(i - originRow, j - originCol));
                }
            }
        }
        block = rotate(block);
    }
    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
    blockSize = rotations[0].size();
}

bool setBlock (int row, int col, const vector<pair<int, int>>& block, int delta) {
    if (delta == 1) {
        bool isCoverable = true;
        for (int i = 0; i < block.size(); ++i) {
            if (!(row + block[i].first >= 0 && col + block[i].second >= 0 && 
                board[row + block[i].first][col + block[i].second] == 0)) {
                isCoverable = false;
                break;
            }
        }
        if (isCoverable) {
            for (int i = 0; i < block.size(); ++i) {
                board[row + block[i].first][col + block[i].second] = 1;
            }
        }
        return isCoverable;
    }
    if (delta == -1) {
        for (int i = 0; i < block.size(); ++i) {
            board[row + block[i].first][col + block[i].second] = 0;
        }
        return true;
    }
}

void search(int placed) {
    int row = -1, col = -1;
    for(int i = 0; i < boardRow; ++i) {
        for (int j = 0; j< boardCol; ++j) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1) break;
    }
    if (row == -1) {
        best = max(best, placed);
        return;
    }
    for (int i = 0; i < rotations.size(); ++i) {
        if(setBlock(row,col, rotations[i], 1)) {
            search(placed + 1);
            setBlock(row, col, rotations[i], -1);
        }
    }
    board[row][col] = 1;
    search(placed);
    board[row][col] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfTestCases;
    cin >> numOfTestCases;
    string inputRow;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        vector<string> block;
        cin >> boardRow >> boardCol >> blockRow >> blockCol;
        for (int i = 0; i < boardRow; ++i) {
            cin >> inputRow;
            for (int j = 0; j < boardCol; ++j) {
                if (inputRow[i] == '#')
                    board[i][j] = 1;
                else
                    board[i][j] = 0;                
            }
        }
        for (int i = 0; i < blockRow; ++i) {
            string inputBlock;
            cin >> inputBlock;
            block.push_back(inputBlock);
        }

        generateRotations(block);
        best = 0;
        search(0);
        cout << best << '\n';
    }
    return 0;
}