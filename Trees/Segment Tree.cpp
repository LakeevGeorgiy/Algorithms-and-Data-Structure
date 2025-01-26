#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct Segtree {
	vector<ll> tree;
	ll size;
	
	void init(int n);
	
	void build(vector<ll>& a, ll x, ll lx, ll rx);
	void build(vector<ll>& a);
	
	void set(ll i, ll v, ll x, ll lx, ll rx);
	void set(ll i, ll v);
	
	ll sum(ll l, ll r, ll x, ll lx, ll rx);
	ll sum(ll l, ll r);
};

void Segtree::init(int n) {
	size = 1;
	while (size < n) size *= 2;
	tree.assign(2 * size - 1, 0);
}

void Segtree::build(vector<ll>& a, ll x, ll lx, ll rx) {
	if (rx - lx == 1) {
		if (lx < a.size())
			tree[x] = a[lx];
	} else {
		ll m = (lx + rx) / 2;
		build(a, 2 * x + 1, lx, m);
		build(a, 2 * x + 2, m , rx);
		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
	}
}

void Segtree::build(vector<ll>& a) {
	init(a.size());
	build(a, 0, 0, size);
}

void Segtree::set(ll i, ll v, ll x, ll lx, ll rx) {
	if (rx - lx == 1) {
		tree[x] = v;
		return;
	}

	ll m = (lx + rx) / 2;
	if (i < m) {
		set(i, v, 2 * x + 1, lx, m);
	} else {
		set(i, v, 2 * x + 2, m, rx);
	}
	
	tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
}

void Segtree::set(ll i, ll v) {
	set(i, v, 0, 0, size);
}

ll Segtree::sum(ll l, ll r, ll x, ll lx, ll rx) {
	if (l >= rx || lx >= r) {
		return 0;
	} 
	
	if (lx >= l && rx <= r) {
		return tree[x];
	}

	ll m = (lx + rx) / 2;
	ll s1 = sum(l, r, 2 * x + 1, lx, m);
	ll s2 = sum(l, r, 2 * x + 2, m, rx);
	return s1 + s2;
}

ll Segtree::sum(ll l, ll r) {
	return sum(l, r, 0, 0, size);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i) 
		cin >> a[i];

	Segtree st;
	st.build(a);
	for (int t = 0; t < m; ++t) {
		int c;
		cin >> c;
		if (c == 1) {
			ll i, v;
			cin >> i >> v;
			st.set(i, v);
		} else {
			ll l, r;
			cin >> l >> r;
			cout << st.sum(l, r) << "\n";
		}
	}
	return 0;
}
