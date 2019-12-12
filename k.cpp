#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200000 + 5;
vector<int> A;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int tony;
    for (int i = 0; i < n; ++i) {
        cin >> tony;
        A.push_back(tony);
    }

    sort(A.begin(), A.end());

    int opt = 0;

    for (int i = 0; i < n; ++i) {
        int cur = A[i];
        int num = A[i];
        int mag_c = 0;
        while (num > 0) {
            ++mag_c;
            num /= 10;
        }

        cout << "mag_c = " << mag_c << endl;

        int wantToFind = (pow(10, mag_c) - 1) - cur;
        cout << "want to find = " << wantToFind << endl;
        auto it = upper_bound(A.begin(), lower_bound(A.begin(), A.end(), cur), wantToFind);

        //if (it != A.begin()) {
            string result = to_string(cur);
            string toAdd;
            if (it == lower_bound(A.begin(), A.end(), cur)) {
                continue;
            } else if (it == A.begin()) {
                toAdd = to_string(*it);
            } else {
                toAdd = to_string(*(--it));
            }
            cout << "STRING: " << result << " " << toAdd << endl;

            auto it1 = result.rbegin();
            auto it2 = toAdd.rbegin();

            assert(result.size() >= toAdd.size());

            while (it2 != toAdd.rend()) {
                cout << *it1 << " + " << *it2 << endl;
                char z =  *it1 - '0';
                char y =  *it2 - '0';

                *it1 = ((z + y) % 10) + '0';

                ++it2;
                ++it1;
            }

            cout << "RESULT = " << result << endl;
            opt = max(opt, atoi(result.c_str()));

        //}
    }

    cout << opt << endl;

    return 0;
}