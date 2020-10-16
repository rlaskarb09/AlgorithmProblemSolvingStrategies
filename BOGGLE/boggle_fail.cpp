#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#define MAX_TEST_CASE_NUM 50
#define MAX_WORD_LEN 10
#define MAX_WORD_NUM 10
#define BOARD_SIZE 5
#define NUM_OF_DIRECTION 8

using namespace std;

char board[BOARD_SIZE][BOARD_SIZE];
char words[MAX_WORD_NUM][MAX_WORD_LEN + 1];
char word[MAX_WORD_LEN + 1];
char wordLen = 0;
int rowMove[NUM_OF_DIRECTION] = {1, 1, 1, -1, -1, -1, 0, 0};
int colMove[NUM_OF_DIRECTION] = {1, -1, 0, 1, -1, 0, 1, -1};

bool hasWord(int wordIdx, int row, int col) {
    if (wordIdx >= wordLen) {
        return true;
    }
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }
    if (board[row][col] == word[wordIdx]) {
        for (int dirIdx = 0; dirIdx < NUM_OF_DIRECTION; ++ dirIdx) {
            if (hasWord(wordIdx + 1, row + rowMove[dirIdx], col + colMove[dirIdx])) {
                return true;
            }
        }
    }
    return false;
}

int main () {
    int numOfTestCases = 0;
    int numOfWords = 0;
    bool foundWord = false;

    scanf("%d", &numOfTestCases);
    for (int i = 0; i < numOfTestCases; ++i) {
        // Get board input
        char boardRowInput[BOARD_SIZE + 1];
        for(int j = 0; j < BOARD_SIZE; ++j) {
            scanf("%s", boardRowInput);
            for (int k = 0; k < BOARD_SIZE; ++k) {
                board[j][k] = boardRowInput[k];
            }
        }

        scanf("%d", &numOfWords);
        for (int j = 0; j < numOfWords; ++j) {
            scanf("%s", word);
            wordLen = strlen(word);
            foundWord = false;
            for (int rowIdx = 0; rowIdx < BOARD_SIZE; ++rowIdx) {
                for (int colIdx = 0; colIdx < BOARD_SIZE; ++colIdx) {
                    if (hasWord(0, rowIdx, colIdx)) {
                        foundWord = true;
                        break;
                    }
                }
                if (foundWord) break;
            }
            if (foundWord) {
                printf("%s YES\n", word);
            } else {
                printf("%s NO\n", word);
            }
        }
    }
    return 0;
}