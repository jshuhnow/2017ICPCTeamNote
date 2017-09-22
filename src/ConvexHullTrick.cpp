#include <cstdio>
#define MN 1000001
int i, j, n, x[MN], dn, L[MN];
long long A, B, C, dp[MN], S[MN];
char buffer[5*MN];
double d[MN];
inline double g(int a) {
	return (double)(dp[i]-dp[a]+A*(S[i]*S[i]-S[a]*S[a]))/(2*A*(S[i]-S[a]));
}
int main() {
	scanf("%d%lld%lld%lld\n",&n,&A,&B,&C);
	gets(buffer+1);
	int xn = 1;
	for (i = 1; buffer[i]; i++) {
		if (buffer[i] == ' ') xn++;
		else x[xn] = x[xn]*10+(buffer[i]-'0');
	}
	d[dn = 1] = -999999999999;
	for (i = j = 1; i <= n; i++) {
		S[i] = S[i-1]+x[i];
		while (j+1 <= dn && d[j+1] <= S[i]) j++;
		if (j > dn) j = dn;
		dp[i] = dp[L[j]] + A*(S[i]-S[L[j]])*(S[i]-S[L[j]])+C;
		while (dn >= 2 && g(L[dn]) <= d[dn]) dn--;
		L[++dn] = i;
		d[dn] = g(L[dn-1]);
	}
	printf("%lld",dp[n]+B*S[n]);
}
