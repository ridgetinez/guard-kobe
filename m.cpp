#include <bits/stdc++.h>

using namespace std;

int main() {
    int numMarbles;
    cin >> numMarbles;

    unordered_map<int, int> m1, m2;

    for (int i = 0; i < numMarbles; ++i) {
        int n1;
        cin >> n1;
        if (m1.find(n1) == m1.end()) 
            m1[n1] = 0;
       
        m1[n1] += 1;
        
    }

    for (int i = 0; i < numMarbles; ++i) {
        int n2;
        cin >> n2;
        if (m2.find(n2) == m2.end()) 
            m2[n2] = 0;
        m2[n2] += 1;
    }

    bool valid = true;
    for (auto p : m1) {
        if (m2.find(p.first) == m2.end() || m2[p.first] != p.second) {
            cout << "error\n";
            valid = false;
            break;
        }
    }
    if (valid)
        cout << "marvelous\n";

    return 0;
}