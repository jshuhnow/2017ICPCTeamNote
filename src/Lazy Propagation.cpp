typedef long long ll;

ll init(vector<ll> &v, vector<ll> &tree, int node, int start, int end) {
	if (start == end) {
		return tree[node] = v[start];
	}
	else {
		return tree[node] = init(v, tree, node * 2, start, (start + end) / 2) + init(v, tree, node * 2 + 1, (start + end) / 2 + 1, end);
	}
}

void update_lazy(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end) {
	if (lazy[node] != 0) {
		tree[node] += (end - start + 1)*lazy[node];
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void update(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end, int left, int right, ll val) {
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

ll sum(vector<ll> &tree, vector<ll> &lazy, int node, int start, int end, int left, int right) {
	update_lazy(tree, lazy, node, start, end);
	if (left > end || right < start) {
		return 0;
	}
	if (left <= start && end <= right) {
		return tree[node];
	}

	return sum(tree, lazy, node * 2, start, (start + end) / 2, left, right) + sum(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}