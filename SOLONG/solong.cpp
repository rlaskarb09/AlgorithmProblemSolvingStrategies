#include <bits/stdc++.h>

using namespace std;

const int ALPHABETS = 26;
int toNumber(char ch) {return ch - 'A';}

bool comp (const pair<string, int>& a, const pair<string, int>& b) {
    if (a.second == b.second) {
        return a < b;
    }
    return a.second > b.second;
}

struct TrieNode {
    TrieNode* children[ALPHABETS];
    int terminal;
    int first;
    TrieNode() : terminal(-1), first(-1) {
        memset(children, 0, sizeof(children));
    }
    ~TrieNode() {
        cout << "oops!" << endl;
        for (int i = 0; i < ALPHABETS; ++i)
            if(children[i])
                delete children[i];
    }

    void insert(const char* key, int id) {
        if (first == -1) first = id;
        if (*key == 0) {
            terminal = id;
        }
        else {
            int next = toNumber(*key);
            if(children[next] == NULL)
                children[next] = new TrieNode();
            children[next]->insert(key + 1, id);
        }
    }

    TrieNode* find(const char* key) {
        if (*key == 0) return this;
        int next = toNumber(*key);
        if(children[next] == NULL) return NULL;
        return children[next]->find(key+1);
    }
};

int getCount(string& query, TrieNode* root, vector<pair<string, int>>& words) {
    int count = 0;
    if (query.size() <= 2) return query.size();
    TrieNode* findNode = root->find(query.c_str());
    if (findNode == NULL || findNode->terminal == - 1) return query.size();
    TrieNode* node = root;
    for (int i = 0; i < query.size() - 1; ++i) {
        node = node->children[toNumber(query[i])];
        if (words[node->first].first == query) return i + 2;
    }
    return query.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int numOfTests;
    cin >> numOfTests;
    for (int testIdx = 0; testIdx < numOfTests; ++testIdx) {
        int count = -1;
        int N, M;
        cin >> N >> M;
        TrieNode * root = new TrieNode();
        vector<pair<string, int>> words(N);
        string query;
        int freq;
        for (int i = 0; i < N; ++i) {
            cin >> words[i].first >> words[i].second;
        }
        sort(words.begin(), words.end(), comp);
        for (int i = 0; i < words.size(); ++i) {
            root->insert(words[i].first.c_str(), i);
        }
        for (int i = 0; i < M; ++i) {
            count++;
            cin >> query;
            count += getCount(query, root, words);
        }
        cout << count << endl;
    }
    TrieNode* root = new TrieNode();

    return 0;
}