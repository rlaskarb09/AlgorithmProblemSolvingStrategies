#include <bits/stdc++.h>

using namespace std;

const int MAX_INPUT_SIZE = 10000;

int numOfLunchboxs;
int hitTimes[MAX_INPUT_SIZE];
vector<pair<int, int>> schedule;    // pair<int -eatingTime, int hittingTime>

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;
    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        schedule.clear();
        cin >> numOfLunchboxs;
        for (int i = 0; i < numOfLunchboxs; ++i) {
            cin >> hitTimes[i];
        }
        for (int i = 0; i < numOfLunchboxs; ++i) {
            int eatTime;
            cin >> eatTime;
            schedule.push_back(make_pair(-eatTime, hitTimes[i]));
        }
        sort(schedule.begin(), schedule.end());

        int totalLunchTime = 0;
        int eatBeginTime = 0;
        for (int i = 0 ; i < numOfLunchboxs; ++i) {
            eatBeginTime += schedule[i].second;
            totalLunchTime = max(totalLunchTime, eatBeginTime - schedule[i].first);
        }
        cout << totalLunchTime << '\n';
    }
    return 0;
}