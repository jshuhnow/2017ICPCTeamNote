

typedef int cap_t;
typedef int cost_t; // cost의 자료형 (double이나 int)
typedef pair<cost_t, int> pq_t;
bool isZeroCap(cap_t cap)
{
    return cap == 0;
}
const int INF = 987654321;
const cap_t CAP_MAX = INF;
const cost_t COST_MAX = INF;
struct edge_t {
    int target;
    cap_t cap;
    cost_t cost;
    int rev;
};
int n;
vector<vector<edge_t> > graph;
vector<cost_t> pi;
vector<cost_t> dist;
vector<cap_t> mincap;
vector<int> from, v;
void init(int _n)
{
    n = _n;
    graph.clear();
    graph.resize(n);
    pi.clear();
    pi.resize(n);
    dist.resize(n);
    mincap.resize(n);
    from.resize(n);
    v.resize(n);
}
void addEdge(int a, int b, cap_t cap, cost_t cost)
{
    edge_t forward = { b, cap, cost, (int)graph[b].size() };
    edge_t backward = { a, 0, -cost, (int)graph[a].size() };
    graph[a].push_back(forward);
    graph[b].push_back(backward);
}
bool dijkstra(int s, int t)
{ // Modified Dijkstra
    priority_queue<pq_t, vector<pq_t>, greater<pq_t> > pq;
    fill(dist.begin(), dist.end(), COST_MAX);
    for (int i = 0; i < n; i++) {
        from[i] = -1;
        v[i] = 0;
    }
    dist[s] = 0;
    mincap[s] = CAP_MAX;
    pq.push(make_pair(dist[s], s));
    while (!pq.empty()) {
        int cur = pq.top().second;
        pq.pop();
        if (v[cur])
            continue;
        v[cur] = 1;
        if (cur == t)
            continue;
        for (int k = 0; k < graph[cur].size(); k++) {
            edge_t edge = graph[cur][k];
            int next = edge.target;
            if (v[next])
                continue;
            if (isZeroCap(edge.cap))
                continue;
            cost_t potCost = dist[cur] + edge.cost - pi[next] + pi[cur];
            if (dist[next] <= potCost)
                continue;
            dist[next] = potCost;
            mincap[next] = min(mincap[cur], edge.cap);
            from[next] = edge.rev;
            pq.push(make_pair(dist[next], next));
        }
    }
    if (dist[t] == COST_MAX)
        return false;
    for (int i = 0; i < n; i++) {
        if (dist[i] == COST_MAX)
            continue;
        pi[i] += dist[i];
    }
    return true;
}
pair<cap_t, cost_t> solve(int source, int sink)
{
    cap_t total_flow = 0;
    cost_t total_cost = 0;
    while (dijkstra(source, sink)) { // 음수 간선이면 SPFA, 양수 간선이면 Dijkstra
    	cap_t f= mincap[sink];
        total_flow += f;
        for (int p = sink; p != source;) {
            edge_t& backward = graph[p][from[p]];
            edge_t& forward = graph[backward.target][backward.rev];
            forward.cap -= f;
            backward.cap += f;
            total_cost += forward.cost * f;
            p = backward.target;
        }
    }
    return make_pair(total_flow, total_cost);
}

struct SPFA {
    vi dist(n, INF); dist[S] = 0;
    queue<int> q; q.push(S);
    vi in_queue(n, 0); in_queue[S] = 1;

    while (!q.empty()) {
      int u = q.front(); q.pop(); in_queue[u] = 0;
      for (j = 0; j < (int)AdjList[u].size(); j++) { // all outgoing edges from u
        int v = AdjList[u][j].first, weight_u_v = AdjList[u][j].second;
        if (dist[u] + weight_u_v < dist[v]) { // if can relax
          dist[v] = dist[u] + weight_u_v; // relax
          if (!in_queue[v]) { // add to the queue only if it's not in the queue
            q.push(v);
            in_queue[v] = 1;
          }
        }
      }
    }


    //return dist
}

