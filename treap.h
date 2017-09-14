#include <bits/stdc++.h>
using namespace std;

class node {
public:
	int randval, sz, val;
	node *l, *r;

	node(int v);
	node(const node* const other);
	void upd();

	pair<node*, node*> cut(int i, int j);
	node* paste(node* v, int idx);
	int get(node* v, int idx);
	node* append(int x);
	void print();
};

node::node(int v) {
	randval = rand();
	val = v;
	sz = 1;
	l = nullptr, r = nullptr;
}

node::node(const node* const other) {
	randval = rand();
	sz = other->sz;
	val = other->val;
	l = other->l;
	r = other->r;
}
