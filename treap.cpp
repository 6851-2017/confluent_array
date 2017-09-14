#include "treap.h"

int vsz(node* v) {
	return (v == nullptr) ? 0 : v->sz;
}

void node::upd() {
	sz = 1 + vsz(l) + vsz(r);
}

node* merge(node* l, node* r) {
	if (l == nullptr && r == nullptr) return nullptr;
	if (l == nullptr) return r;
	if (r == nullptr) return l;

	node* res;
	if (l->randval > r->randval) {
		res = new node(l);
		res->r = merge(l->r, r);
	} else {
		res = new node(r);
		res->l = merge(l, r->l);
	}
	res->upd();
	return res;
}

// first will have size k
pair<node*, node*> split(const node* v, int k) {
	if (v == nullptr) return {nullptr, nullptr};

	node* splitv = new node(v);
	int lsz = vsz(v->l);
	if (lsz < k) {
		auto p = split(v->r, k - lsz - 1);
		splitv->r = p.first;
		splitv->upd();
		return {splitv, p.second};
	}
	auto p = split(v->l, k);
	splitv->l = p.second;
	splitv->upd();
	return {p.first, splitv};
}

// returns (cut out, remaining array)
// [i, j) is cut out
pair<node*, node*> node::cut(int i, int j) const {
	auto cut1p = split(this, i);
	auto cut2p = split(cut1p.second, j - i);
	return {cut2p.first, merge(cut1p.first, cut2p.second)};
}

node* node::paste(node* v, int idx) const {
	auto cutp = split(this, idx);
	return merge(cutp.first, merge(v, cutp.second));
}

int node::get(int idx) const {
	int lsz = vsz(l);
	if (lsz == idx) return val;
	if (lsz > idx) return l->get(idx);
	return r->get(idx - lsz - 1);
}

node* node::set(int val, int idx) const {
	// ignore the part we cut out
	node* res = cut(idx, idx + 1).second;
	return res->paste(new node(val), idx);
}

node* node::append(int x) const {
	node* nv = new node(x);
	return paste(nv, sz);
}

void node::print() const {
	if (l != nullptr) l->print();
	cout << val << ' ';
	if (r != nullptr) r->print();
}

int main() {
	node *v = new node(-1);
	for (int i = 0; i < 10; i++) {
		v = v->append(i);
		v->print();
		cout << endl;
	}
	v = v->set(20, 1);
	v->print();
	cout << "\n result after all append and set!\n" << endl;
	v = v->paste(v, 3);
	v->print();
	cout << "\n after paste!\n" << endl;
	v = v->paste(v, 10);
	v->print();
	cout << "\n after paste 2!\n" << endl;
	v = v->set(100, 0);
	for (int i = 0; i < v->sz; i++)
		cout << v->get(i) << ' ';
	cout << "\n after setting first element to 100!\n" << endl;
}
