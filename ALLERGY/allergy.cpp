#include <bits/stdc++.h>

using namespace std;

const int MAX_TEST_CASES = 50;
const int MAX_FRIENDS = 20;
const int MAX_FOODS = 20;

int numOfFriends, numOfFoods;
vector<int> canEat[MAX_FRIENDS], eaters[MAX_FOODS];
int best;

void search(vector<int>& edible, int chosen) {
    if (chosen >= best) return;
    int first = 0;
    while (first < numOfFriends && edible[first] > 0) ++first;
    if (first == numOfFriends) {
        best = chosen;
        return;
    }
    for (int i = 0; i < canEat[first].size(); ++i) {
        int food = canEat[first][i];
        for (int j = 0; j < eaters[food].size(); ++j) {
            edible[eaters[food][j]]++;
        }
        search(edible, chosen + 1);
        for (int j = 0; j < eaters[food].size(); ++j) {
            edible[eaters[food][j]]--;
        }    
    }

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numOfTestCases;
    cin >> numOfTestCases;
    map<string, int> friends;

    for (int caseIdx = 0; caseIdx < numOfTestCases; ++caseIdx) {
        friends.clear();
        for (int i = 0; i < MAX_FRIENDS; ++i) {
            canEat[i].clear();
            eaters[i].clear();
        }
        cin >> numOfFriends >> numOfFoods;
        for (int i = 0; i < numOfFriends; ++i) {
            string friendName;
            cin >> friendName;
            friends.insert(make_pair(friendName, i));
        }
        for (int i = 0; i < numOfFoods; ++i) {
            int eaterNum;
            cin >> eaterNum;
            string friendName;
            for (int j = 0; j < eaterNum; ++j) {
                cin >> friendName;
                int friendNum = friends.find(friendName)->second;
                canEat[friendNum].push_back(j);
                eaters[j].push_back(friendNum);
            }
        }

        best = numOfFoods;
        vector<int> edible(numOfFriends, 0);
        search(edible, 0);
        cout << best << '\n';
    }


    return 0;
}