#include <bits/stdc++.h>

using namespace std;

void printPostOrder(const vector<int>& preOrder, const vector<int>& inOrder) {
    // preOrder.size() == inOrder.size()
    if (preOrder.size() == 0) {
        return;
    } 
    // else if (preOrder.size() == 1) {
    //     cout << preOrder[0] << " ";
    //     return;
    // }
    int rootVal = preOrder[0];
    int rootIdx = find(inOrder.begin(), inOrder.end(), rootVal) - inOrder.begin();
    printPostOrder(vector<int>(preOrder.begin() + 1, preOrder.begin() + 1 + rootIdx), 
                    vector<int>(inOrder.begin(), inOrder.begin() + rootIdx));
    printPostOrder(vector<int>(preOrder.begin() + 1 + rootIdx, preOrder.end()), 
                    vector<int>(inOrder.begin() + rootIdx + 1, inOrder.end()));   

    cout << rootVal << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;

    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N;
        cin >> N;
        vector<int> preOrder(N), inOrder(N);
        for (int i = 0; i < N; ++i) cin >> preOrder[i];
        for (int i = 0; i < N; ++i) cin >> inOrder[i];
        printPostOrder(preOrder, inOrder);
        cout << endl;
    }


    return 0;
}