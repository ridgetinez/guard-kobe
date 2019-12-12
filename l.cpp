#include <bits/stdc++.h>

using namespace std;

const int V = 100 + 100 + 2 + 10;
const int E = 2*(V*V + V + V + 10);
const int N = V;
const int INF = INT32_MAX;

// the index of the first outgoing edge for each vertex, initialised to -1
int start[V];

// if e is an outgoing edge from u, succ[e] is another one, or -1
// cap[e] is the capacity/weight of the e
// to[e] is the destination vertex of e
int succ[E], cap[E], to[E];

int edge_counter;
void add_edge(int u, int v, int c) {
  // set the properties of the new edge
  cap[edge_counter] = c, to[edge_counter] = v;
  // insert this edge at the start of u's linked list of edges
  succ[edge_counter] = start[u];
  start[u] = edge_counter;
  ++edge_counter;
}

// edges are in pairs so we can easily go between residuals & originals
int inv(int e) { return e ^ 1; }
// easily iterate through all of u's outgoing edges (~(-1) == 0)
// assumes the residual graph is constructed as in the previous section
// n = #nodes, s = source, t = sink
int n, s, t;
// stores dist from s.
int lvl[N];
// stores first non-useless child.
int nextchld[N];

// constructs the BFS tree.
// Returns if the sink is still reachable.
bool bfs() {
  for (int i = 0; i < n; i++) lvl[i] = -1;
  queue<int> q;
  q.push(s); lvl[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    nextchld[u] = start[u]; // reset nextchld
    for (int e = start[u]; ~e; e = succ[e]) {
      if (cap[e] > 0) {
        int nxt = to[e];
        if (lvl[nxt] != -1) continue; // already seen
        lvl[nxt] = lvl[u] + 1;
        q.push(nxt);
      }
    }
  }
  return lvl[t] != -1;
}

// Finds an augmenting path with up to cflow flow.
int aug(int u, int cflow) {
  if (u == t) return cflow; // base case.
  // Note the reference here! We will keep decreasing nextchld[u]
  // Till we find a child that we can flow through.
  for (int &i = nextchld[u]; i >= 0; i = succ[i]) {
    if (cap[i] > 0) {
      int nxt = to[i];
      // Ignore edges not in the BFS tree.
      if (lvl[nxt] != lvl[u] + 1) continue;
      int rf = aug(nxt, min(cflow, cap[i]));
      // Found a child we can flow through!
      if (rf > 0) {
        cap[i] -= rf;
        cap[i^1] += rf;
        return rf;
      }
    }
  }
  lvl[u]=-1;
  return 0;
}

int mf() {
  int tot = 0;
  while (bfs())
    for (int x = aug(s,INF); x; x = aug(s,INF)) tot+=x;
  return tot;
}

int main() {
    fill(start, start + V, -1);

    int Z;
    cin >> Z;

    // Connect rows to columns with ininfity edges
    for (int i = 0; i < Z; ++i) {
        for (int j = 0; j < Z; ++j) {
            add_edge(i, j + Z, INF);
            add_edge(j + Z, i, 0);
        }
    }

    s = Z + Z;
    t = Z + Z + 1;
    n = Z + Z + 2;

    for (int i = 0; i < Z; ++i) {
        int yes;
        cin >> yes;
        add_edge(s, i, yes);
        add_edge(i, s, 0);
    }

    for (int i = 0; i < Z; ++i) {
        int yes;
        cin >> yes;
        add_edge(i+Z, t, yes);
        add_edge(t, i+Z, 0);

    }

    for (int u = 0; u < n + n; ++u) {
        for (int e = start[u]; ~e; e = succ[e]) {
            if (to[e] == s) continue;

            
        }
    }

    cout << mf() << "\n";
}