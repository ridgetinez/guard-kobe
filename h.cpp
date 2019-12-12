#include <bits/stdc++.h>

using namespace std;

const int MAX_RC = 50 + 2;
const int MAX_M = 10 + 2;

int matrix[MAX_RC + MAX_M][MAX_RC + MAX_M];
bool seen[MAX_RC + MAX_M][MAX_RC + MAX_M];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int M;
    string walk;

    cin >> M;
    if (M != 0) {
        cin >> walk;
    }

    int R, C;
    cin >> R >> C;

    for (int i = MAX_M; i < R + MAX_M; ++i) {
        for (int j = MAX_M; j < C + MAX_M; ++j) {
            cin >> matrix[i][j];
        }
    }

    int opt = 0;

    for (int i = 0; i < MAX_RC + MAX_M; ++i) {
        for (int j = 0; j < MAX_RC + MAX_M; ++j) {
            int currI = i;
            int currJ = j;
            int curropt = 0;
            bool died = false;

            for (int c = 0; c < M; ++c) {
                if (currI < 0 || currJ < 0 || currI >= MAX_RC + MAX_M || currJ >= MAX_RC + MAX_M) {
                    curropt = 0;
                    died = true;
                    break;
                }

                if (!seen[currI][currJ]) {
                    curropt += matrix[currI][currJ];
                }

                seen[currI][currJ] = true;

                switch (walk[c]) {
                    case 'u' : --currI; break;
                    case 'l' : --currJ; break;
                    case 'd' : ++currI; break;
                    case 'r' : ++currJ; break;
                }
            }

            if (currI < 0 || currJ < 0 || currI >= MAX_RC + MAX_M || currJ >= MAX_RC + MAX_M) {
                curropt = 0;
                died = true;
            }

            if (!died && !seen[currI][currJ]) {
                curropt += matrix[currI][currJ];
            }

            opt = max(opt, curropt);

            for (int i = 0; i < MAX_RC + MAX_M; ++i) {
                for (int j = 0; j < MAX_RC + MAX_M; ++j) {
                    seen[i][j] = false;
                }
            }
        }
    }

    cout << opt << "\n";

    return 0;
}