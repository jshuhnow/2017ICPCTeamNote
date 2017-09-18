typedef pair<int, int> ii;

struct mycomp {
	bool operator() (const ii &l, const ii &r) const {
		return l.second < r.second;
	}
};
vector<ii> LIS(vector<ii> v) {
	map < ii, int, mycomp> m;
	map < ii, int, mycomp>::iterator k, l;
	vector<ii> res;
	
	const int N = v.size(); 
	vector<int> pre(N, -1);

	for (int i = 0; i < N; i++) {
		if (m.insert({ v[i], i }).second) {
			k = m.find(v[i]);
			l = k; k++;
			if (l == m.begin()) {
				pre[i] = -1;
			}
			else {
				l--;
				pre[i] = l->second;
			}
			if (k != m.end()) {
				m.erase(k);
			}
		}
	}
	k = m.end(); k--;
	int j = k->second;
	while (j != -1) {
		res.push_back(v[j]);
		j = pre[j];
	}
	reverse(res.begin(), res.end());
	return res;
}

int main(void) {
	int N; scanf("%d", &N);

	vector<ii> v;
	for (int i = 0; i < N; i++) {
		int a, b; scanf("%d %d", &a, &b);
		v.push_back({ a, b });
	}
	sort(v.begin(), v.end());

	auto r = LIS(v);
	auto it = r.begin();
	printf("%d\n", v.size() - r.size());
	for (auto e : v) {
		if (e != (*it)) {
			printf("%d\n", e.first);
		}
		else {
			it++;
		}
	}

}
