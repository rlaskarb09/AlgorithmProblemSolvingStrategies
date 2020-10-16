#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_GUARD_POSTS = 100;
const double CASTLE_RADIUS = 8.0;
const int INF = 987654321;
const double PI = 2.0 * acos(0);
int numOfGuardPosts;

vector<pair<double, double>> ranges;

pair<double, double> getRange(double xPos, double yPos, double radius) {
    if (radius >= 16.0) return make_pair(0, 2 * PI);
    double centerAngle = fmod(2 * PI + atan2(yPos, xPos), 2 * PI);
    double theta = 2.0 * asin(radius / 2.0 / 8.0);

    return make_pair(centerAngle - theta, centerAngle + theta);
}

int solveLinear(double begin, double end)
{
    int used = 0, idx = 0;
    while (begin < end)
    {
        double maxCover = -1;
        while (idx < numOfGuardPosts && ranges[idx].first <= begin)
        {
            maxCover = max(maxCover, ranges[idx].second);
            idx++;
        }
        if (maxCover <= begin)
            return INF;
        begin = maxCover;
        used++;
    }
    return used;
}

int findMinNumOfGps() {
    int result = INF;

    for (int i = 0; i < numOfGuardPosts; i++) {
        if (ranges[i].first <= 0 || ranges[i].second >= 2 * PI)
        {
            double begin = fmod(ranges[i].second, 2 * PI);
            double end = fmod(ranges[i].first + 2 * PI, 2 * PI);
            result = min(result, 1 + solveLinear(begin, end));
        }
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;
    cin >> numOfTestCases;
    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        ranges.clear();
        cin >> numOfGuardPosts;
        for (int i = 0; i < numOfGuardPosts; ++i) {
            double xPos, yPos, radius;
            cin >> yPos >> xPos >> radius;
            ranges.push_back(getRange(xPos, yPos, radius));
        }
        sort(ranges.begin(), ranges.end());

        int minNum = findMinNumOfGps();
        
        if (minNum == INF) cout << "IMPOSSIBLE\n";
        else {
            cout.precision(9);
            cout << minNum << '\n';
        }
    }

    return 0;
}