#include <bits/stdc++.h>

using namespace std;

int nextNew;

struct RMQ {
    int size;
    const int INF_NUM = 987654321;
    vector<int> rangeMin;
    
    RMQ(vector<int> array) {
        size = array.size();
        rangeMin.resize(size * 4);
        init(array, 0, size - 1, 1);
    }

    int init(const vector<int>& array, int left, int right, int node) {
        if (left == right) return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid + 1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }

    int query(int start, int end, int left, int right, int node) {
        if (start > right || end < left) return INF_NUM;
        if (start <= left && end >= right) return rangeMin[node];
        int mid = (left + right) / 2;
        return min(query(start, end, left, mid, node * 2), query(start, end, mid + 1, right, node * 2 + 1));
    }

    int query(int start, int end) {
        return query(start, end, 0, size - 1, 1);
    }
};

void traverse(int here, int d, vector<int>& trip, vector<vector<int>>& child, vector<int>& originToNew, 
                vector<int>& firstRef, vector<int>& depth) {
    originToNew[here] = nextNew;
    int myNewNum = nextNew;
    trip.push_back(myNewNum);
    firstRef[myNewNum] = trip.size() - 1;
    depth[myNewNum] = d;
    ++nextNew;
    for (int i = 0; i < child[here].size(); ++i) {
        traverse(child[here][i], d + 1, trip, child, originToNew, firstRef, depth);
        if(i < child[here].size() - 1) {
            trip.push_back(myNewNum);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int numOfTests;
    cin >> numOfTests;
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N, Q;
        nextNew = 0;
        cin >> N >> Q;
        vector<vector<int>> child(N);
        vector<int> originToNew(N), firstRef(N), depth(N), trip;
        for (int i = 1; i < N; ++i) {
            int parent;
            cin >> parent;
            child[parent].push_back(i);
        }
        traverse(0, 1, trip, child, originToNew, firstRef, depth);

        RMQ rmq(trip);
        for (int i = 0; i < Q; ++i) {
            int a, b;
            cin >> a >> b;
            int newA = originToNew[a], newB = originToNew[b];
            if (newA > newB) swap(newA, newB);
            int ancestor = rmq.query(firstRef[newA], firstRef[newB]);
            cout << depth[newA] + depth[newB] - 2 * depth[ancestor] << endl;
        }
    }
    return 0;
}