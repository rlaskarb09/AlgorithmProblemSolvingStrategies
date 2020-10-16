#include <iostream>
#include <cstring>
#include <vector>
#include <set>

#define MAX_NUM_OF_TEST_CASES 50
#define MAX_NUM_OF_FRIENDS 10
#define MAX_NUM_OF_PAIRS 45

using namespace std;

int numOfTestCases = 0;
int numOfPairCases = 0;
int numOfPairedFriends = 0;
vector<pair<int, int>> pairs;
bool isSelected[MAX_NUM_OF_FRIENDS];

void initIsSelected() {
    for (int i = 0; i < MAX_NUM_OF_FRIENDS; ++i) {
        isSelected[i] = false;
    }
}

void findFriends(int remainNumOfPairs, vector<pair<int, int>>::iterator currentIter) {
    if (remainNumOfPairs == 1 && !isSelected[currentIter->first] && !isSelected[currentIter->second]) {
        numOfPairCases++;
        return;
    }
    if (!isSelected[currentIter->first] && !isSelected[currentIter->second]) {
        isSelected[currentIter->first] = true;
        isSelected[currentIter->second] = true;
        for (auto iter = currentIter + 1; iter != pairs.end(); iter++) {
            findFriends(remainNumOfPairs - 1, iter);
        }
        isSelected[currentIter->first] = false;
        isSelected[currentIter->second] = false;
    }
}

int main() {
    int numOfFriends;
    int numOfPairs;


    scanf("%d", &numOfTestCases);

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        pairs.clear();
        // Get input
        scanf("%d %d", &numOfFriends, &numOfPairs);
        for (int i = 0; i < numOfPairs; i++) {
            int firstFriend, secondFriend;
            scanf("%d %d", &firstFriend, &secondFriend);
            pairs.push_back(make_pair(firstFriend, secondFriend));
        }
        numOfPairCases = 0;
        initIsSelected();
        for (auto iter = pairs.begin(); iter != pairs.end(); iter++) {
            findFriends(numOfFriends / 2, iter);
        }

        printf("%d\n", numOfPairCases);
    }

    return 0;
}