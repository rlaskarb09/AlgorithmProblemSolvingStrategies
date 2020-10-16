#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int K, N, sum = 0, count = 0;
        unsigned int A = 1983u;
        cin >> K >> N;
        queue<int> q;
        for (int i = 0; i < N; ++i) {
            int input = A % 10000u + 1;
            q.push(input);
            sum += input;
            while(sum >= K) {
                if (sum == K) {
                    count ++;
                }
                int popped = q.front();
                q.pop();
                sum -= popped;
            }

            A = A * 214013u + 2531011u;
        }
        cout << count << endl;
    }

    return 0;
}