// s : 입력 문자열
// group : 접미사의 첫 글자 (입력 문자열의 각 문자)
// sagroup : gap에 따른 Counting Sort 후의 group
// gap : Counting Sort시, group의 각 원소를 비교하는 길이
// lcp : 최장 공통 접두사 길이


const bool cmp(int i, int j) {
	if (group[i] != group[j]) return group[i] < group[j];
	return group[i + gap] < group[j + gap];
}

void getSuffixArray() {
	for (int i = 0; i < n; i++) {
		sa[i] = i;
		group[i] = s[i];
	}

	group[n] = -1, sagroup[n] = -1, gap = 1;

	while (gap < n) {					// Counting Sort
		sort(sa, sa + n, cmp);
		for (int i = 1; i < n; i++)
			sagroup[i] = sagroup[i - 1] + cmp(sa[i - 1], sa[i]);
		for (int i = 0; i < n; i++) group[sa[i]] = sagroup[i];

		if (sagroup[n - 1] == n - 1) break;
		gap *= 2;
	}
}
}

void getLcpArray() {
	for (int i = 0, k = 0; i < n; i++) {
		if (group[i] == 0) lcp[group[i]] = 0;
		else {
			for (int j = sa[group[i] - 1]; s[i + k] == s[j + k]; k++);
			lcp[group[i]] = k;

			if (k != 0) k--;
		}
	}
}
