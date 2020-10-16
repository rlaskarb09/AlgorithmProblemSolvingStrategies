#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_INPUT_SIZE = 100;

int numOfInput;


int main() {
    int numOfTestCases;
    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        priority_queue<int, vector<int>, greater<int>> priorityQ;
        cin >> numOfInput;
        for (int i = 0; i < numOfInput; ++i) {
            int inputNum;
            cin >> inputNum;
            priorityQ.push(inputNum);
        }
        if (numOfInput == 1) cout << "0\n";
        long long int cost = 0;
        while (priorityQ.size() >= 2) {
            int num1 = priorityQ.top();
            priorityQ.pop();
            int num2 = priorityQ.top();
            priorityQ.pop();
            cost += num1 + num2;
            priorityQ.push(num1 + num2);
        }
        cout << cost << '\n';
    }

    return 0;
}