#include <bits/stdc++.h>

using namespace std;

int main() {
    char arrayChar;
    double index;
    int increment;
    map<double, int> arrays[26];
    while (scanf("%c[%lf] += %d\n", &arrayChar, &index, &increment) == 3) {
        if (arrays[arrayChar - 'A'].find(index) != arrays[arrayChar - 'A'].end()) {
            arrays[arrayChar - 'A'][index] += increment;
        } else {
            arrays[arrayChar - 'A'][index] = increment;
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (!arrays[i].empty()) {
            printf("%c\n", i + 'A');
        }
        for (const pair<double, int>& ary : arrays[i]) {
            if (ary.second == 0) continue;
            printf("%d\n", ary.second);
        }
    }

    return 0;
}