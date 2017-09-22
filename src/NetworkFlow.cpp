/* L-R Flow
 * for each edge a->b whose capacity is [l, r]
 * 1) a->b with capacity l, cost -1 and with capacity r-l, cost 0
 * 2) new source -> b with capacity l, a -> new sink with capacity l, a->b with capacity r-l, sink->source with capacity INF
 * and check that the Maximum Flow is eqaul to the summation of 'l's
 *
 * actual flow - do maxflow(oldsrc, olddst)
 */
// O(V^2E) / O( min( V^(2/3)E, E^(3/2)) with UNIT capacity!
struct Dinic {
	typedef long long flow_t;
	struct Edge {
		int dest;
		int inv;
		flow_t res;
	};

	vector<vector<Edge>> adj;
	vector<int> level, start;

	Dinic(int n) : adj(n), level(n), start(n) {}

	void addEdge(int here, int there, flow_t cap, flow_t caprev = 0) {
		Edge forward = { there, adj[there].size(), cap };
		Edge backward = { here, adj[here].size(), caprev };
		adj[here].push_back(forward);
		adj[there].push_back(backward);
	}

	bool assignLevel(int source, int sink) {
		fill(level.begin(), level.end(), 0);
		queue<int> q;
		q.push(source);
		level[source] = 1;
		while (!q.empty() && level[sink] == 0) {
			int here = q.front();
			q.pop();
			for (Edge &edge : adj[here]) {
				int next = edge.dest;
				if (level[next] == 0 && edge.res > 0) {
					level[next] = level[here] + 1;
					q.push(next);
				}
			}
		}
		return level[sink] != 0;
	}

	flow_t blockFlow(int here, int sink, flow_t flow) {
		if (here == sink) return flow;
		for (int &i = start[here]; i < adj[here].size(); ++i) {
			Edge &edge = adj[here][i];
			if (level[edge.dest] != level[here] + 1 || edge.res == 0) continue;
			flow_t res = blockFlow(edge.dest, sink, min(flow, edge.res));
			if (res > 0) {
				edge.res -= res;
				adj[edge.dest][edge.inv].res += res;
				return res;
			}
		}
		return 0;
	}

	flow_t solve(int source, int sink) {
		flow_t ret = 0;
		while (assignLevel(source, sink)) {
			fill(start.begin(), start.end(), 0);
			while (flow_t flow = blockFlow(source, sink, numeric_limits<flow_t>::max()))
				ret += flow;
		}
		return ret;
	}
};

struct EdmondKarp {
	const int INF = 987654321;


	int min(int a, int b) {
	    return a<b? a:b;
	}
	pair<int, vector<int>> BFS(const vector<vector<int>> &cap, const vector<vector<int>> &graph,
	                           vector<vector<int>> &flow, const int src, const int sink) {
	    vector<int> prv(graph.size(), -1);
	    vector<int> M(graph.size(), -1);
	    prv[src]=-2; M[src] = INF;

	    queue<int> q; q.push(src);

	    while(!q.empty()) {
	        int u = q.front(); q.pop();
	        for (int v : graph[u]) {
	            if (cap[u][v] - flow[u][v] > 0 && prv[v] == -1) {
	                prv[v] = u;
	                M[v] = min(M[u], cap[u][v] - flow[u][v]);
	                if (v!=sink) {
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
	int MaxFlow(const vector<vector<int>> cap, const vector<vector<int>> graph,
	            const int src, const int sink) {
	    int sum =0;
	    vector<vector<int>> flow(graph.size(), vector<int>(graph.size(),0));

	    while(true) {
	        //BFS
	        pair<int, vector<int>> ret = BFS(cap, graph, flow, src, sink);
	        int m = ret.first; vector<int> &prv = ret.second;

	        if (m == 0) break;
	        sum+= m;
	        
	        int v= sink;
	        while(v != src) {
	            int u = prv[v];
	            flow[u][v] += m;
	            flow[v][u] -= m;
	            v = u;
	        }
	    }
	    return sum;
	}

	/* Usage
	    vector<vector<int>> graph(V), cap(V, vector<int>(V, 0));
	    graph[src].push_back(dst);
	    graph[dst].push_back(src);
	    cap[src][dst] = 1;

	    printf("%d\n", MaxFlow(cap,graph, src, dst));
	*/
};

struct BipartieMatch {
	bool dfs(size_t now, const vector<vector<int>> &graph,
		vector<bool> &visited, vector<size_t> &back_match) {
		if (visited[now]) return false;
			visited[now] = true;
		for (int nxt: graph[now]) {
			if (back_match[nxt] == -1 ||
				dfs(back_match[nxt], graph, visited, back_match)) {
				back_match[nxt] = now;
				return true;
			}
		}

		return false;
	}

	int bipartite_match(const vector<vector<int>> &graph) {
		int matched = 0;
		vector<bool> visited(graph.size(), false);
		vector<size_t> back_match(graph.size(), -1);
		for (size_t i =0; i<graph.size(); i++) {
			if (dfs(i, graph, visited, back_match)) {
				matched++;
			}
		}
		return matched;
	}
}
