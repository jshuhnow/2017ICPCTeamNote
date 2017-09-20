typedef long long ll;

// h : 2^h>N 중 가장 작은 h, tree_size : Segment Tree의 총 노드 수
// tree : Segment Tree, v : 입력 배열 -> tree size : 4 * N
// node : Segment Tree에서 현재 노드 번호( 1 - base )
// start : 현재 노드가 포함하는 범위의 시작, end : 현재 노드가 포함하는 범위의 끝 ( 1 - base )
// left : update하는 구간의 시작, right : update하는 구간의 끝 ( 1 - base )

int get_height(int n) {
	int cnt = 0, t = 1;
	while (t < n) {
		cnt++;
		t *= 2;
	}
	return cnt;
}

long long init(vector<long long> &v, vector<long long> &tree, int node, int start, int end) {
	if (start == end) {
		return tree[node] = v[start];
	}
	else {
		return tree[node] = init(v, tree, node * 2, start, (start + end) / 2) + init(v, tree, node * 2 + 1, (start + end) / 2 + 1, end);
	}
}

void update_lazy(vector<long long> &tree, vector<long long> &lazy, int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] += (end - start + 1)*lazy[node];
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(vector<long long> &tree, vector<long long> &lazy, int node, int start, int end, int left, int right, long long val) {
	update_lazy(tree, lazy, node, start, end);
	if (left > end || right < start) {
		return;
	}
	if (left <= start && end <= right) {
		tree[node] += (end - start + 1)*val;
		if (start != end) {
			lazy[node * 2] += val;
			lazy[node * 2 + 1] += val;
		}
		return;
	}

	update(tree, lazy, node * 2, start, (start + end) / 2, left, right, val);
	update(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

long long sum(vector<long long> &tree, vector<long long> &lazy, int node, int start, int end, int left, int right) {
	update_lazy(tree, lazy, node, start, end);
	if (left > end || right < start) {
		return 0;
	}
	if (left <= start && end <= right) {
		return tree[node];
	}

	return sum(tree, lazy, node * 2, start, (start + end) / 2, left, right) + sum(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}