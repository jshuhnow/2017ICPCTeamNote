// O(V+E)

vector<pii> edges, vector<int> vertexes;
vector<int> dfs_num, dfs_low, dfs_parent; vector<bool> chk;
const int UNVISITED = -1;
void dfs(int u) {
	dfs_low[u] = dfs[num] = dfsCnt++; //dfs_low[u]<=dfs_num[u]
	for (int j=0; j<(int)adj[u].size(); j++) {
		pii v = adj[u][j];
		if (dfs_num[v.first] == UNVISITED) {
			dfs_parent[v.first] = u;
			if (u==dfsRoot) rootChildren++;

			dfs(v.first);

			if (dfs_low[v.first] >= dfs_num[u])
				chk[u] = true;
			if (dfs_low[v.first] > dfs_num[u])
				edge.push_back({u, v.first});
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);
		}
		else if (v.first != dfs_parent[u])
			dfs_low[u] = min(dfs_low[u], dfs_num[v.first]);

	}
}

void findArticulation() {
	dfsCnt = 0; 
	dfs_num.assign(V, UNVISITED);
	dfs_low.assign(V, 0);
	dfs_parent.assign(V, 0);
	chk.assign(V, false);
	for (int i=0; i<V; i++) {
		if (dfs_num[i] == UNVISITED) {
			dfsRoot = i; rootChildren = 0; findArticulation(i);
			chk[i] = (rootChildren > 1);
		}
	}

}


// O(E V^0.5)
size_t q;

namespace HopcroftKarp {
	const size_t &INF = numeric_limits<size_t>::max();
	const size_t &NIL = 0;

	vector<size_t> pairL, pairR, level;
	queue<size_t> que;
	const vector<vector<size_t>> *graph;
	size_t n, totalMatching;

	inline bool bfs() {
		for (size_t left = 1; left <= n; left++) {
			if (pairL[left] == NIL) {
				level[left] = 0;
				que.emplace(left);
			}
			else level[left] = INF;
		}
		level[NIL] = INF;

		while (que.size()) {
			size_t left = que.front();
			que.pop();

			if (level[left] >= level[NIL]) continue;

			for (size_t right : graph->at((left - 1) % q + 1)) {
				size_t prevPair = pairR[right];

				if (level[prevPair] == INF) {
					level[prevPair] = level[left] + 1;
					que.emplace(prevPair);
				}
			}
		}

		return level[NIL] != INF;
	}

	bool dfs(size_t left) {
		if (left == NIL) return true;

		for (size_t right : graph->at((left - 1) % q + 1)) {
			size_t &traceLink = pairR[right];

			if (level[traceLink] == level[left] + 1 && dfs(traceLink)) {
				traceLink = left;
				pairL[left] = right;
				return true;
			}
		}

		level[left] = INF;
		return false;
	}

	size_t maximumMatching(const vector<vector<size_t>> &graph, size_t n, size_t m) {
		HopcroftKarp::graph = &graph;
		HopcroftKarp::n = n;

		level.resize(n + 1);
		pairL.resize(n + 1);
		fill(pairL.begin(), pairL.end(), NIL);
		pairR.resize(m + 1);
		fill(pairR.begin(), pairR.end(), NIL);
		totalMatching = 0;

		while (bfs()) {
			for (size_t left = 1; left <= n; left++) {
				if (pairL[left] == NIL && dfs(left)) {
					totalMatching++;
				}
			}
		}

		return totalMatching;
	}
}

/* Usage
	size_t n, m, p, a;
	scanf("%zu%zu", &n, &m);
	vector<vector<size_t>> graph(n + 1);

	q = n;
	for (size_t i = 1; i <= n; i++) {
		scanf("%zu", &p);
		while (p--) {
			scanf("%zu", &a);
			graph[i].emplace_back(a);
		}
	}

	printf("%zu", HopcroftKarp::maximumMatching(graph, n + n, m));
*/				
