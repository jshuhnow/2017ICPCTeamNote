// H is convex Hull(not circular)
void diameter(const vector<Point> &H) {
	const int M = H.size();
	if (M == 2) {
		printf("%lld %lld %lld %lld\n", H[0].first, H[0].second, H[1].first, H[1].second);
		return;
	}

	int k = 1;
	while (area(H[M - 1], H[0], H[(k + 1) % M]) > area(H[M - 1], H[0], H[k]))
		++k;

	ll maxDist = 0;
	int ti = -1, tj = -1;
	for (int i = 0, j = k; i <= k && j < M; i++) {
		ll now = dist(H[i], H[j]);
		if (maxDist < now) {
			maxDist = now;
			ti = i, tj = j;
		}

		while (j<M && area(H[i], H[(i + 1) % M], H[(j + 1) % M]) > area(H[i], H[(i + 1) % M], H[j])) {
			ll now = dist(H[i], H[(j+1)%M]);
			if (maxDist < now) {
				maxDist = now;
				ti = i, tj = (j+1)%M;
			}
			++j;
		}
	}
	printf("%lld %lld %lld %lld\n", H[ti].first, H[ti].second, H[tj].first, H[tj].second);
}
