#include <bits/stdc++.h>

using namespace std;

const int MAX_POINTS = 100;

int numOfPoints;
double dist[MAX_POINTS + 1][MAX_POINTS + 1];
pair<double, double> points[MAX_POINTS + 1];

bool decision (double d) {
    vector<bool> visited(numOfPoints, false);
    visited[0] = true;
    queue<int> q;
    q.push(0);
    int seen = 0;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        ++seen;
        for (int there = 0; there < numOfPoints; ++there) {
            if (!visited[there] && dist[here][there] <= d) {
                visited[there] = true;
                q.push(there);
            }
        }
    }
    return seen == numOfPoints;
}

double optimize() {
    double low = 0, high = 1416.00;
    for (int it = 0; it < 100; ++it) {
        double mid = (low + high) / 2;
        if (decision(mid))
            high = mid;
        else
            low = mid;        
    }
    return high;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int numOfTestCases;
    cin >> numOfTestCases;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        cin >> numOfPoints;
        for (int i = 0; i < numOfPoints; ++i) {
            cin >> points[i].first >> points[i].second;
        }

        for (int i = 0; i < numOfPoints; ++i) {
            for (int j = 0; j < numOfPoints; ++j) {
                dist[i][j] = sqrt((points[i].first - points[j].first) * (points[i].first - points[j].first) + 
                                    (points[i].second - points[j].second) * (points[i].second - points[j].second));
            }
        }

        double result = round(optimize() * 100) / 100;
        printf("%.2f\n", result);
    }

    return 0;
}




