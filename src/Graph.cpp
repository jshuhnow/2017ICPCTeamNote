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
				
