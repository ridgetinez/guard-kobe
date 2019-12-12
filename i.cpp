#include <bits/stdc++.h>

using namespace std;

const int N = 100;

int main() {

    int numItems, numRemove;
    cin >> numItems >> numRemove;
    unordered_map<string, int> itemCounts;

    for (int i = 0; i < numItems; ++i) {
        int n;
        string item;
        cin >> n >> item;
        if (n > 1)
            item.pop_back();
        itemCounts[item] = n;
    }
    
    for (int i = 0; i < numRemove; ++i) {
        int n;
        string item;
        cin >> n >> item;
        if (n > 1)
            item.pop_back();
        if (itemCounts.find(item) == itemCounts.end()) {
            itemCounts[item] = -1;
        } else {
            itemCounts[item] -= n;
        }
    }

    int sum = 0;
    bool err = false;
    for (const auto p : itemCounts) {
        if (p.second < 0) {
            cout << "error\n";
            err = true;
            break;
        }
        sum += p.second;
    }

    if (!err) {
        if (sum == 0) {
            cout << "null\n";
        } else if (sum == 1) {
            cout << "item\n";
        } else {
            cout << "items\n";
        }
    }
    
    return 0;
}