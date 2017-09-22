#define MX 100000
char T[MX], P[MX]; // T - sentece, P - word
int b[MX], n, m;  // b- failure function, len(T) = n , len(P) = m;

void kmpPreprocess() {
	int i = 0, j=-1; b[0] = -1;
	while(i<m) {
		while (j>=0 && P[i] != P[j]) j=b[j];
		i++; j++;
		b[i] = j;
	}
}

void kmpSearch() {
	int i=0, j=0;
	while(i<n) {
		while(j>=0 && T[i] != P[j]) j=b[j];
		i++; j++;
		if (j==m) {
			printf("Found at %d\n", i-j);
			j=b[j];
		}
	}
}
