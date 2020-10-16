#include <bits/stdc++.h>

using namespace std;

const int ALPHABETS = 26;

bool checkPossible(vector<int> &outDegree, vector<int> &inDegree) {
    int plusOne = 0, minusOne = 0;
    for (int i = 0; i < ALPHABETS; ++i) {
        if (outDegree[i] == inDegree[i] + 1)
            ++plusOne;
        else if (outDegree[i] + 1 == inDegree[i])
            ++minusOne;
        else if (outDegree[i] != inDegree[i])
            return false;
    }
    if ((plusOne == 0 && minusOne == 0) || (plusOne == 1 && minusOne == 1))
        return true;
    return false;
}

void getEulerCircuit (int here, vector<int>& circuit, vector<vector<int>>& adj)  {
    for (int there = 0; there < ALPHABETS; ++there) {
        while(adj[here][there] > 0) {
            --adj[here][there];
            getEulerCircuit(there, circuit, adj);
        }
    }
    circuit.push_back(here);
}

vector<int> getEulerTrailOrCircuit (vector<int>& inDegree, vector<int>& outDegree, vector<vector<int>>& adj) {
    vector<int> circuit;
    for (int i = 0; i < ALPHABETS; ++i) {
        if(outDegree[i] == inDegree[i] + 1) {
            getEulerCircuit(i, circuit, adj);
            return circuit;
        }
    }
    for (int i = 0; i < ALPHABETS; ++i) {
        if (outDegree[i] > 0) {
            getEulerCircuit(i, circuit, adj);
            return circuit;
        }
    }

    return circuit;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int N;
        cin >> N;
        vector<vector<int>> adj(ALPHABETS, vector<int>(ALPHABETS));
        vector<int> outDegree(ALPHABETS), inDegree(ALPHABETS);
        vector<vector<list<string>>> wordList(ALPHABETS, vector<list<string>>(ALPHABETS));
        for (int i = 0; i < N; ++i) {
            string word;
            cin >> word;
            int firstIdx = word[0] - 'a';
            int lastIdx = word[word.size() - 1] - 'a';
            ++adj[firstIdx][lastIdx];
            ++outDegree[firstIdx];
            ++inDegree[lastIdx];
            wordList[firstIdx][lastIdx].push_back(word);
        }
        vector<int> counts(ALPHABETS);
        for (int i = 0; i < ALPHABETS; ++i) {
            for (int j = 0; j < ALPHABETS; ++j) {
                counts[i] += adj[i][j];
                counts[j] -= adj[i][j];
            }
        }
        if (!checkPossible(outDegree, inDegree)) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        vector<int> circuit = getEulerTrailOrCircuit(inDegree, outDegree, adj);
        if (circuit.size() == 0) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        reverse (circuit.begin(), circuit.end());
        string answer;
        for (int i = 1; i < circuit.size(); ++i) {
            int a = circuit[i - 1], b = circuit[i];
            if (answer.size()) answer += " ";
            answer += wordList[a][b].back();
            wordList[a][b].pop_back();
        }
        cout << answer << endl; 
    }
    return 0;
}