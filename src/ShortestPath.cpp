// Dijkstra - O((V+E)logV) with priority queue - with an important checking - if (now_dist > dist[now_idx]) continue;
// BelmanFord - do V-1 iteration - O(VE) with adj list. V-th iteration checks the existence of negative cycle
// Floyd-Warshall - k, i, j O(V^3) - applicable to graph with negative edges.
// 	Cycle Detection - init d[i][i] = INF, check whether d[i][i] >= 0 still
