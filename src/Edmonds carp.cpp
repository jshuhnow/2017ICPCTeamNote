const int INF = 987654321;
using namespace std;

pair<int, vector<int> > BFS(const vector<vector<int> >& cap, const vector<vector<int> >& graph,
    vector<vector<int> >& flow, const int src, const int
                                                   sink)
{
    vector<int> prv(graph.size(), -1);
    vector<int> M(graph.size(), -1);
    prv[src] = -2;
    M[src] = INF;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (cap[u][v] - flow[u][v] > 0 && prv[v] == -1) {
                prv[v] = u;
                M[v] = min(M[u], cap[u][v] - flow[u][v]);
                if (v != sink) {
                    q.push(v);
                }
                else {
                    return make_pair(M[sink], prv);
                }
            }
        }
    }
    return make_pair(0, prv);
}
//Edmonds Karp Algorithm
int MaxFlow(const vector<vector<int> > cap, const vector<vector<int> >
                                                graph,
    const int src, const int sink)
{
    int sum = 0;
    vector<vector<int> > flow(graph.size(), vector<int>(graph.size(), 0));
    while (true) {
        //BFS
        pair<int, vector<int> > ret = BFS(cap, graph, flow, src, sink);
        int m = ret.first;
        vector<int>& prv = ret.second;
        if (m == 0)
            break;
        sum += m;
        int v = sink;
        while (v != src) {
            int u = prv[v];
            flow[u][v] += m;
            flow[v][u] -= m;
            v = u;
        }
    }
    return sum;
}
//Usage
/* vector<vector<int> > graph(V), cap(V, vector<int>(V,0));
graph[src].push_back(dst);
graph[dst].push_back(src);
cap[src][dst] = w;
    
printf("%d\n", MaxFlow(cap, graph, src, dst)); */


