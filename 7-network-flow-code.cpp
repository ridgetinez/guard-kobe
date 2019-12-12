/*
 *
 * code for network flow
 *
 */

/*
 * edge list representation
 */

// the index of the first outgoing edge for each vertex, initialised to -1
int start[V];
fill(start, start + V, -1);
// if e is an outgoing edge from u, succ[e] is another one, or -1
// cap[e] is the capacity/weight of the e
// to[e] is the destination vertex of e
int succ[E], cap[E], to[E];

int edge_counter = 0;
void add_edge(int u, int v, int c) {
  // set the properties of the new edge
  cap[edge_counter] = c, to[edge_counter] = v;
  // insert this edge at the start of u's linked list of edges
  succ[edge_counter] = start[u];
  start[u] = edge_counter;
  ++edge_counter;
}
for (/* edge u -> v with capacity c in the original graph */) {
  add_edge(u, v, c); // original
  add_edge(v, u, 0); // residual edge
}

// edges are in pairs so we can easily go between residuals & originals
int inv(int e) { return e ^ 1; }
// easily iterate through all of u's outgoing edges (~(-1) == 0)
for (int e = start[u]; ~e; e = succ[e]) /* do something */;


/*
 * ford fulkerson
 */

// assumes the residual graph is constructed as in the previous section

int seen[V];

int inv(int e) { return e ^ 1; }

bool augment(int u, int t, int f) {
  if (u == t) return true;                     // the path is empty!
  if (seen[u]) return false;
  seen[u] = true;
  for (int e = start[u]; ~e; e = succ[e])
    if (cap[e] >= f && augment(to[e], t, f)) { // if we can reach the end,
      cap[e] -= f;                             // use this edge
      cap[inv(e)] += f;                        // allow "cancelling out"
      return true;
    }
  return false;
}

int max_flow(int s, int t) {
  int res = 0;
  fill(seen, seen + V, 0);
  while (augment(s, t, 1)) {
    fill(seen, seen + V, 0);
    res += 1;
  }
  return res;
}


/*
 * edmonds karp
 */

int augment(int s, int t) {
  // This is a BFS, shortest path means by edge count not capacity
  queue<int> q;
  // path[v] = which edge we used from to reach v
  fill(path, path + V, -1);
  for (q.push(s), path[s] = -2; !q.empty(); q.pop()) {
    int u = q.front();
    for (int e = start[u]; ~e; e = succ[e]) {
      // if we can use e and we haven't already visited v, do it
      if (cap[e] <= 0) continue;
      int v = to[e];
      if (path[v] == -1) {
        path[v] = e;
        q.push(v);
      }
    }
  }
  if (path[t] == -1) return 0; // can't reach the sink
  int res = INF;
  // walk over the path backwards to find the minimum edge
  for (int e = path[t]; e != -2; e = path[to[inv(e)]])
    res = min(res, cap[e]);
  // do it again to subtract that from the capacities
  for (int e = path[t]; e != -2; e = path[to[inv(e)]]) {
    cap[e] -= res;
    cap[inv(e)] += res;
  }
  return res;
}


/*
 * dinics 1
 */

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

/*
 * dinics 2
 */

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

vector<int> min_cut(int edges) {
  int total_size = max_flow(s, t);
  vector<int> ans;
  // the odd-numbered edges are the residual ones
  for (int e = 0; e < edges; e += 2) {
    if (!seen[to[e]] && seen[to[inv(e)]]) {
      ans.push_back(e);
    }
  }
  return ans;
}


/*
 * project selection
 */

// Construction:
// Nodes 0 to N-1 are the project nodes.
// Nodes N to N+M-1 are the machine nodes.
// Node N+M is the source, N+M+1 is the sink.

int main() {
    int N, M, D;
    scanf("%d %d", &N, &M);
    int totalRevenue = 0;
    int source = N+M, sink = N+M+1;
    for (int i = 0; i < N; i++) {
        int c; scanf("%d", &c);
        add_edge(source, i, c);
        totalRevenue += c;
    }
    for (int i = 0; i < M; i++) {
        int c; scanf("%d", &c);
        add_edge(i+N, sink, c);
    }
    scanf("%d", &D);
    for (int i = 0; i < D; i++) {
        int a, b; scanf("%d %d", &a, &b);
        a--; b--;
        add_edge(a, b+N, INF); // INF > all possible outputs.
    }
    printf("%d\n", totalRevenue - get_max_flow());
}

/*
 * magic hours
 */

// Construction:
// Nodes 0 to N-1 are the tourists.
// Nodes N to N+M-1 are the attractions.
// Node N+M is the magic hour, N+M+1 source, N+M+2 sink.

int main() {
    scanf("%d %d %d", &N, &M, &K);
    int magicnode = N+M, source = N+M+1, sink = N+M+2;
    for (int i = 0; i < M; i++) {
        int c; scanf("%d", &c);
        add_edge(i+N, sink, c);
    }
    vector<int> magicOpen(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &magicOpen[i]);
    }
    for (int i = 0; i < N; i++) {
        add_edge(source, i, 1);
        int b, C;
        scanf("%d %d", &b, &C);
        for (int j = 0; j < C; j++) {
            int x; scanf("%d", &x); x--;
            add_edge(i, x+N, 1);
            if (b && magicOpen[x]) add_edge(i, magicnode, 1);
        }
    }
    add_edge(magicnode, sink, K);
    // run max flow
}

/*
 * irrigation
 */

// Construction:
// Nodes 0 to N-1 are the row vertices.
// Nodes N to N+M-1 are the column vertices.
// Node N+M is the source, N+M+1 is the sink.

int N, M;
int main() {
    scanf("%d %d", &N, &M);
    int source = N+M, sink = N+M+1;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < M; c++) {
            char inp; scanf(" %c", &inp);
            if (inp == '1') {
                add_edge(r, c+N, 1);
            }
        }
    }
    for (int r = 0; r < N; r++) {
        add_edge(source, r, 1);
    }
    for (int c = 0; c < M; c++) {
        add_edge(c+N, sink, 1);
    }
    printf("%d\n", get_max_flow());
}

/*
 * jumping frogs
 */

double lo = 0, hi = 1e10;
for (int it = 0; it < 70; it++) {
  double mid = (lo + hi) / 2;
  if (cando(mid)) hi = mid;
  else lo = mid;
}
printf("%lf\n", lo);


/*
 * jumping frogs 2
 */

// Each stone is represented by 2 vertices, (0,1), (2, 3), ...
// Source is 2N, fake sink is 2N+1. real sink is 2N+2.
// Edge of cap 2 from fake to real sink to limit max flow to 2.
double sqdist(double x1, double y1, double x2, double y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

bool cando(double maxdist) {
    if (D < maxdist) return true;
    int source = 2*N;
    int fakesink = 2*N+1;
    int realsink = 2*N+2;
    for (int i = 0; i < N; i++) {
        int cap = isbig[i] ? INF : 1;
        add_edge(2*i, 2*i+1, cap);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sqdist(x[i], y[i], x[j], y[j]) < maxdist*maxdist)
                add_edge(2*i+1, 2*j, INF);
        }
    }
    for (int i = 0; i < N; i++) {
        if (x[i] < maxdist) add_edge(source, 2*i, INF);
        if (x[i] + maxdist > D) add_edge(2*i+1, fakesink, INF);
    }
    add_edge(fakesink, realsink, 2);
    return get_max_flow() == 2;
}

