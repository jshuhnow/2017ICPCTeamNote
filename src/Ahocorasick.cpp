#define ll long long
const int ALPHABETS = 27;
int toNum(char c) {
	return c ? ¡®a¡¯;
}
struct node {
	node *children[ALPHABETS];
	int end;
	node() : end(false) { for (int i = 0; i < ALPHABETS; i++) children[i] = NULL; };
 	node *fail;
	void insert(const char *key) {
		if (*key == 0)
 			end = 1;
 		else
 		{
 			int next = toNum(*key);
 			if (children[next] == NULL)
 			children[next] = new node();
 			children[next]->insert(key + 1);
 		}
 	}
};
void FFC(node* root) {
	queue<node*> q;
	root->fail = root;
	q.push(root);

	while (!q.empty()) {
		node* here = q.front(); q.pop();
		for (int edge = 0; edge< ALPHABETS; edge++) {
			node *child = here->children[edge];
			if (!child) continue;
			if (here == root) child->fail = root;
			else {
				node *t = here->fail;
				while (t != root && t->children[edge] == NULL)
					t = t->fail;
				if (t->children[edge]) t = t->children[edge];
					child->fail = t;
			}
			child->end += child->fail->end;
			q.push(child);
		}
	}
}
int aho(const string &s, node *root) {
	int ret = 0;
	node *state = root;
	int size = s.size();
	for (int i = 0; i < size; i++) {
	int chr = toNum(s[i]);
	while (state != root && state->children[chr] == NULL)
 		state = state->fail;
 	if (state->children[chr]) state = state->children[chr];
 		ret += state->end;
 	}
	return ret;
}
