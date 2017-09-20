#define MX 312345
int a[MX * 2];
char s[MX * 2];
char buf[MX];

int main(void) {
	scanf("%s", buf);

 	//builld formatted string
 	for (int i = 0; i<strlen(buf) - 1; i++) {
	 	s[2 * i] = buf[i];
	 	s[2 * i + 1] = '#';
	}
	s[2 * strlen(buf) - 2] = buf[strlen(buf)-1];
	s[2 * strlen(buf) - 1] = 0;
	
	int r = -1, p = -1;
 	int len = 2 * strlen(buf) - 1;

 	for (int i = 0; i<len; i++) {
 	if (i <= r) a[i] = min(a[2 * p - i], r - i);
 	else a[i] = 0;
	while (i-a[i]-1>=0 && i+a[i]+1 < strlen(s) && s[i - a[i] - 1] == s[i + a[i] + 1]) {
 		a[i]++;
 	}
 	if (i + a[i] > r) {
		r = a[i] + i; p = i;
 	}
	scanf("%s", buf);

	//builld formatted string
	for (int i = 0; i<strlen(buf) - 1; i++) {
		s[2 * i] = buf[i];
		s[2 * i + 1] = '#';
	}
	s[2 * strlen(buf) - 2] = buf[strlen(buf)-1];
	s[2 * strlen(buf) - 1] = 0;
	int r = -1, p = -1;
	int len = 2 * strlen(buf) - 1;
	
	for (int i = 0; i<len; i++) {
		if (i <= r) a[i] = min(a[2 * p - i], r - i);
		else a[i] = 0;
		while (i-a[i]-1>=0 && i+a[i]+1 < strlen(s) && s[i - a[i] - 1] == s[i +
			a[i] + 1]) {
		 	a[i]++;
		}
	 
		if (i + a[i] > r) {
	 		r = a[i] + i; p = i;
	 	}
	}
}

