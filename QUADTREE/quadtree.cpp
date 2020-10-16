#include <bits/stdc++.h>

const int MAX_TEST_CASES = 50;
const int MAX_INPUT_LEN = 1000;
const int MAX_PIXEL_SIZE = (2 << 20);

using namespace std;

int numOfTestCases;
char inputStr[MAX_INPUT_LEN + 1];
char resultStr[MAX_INPUT_LEN + 1];


pair<vector<char>, vector<char>::iterator> quadTree(vector<char>::iterator iter) {
    if ((*iter) == 'w' || (*iter) == 'b') {
        vector<char> returnVector(1, (*iter));
        return make_pair(returnVector, iter + 1);
    }
    auto returnPair1 = quadTree(iter + 1);
    auto returnPair2 = quadTree(returnPair1.second);
    auto returnPair3 = quadTree(returnPair2.second);
    auto returnPair4 = quadTree(returnPair3.second);
    
    vector<char> returnVector(1, 'x');
    returnVector.insert(returnVector.end(), returnPair3.first.begin(), returnPair3.first.end());
    returnVector.insert(returnVector.end(), returnPair4.first.begin(), returnPair4.first.end());
    returnVector.insert(returnVector.end(), returnPair1.first.begin(), returnPair1.first.end());
    returnVector.insert(returnVector.end(), returnPair2.first.begin(), returnPair2.first.end());

    return make_pair(returnVector, returnPair4.second);
}

int main() {
    scanf("%d", &numOfTestCases);
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        scanf("%s", inputStr);
        vector<char> inputVector(inputStr, inputStr + strlen(inputStr));
        pair<vector<char>, vector<char>::iterator> result = quadTree(inputVector.begin());
        memset(resultStr, 0, sizeof(resultStr));
        
        copy(result.first.begin(), result.first.end(), resultStr);
        printf("%s\n", resultStr);
    }

    return 0;
}