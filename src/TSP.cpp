// O(2^N * N^2)

const int MAXN = 16;
 
int n;
int W[MAXN][MAXN], dp[1 << MAXN][MAXN];
 
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &W[i][j]);
 
	memset(dp, -1, sizeof(dp));
 
	dp[1][0] = 0; //start from 0.
	for (int bit = 0; bit < (1 << n); bit++) {
		for (int now = 0; now < n; now++) {
			if ((bit & (1 << now)) != (1 << now)) continue;
			if (dp[bit][now] == -1) continue;
 
			for (int nxt = 0; nxt < n; nxt++) {
				if ((bit & (1 << nxt)) == (1 << nxt)) continue;
				if (W[now][nxt] == 0) continue;
				int status = bit | (1 << nxt);
				if (dp[status][nxt] == -1 || dp[status][nxt] > dp[bit][now] + W[now][nxt]) {
					dp[status][nxt] = dp[bit][now] + W[now][nxt];
				}
			}
		}
	}
 
	int ans = 2e9;
	for (int i = 0; i < n; i++) {
		if (W[i][0] == 0) continue;
		if (dp[(1 << n) - 1][i] == -1) continue;
		ans = std::min(ans, dp[(1 << n) - 1][i] + W[i][0]);
	}
	printf("%d", ans);
 
	return 0;
}
~
