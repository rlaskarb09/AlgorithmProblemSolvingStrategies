#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int startIdx = 400;
int maxN, M;
vector<pair<int, int>> plusLink, minusLink, sameLink;
vector<pair<int, int>> link[startIdx + 1];

void makeLink() {
    for (int here = 0; here <= maxN * 2; ++here) {
        for (int i = 0; i < sameLink.size(); ++i)
            link[here].emplace_back(here, sameLink[i].second);
        for (int i = 0; i < plusLink.size(); ++i) {
            if (here + plusLink[i].first > maxN * 2)
                break;
            link[here].emplace_back(here + plusLink[i].first, plusLink[i].second);
        }
        for (int i = 0; i < minusLink.size(); ++i) {
            if (here + minusLink[i].first < 0)
                break;
            link[here].emplace_back(here + minusLink[i].first, minusLink[i].second);
        }
    }
    for (int i = 0; i < sameLink.size(); ++i)
        link[startIdx].emplace_back(0, sameLink[i].second);
    for (int i = 0; i < plusLink.size(); ++i) 
        link[startIdx].emplace_back(plusLink[i].first, plusLink[i].second);
}

int dijkstra() {
    vector<int> dist(401, INF);
    dist[startIdx] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push(make_pair(0, startIdx));
    while(!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();
        // cout << "cost=" << cost << ", here=" << here << endl;
        if (dist[here] < cost) continue;
        for (int i = 0; i < link[here].size(); ++i) {
            int there = link[here][i].first;
            int nextDist = cost + link[here][i].second;
            // cout << "there=" << there << ", nextDist=" << nextDist << endl;
            if(dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
            }
        }
    }

    return dist[0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tests;
    cin >> tests;
    for (int testIdx = 0; testIdx < tests; ++testIdx) {
        maxN = 1;
        plusLink.clear();
        minusLink.clear();
        sameLink.clear();
        for (int i = 0; i <= 400; ++i)
            link[i].clear();
        cin >> M;
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            if (a == b) 
                sameLink.emplace_back(0, a);
            else if (a > b) 
                plusLink.emplace_back(a-b, a);
            else 
                minusLink.emplace_back(a-b, a);
            maxN = max(maxN, abs(a-b));
        }
        sort(plusLink.begin(), plusLink.end());
        sort(minusLink.begin(), minusLink.end(), greater<pair<int, int>>());
        makeLink();
        int dist = dijkstra();
        if (dist == INF)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << dist << endl;
    }
}