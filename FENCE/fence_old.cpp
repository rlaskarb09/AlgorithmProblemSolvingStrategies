#include <bits/stdc++.h>

const int MAX_TEST_CASES = 50;
const int MAX_NUM_OF_FENCES = 20000;
const int MAX_FENCE_LENGTH = 10000;

int numOfTestCases;
int numOfFences;

int fences[MAX_NUM_OF_FENCES + 1];

using namespace std;

int calcMaxFenceArea(int* beginPtr, int* endPtr) {
    // one element -> return height
    if (beginPtr + 1 == endPtr) return (*beginPtr);
    // no element -> return 0
    if (beginPtr >= endPtr) return 0;

    int* minElement = min_element(beginPtr, endPtr);
    int currentMax = (endPtr - beginPtr) * (*minElement);
    int childMax = max(calcMaxFenceArea(beginPtr, minElement), calcMaxFenceArea(minElement + 1, endPtr));

    return max(currentMax, childMax);
}

int main() {
    scanf("%d", &numOfTestCases);
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        scanf("%d", &numOfFences);
        for (int i = 0; i < numOfFences; ++i) {
            scanf("%d", fences + i);
        }
        int result = calcMaxFenceArea(fences, fences + numOfFences);
        printf("%d\n", result);
    }
    return 0;
}