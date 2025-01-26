#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct ListOfEdges {
	ll weight;
	ll from;
	ll to;
};

bool operator<(ListOfEdges& lhs, ListOfEdges& rhs) {
	return lhs.weight < rhs.weight;
}

void mst(ll n, ll m) {

	vector<ListOfEdges> a(m);
	vector<ll> id(n + 1);
	
	iota(id.begin(), id.end(), 0);

	for (int i = 0; i < m; ++i) {
		cin >> a[i].from >> a[i].to >> a[i].weight;
	}

	sort(a.begin(), a.end());
	ll sum = 0;
	vector<pair<ll, ll>> ans;
	ll pok = 0;
	for (int i = 0; i < m; ++i) {
		ll to = a[i].to;
		ll from = a[i].from;
		if (id[to] != id[from]) {
			sum += a[i].weight;
			ans.push_back({ a[i].from, a[i].to });
			ll old = id[to];
			for (int j = 1; j <= n; ++j) {
				if (id[j] == old)
					id[j] = id[from];
			}
		}
	}
	cout << sum << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n, m;
	cin >> n >> m;
	mst(n,m);
	return 0;
}
