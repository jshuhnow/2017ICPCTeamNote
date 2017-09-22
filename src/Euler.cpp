void EulerTour(list<int>::iterator i, int u) {
	for (int j=0; j<adj[u].size; j++) {
		ii &v = adj[u][j];
		if (v.second) {
			v.second = 0;
			for (int k=0; k<adj[v.first].size(); k++) {
				ii &uu = adj[v.first][k];
				if (uu.first == u && uu.second) {
					uu.second = 0;
					break;
				}
			}
			EulerTour(cycle.insert(i, u), v.first);
		}
	}
}
/* Usage
	cyc.clar();
	EulerTour(cyc.begin(), src);
	for (auto it : cyc) {
		printf("%d\n", (*it);
	}

