#include <iostream>
#include <cstring>

#define MAX_HEIGHT 20
#define MAX_WIDTH 20
#define MAX_CASES 30
#define MAX_WHITES 50
#define NUM_OF_SHAPES 4

using namespace std;

int height = 0;
int width = 0;
int board[MAX_HEIGHT + 2][MAX_WIDTH + 2];
int numOfWhites = 0;
int numOfTestCases = 0;
int numOfCoverCases = 0;
int shapesRow[NUM_OF_SHAPES][3] = {{0, 0, 1}, {0, 0, 1}, {0, 1, 1}, {0, 1, 1}};
int shapesCol[NUM_OF_SHAPES][3] = {{0, 1, 0}, {0, 1, 1}, {0, 0, 1}, {0, 0, -1}};

void initBoard() {
    for (int i = 1; i <= MAX_HEIGHT; i++) {
        for (int j = 1; j <= MAX_WIDTH; j++) {
            board[i][j] = 1;
        }
    }
}

void printBoard() {
    for (int i = 1; i <= MAX_HEIGHT; i++) {
        for (int j = 1; j <= MAX_WIDTH; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

bool isBlockFit(int shapeIdx, int row, int col) {
    if (!board[row + shapesRow[shapeIdx][0]][col + shapesCol[shapeIdx][0]] &&
        !board[row + shapesRow[shapeIdx][1]][col + shapesCol[shapeIdx][1]] &&
        !board[row + shapesRow[shapeIdx][2]][col + shapesCol[shapeIdx][2]]) {
        return true;
    }
    return false;
}

bool fillBlock(int shapeIdx, int row, int col) {
    board[row + shapesRow[shapeIdx][0]][col + shapesCol[shapeIdx][0]] = 1;
    board[row + shapesRow[shapeIdx][1]][col + shapesCol[shapeIdx][1]] = 1;
    board[row + shapesRow[shapeIdx][2]][col + shapesCol[shapeIdx][2]] = 1;
}

bool emptyBlock(int shapeIdx, int row, int col) {
    board[row + shapesRow[shapeIdx][0]][col + shapesCol[shapeIdx][0]] = 0;
    board[row + shapesRow[shapeIdx][1]][col + shapesCol[shapeIdx][1]] = 0;
    board[row + shapesRow[shapeIdx][2]][col + shapesCol[shapeIdx][2]] = 0;
}

void findBlockCoverCases(int remainBlocks) {
    if (remainBlocks == 0) {
        numOfCoverCases += 1;
        return;
    }
    for (int rowIdx = 1; rowIdx <= height - 1; ++rowIdx) {
        for (int colIdx = 1; colIdx <= width; ++colIdx) {
            if (board[rowIdx][colIdx] == 0) {
                for (int shapeIdx = 0; shapeIdx < NUM_OF_SHAPES; ++shapeIdx) {
                    if (isBlockFit(shapeIdx, rowIdx, colIdx)) {
                        fillBlock(shapeIdx, rowIdx, colIdx);
                        findBlockCoverCases(remainBlocks - 1);
                        emptyBlock(shapeIdx, rowIdx, colIdx);
                    }
                }
                return;
            }
        }
    }    
}

int main() {
    char widthInput[MAX_HEIGHT + 1];
    for (int i = 0; i < MAX_HEIGHT + 2; i++) {
        for (int j = 0; j < MAX_WIDTH + 2; j++) {
            board[i][j] = 1;
        }
    }
    scanf("%d", &numOfTestCases);
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        // Get input for this case
        numOfCoverCases = 0;
        numOfWhites = 0;
        initBoard();
        scanf("%d %d", &height, &width);
        for (int i = 1; i <= height; ++i) {
            scanf("%s", widthInput);
            for (int j = 1; j <= width; ++j) {
                if (widthInput[j - 1] == '.') {
                    board[i][j] = 0;
                    numOfWhites++;
                }
            }
        }
        // printBoard();
        
        // Check before finding cover cases
        if (numOfWhites == 0) numOfCoverCases = 1;
        else if (numOfWhites % 3 != 0) numOfCoverCases = 0;
        // find cover cases
        else {
            findBlockCoverCases(numOfWhites / 3);
        }
        printf("%d\n", numOfCoverCases);
    }

    return 0;
}