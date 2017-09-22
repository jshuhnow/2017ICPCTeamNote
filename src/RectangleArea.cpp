typedef long long int lld;
int tree[MX*4], lazy[MX*4];
int len, r;

struct line {
	int x_idx, y1_idx, y2_idx;
	int inc;
};
struct rect {
	int x1, x2, y1, y2;
};
vector<rect> vec_rects;
vector<int> vec_x_coords, vec_y_coords;
vector<line> vec_lines;

int get_idx(const vector<int> &vec_coord, const int val) {
	return lower_bound(vec_coord.begin(), vec_coord.end(), val) - vec_coord.begin();
}
bool line_comp(const line &l, const line &r)  {
	return l.x_idx < r.x_idx;
}

void make_unique( vector<int> &vec) {
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
}
void update(int node, int start, int end, int left, int right, int inc) {
	if (start > end || right < start || end < left) return; 

	if (left <= start && end <= right) {
		lazy[node] += inc;
	}
	else {
		int mid = (start + end) / 2;
		update(node * 2, start, mid, left, right, inc);
		update(node * 2 + 1, mid + 1, end, left, right, inc);
	}

	if (lazy[node] > 0) {
		tree[node] = vec_y_coords[end+1]- vec_y_coords[start];
	}
	else {
		if (node <= len-r) {
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
		else {
			tree[node] = 0;
		}
	}
}
lld solve() {
	lld res = 0;
	int N; scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		int x1, x2, y1, y2; scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
		vec_rects.push_back({ x1, x2, y1, y2 });
		vec_x_coords.push_back(x1); vec_x_coords.push_back(x2);
		vec_y_coords.push_back(y1); vec_y_coords.push_back(y2);
	}
	make_unique(vec_x_coords); make_unique(vec_y_coords);
	for (const rect &current_rect : vec_rects) {
		vec_lines.push_back({
			get_idx(vec_x_coords, current_rect.x1),
			get_idx(vec_y_coords, current_rect.y1),
			get_idx(vec_y_coords, current_rect.y2),
			1
		});
		vec_lines.push_back({
			get_idx(vec_x_coords, current_rect.x2),
			get_idx(vec_y_coords, current_rect.y1),
			get_idx(vec_y_coords, current_rect.y2),
			-1
		});
	}
	sort(vec_lines.begin(), vec_lines.end(), line_comp);

	const int tree_size = vec_y_coords.size() - 1;
	len = 1, r = 1;
	while (r < tree_size) {
		r *= 2;
		len += r;
	}

	for (int i = 0; i < vec_lines.size(); i++){
		const line &current_line = vec_lines[i];
		
		
		if (i > 0) {
			const line &prev_line = vec_lines[i - 1];
			res += lld(tree[1]) *
				lld(vec_x_coords[current_line.x_idx] - vec_x_coords[prev_line.x_idx]);
		}
		update(1, 0, r - 1,
			current_line.y1_idx,
			current_line.y2_idx - 1,
			current_line.inc);

	}
	return res;
}
