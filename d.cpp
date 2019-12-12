#include <bits/stdc++.h>

using namespace std;

const int N = 131072 + 3; // 2^N

vector<int> edges[N];
bool seen[N];
bool active[N];
int counts[N];

bool hasCycle(int u, int prev = -1) {
    if (seen[u])
        return false;
    seen[u] = true;
    active[u] = true;
    for (int v : edges[u]) {
        if (v == prev) continue;
        if (active[v] || hasCycle(v, u))
            return true;
    }
    active[u] = false;
    //cout << "AT: " << u << "\n";
    return false;
}

int main() {
    int numRounds;
    cin >> numRounds;

    const int twoN = (1 << numRounds);
    int numMatches = twoN - 1;
    //cout << "NUM MATCHES: " << numMatches << "\n";
    for (int i = 0; i < numMatches; ++i) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
        counts[u]++;
        counts[v]++;
    }

    bool isValid = true;
    for (int depth = 1; depth <= numRounds; ++depth) {
        int countToFind = (1 << (numRounds - depth));
        if (countToFind == 1) {
            countToFind = 2;
        }
        int count = 0;
        for (int i = 1; i <= twoN; ++i) {
            if (counts[i] == depth)
                count++;
        }
        //cout << "Depth: " << depth << " countToFind: " << countToFind << " count: " << count << "\n";
        if (count != countToFind) {
            cout << "MISTAKE\n";
            isValid = false;
        }
    }

    if (isValid) {
        if (hasCycle(1)) {
            cout << "MISTAKE\n";
        } else {
            bool disconnected = false;
            //cout << "LOOKING THRU SEEN: " << (1 << (numRounds)) << "\n"; 
            for (int i = 1; i <= twoN; ++i) {
                //cout << i << "seen: " << seen[i] << "\n";
                if (!seen[i]) {
                    cout << "MISTAKE\n";
                    disconnected = true;
                    break;
                }
            }
            if (!disconnected) {
                cout << "OK\n";
            }
        }
    }

    return 0;
}