#include <stdio.h>
struct Node {
    Node *l, *r, *p;
    int key;
    int cnt;
    int sum, value, lazy;
    bool inv;
} *root;

void update(Node *x) {
    x->cnt = 1;
    x->sum = x->value;
    if (x->l) {
        x->cnt += x->l->cnt;
        x->sum += x->l->sum;
    }
    if (x->r) {
        x->cnt += x->r->cnt;
        x->sum += x->r->sum;
    }

}
void rotate(Node *x) {
    Node *p = x->p;Node *b;
    if (x == p->l) {
        p->l = b = x->r;
        x->l = p;
    } else {
        p->r = b = x->l;
        x->l = p;
    }
    x->p = p->p;
    p->p = x;
    if (b) b->p = p;
    (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
    update(p);
    update(x);
}
void splay(Node *x) {
    while (x->p) {
        Node *p = x->p, *g = p->p;
        if (g) rotate((x==p->l) == (p == g->l) ? p: x);
        rotate(x);
    }
}
void insert(int key) {
    Node *p = root, **pp;
    if (!p) {
        Node *x = new Node;
        root = x;
        x->l = x->r = x->p = NULL;
        x->key = key;
        return;
    }
    while(1) {
        if (key == p->key) return;
        if (key < p->key) {
            if (!(p->l)) {
                pp = &p->l;
                break;
            }
            p = p->l;
        } else {
            if (! (p->r)) {
                pp = &p->r;
                break;
            }
            p = p->r;
        }
    }
    Node *x = new Node;
    *pp = x;
    x->l = x->r = NULL;
    x->p = p;
    x->key = key;
    splay(x);
}
bool find(int key) {
    Node *p = root;
    if (!p) return false;
    while(p) {
        if (key == p->key) break;
        if (key < p->key) {
            if (!p->l) break;
            p = p->l;
        } else {
            if (! p->r) break;
            p = p->r;
        }
    }
    splay(p);
    return key == p->key;
}
void remove(int key) {
    if (!find(key))return;
    Node *p = root;
    if (p->l) {
        if (p->r) {
            root = p->l;
            root->p = NULL;
            Node *x = root;
            while (x->r) x=x->r;
            x->r = p->r;
            p->r->p = x;
            splay(x);
            delete p;
            return;
        }
        root = p->l;
        root->p = NULL;
        delete p;
        return;
    }
    if (p->r) {
        root = p->r;
        root->p = NULL;
        delete p;
        return;
    }
    root = NULL;
}

void propagate(Node *x) {
    x->value += x->lazy;
    if (x->inv) {
        Node *t = x->l; x->l = x->r; x->r = t;
        x->inv = false;
        if (x->l) x->l->inv = !x->l->inv;
        if (x->r) x->r->inv = !x->r->inv;
    }
    if (x->l) {
        x->l->lazy += x->lazy;
        x->l->sum += x->l->cnt * x->lazy;
    }
    if (x->r) {
        x->r->lazy += x->lazy;
        x->r->sum += x->r->cnt * x->lazy;
    }
    x->lazy = 0;
}

//Note that k is 0-base !
void findKth(int k) {
    Node *x = root;
    propagate(x);
    while(1) {
        while(x->l && x->l->cnt > k) {
            x = x->l;
            propagate(x);
        }
        if (x->l) k -= x->l->cnt;
        if (!k--) break;
        x = x->r;
        propagate(x);
    }
    splay(x);
}

void init(int n) {
    Node *x;
    int i;
    root = x = new Node;
    x->l= x->= x->p = NULL;
    x->cnt = n;
    x->sum = x->value = 0;
    for (i=1; i<n; i++) {
        x->r = new Node;
        x->r->p = x;
        x = x->r;
        x->l = x->r = NULL;
        x->cnt = n-i;
        x->sum = x->value = 0;
    }
}
void add(int i, int z) {
    findKth(i);
    root->sum += z;
    root->value += z;
}
// [l, r] inclusive
void interval(int l, int r) {
    findKth(l-1);
    Node *x = root;
    root = x->r;
    root->p = NULL;
    findKth(r-l+1);
    x->r = root;
    root->p = x;
    root = x;
}
int sum(int l, int r) {
    interval(l, r);
    return root->r->l->sum;
}

void add(int l, int r, int z) {
    interval(l, r);
    Node *x = root->r->l;
    x->sum += x->cnt * z;
    x->lazy += z;
}
void reverse(int l, int r) {
    interval(l, r);
    Node *x = root->r->l;
    x->inv = !x->inv;
}
int a[100001];
int main(void) {
    int N; scanf("%d", &N);
    init(N);
    for (int i=1; i<=N; i++) {
        scanf("%d", a+i);
    }
    for (int i=1; i<=N; i++) {
        insert(a[i]);
        root->value=i;
    }
    for (int i=1; i<=N; i++) {
        find(i);
    }

}
