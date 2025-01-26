#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void dfs(ll v, ll p, ll time, vector<ll>& res, vector<bool>&used, vector<ll>& in, vector<ll>& out, vector<vector<ll>>& graph) {
	
	used[v] = true;
	in[v] = time + 1;
	out[v] = time + 1;
	++time;
	
	ll nodes = 0;
	for (int i = 0; i < graph[v].size(); ++i) {
		ll to = graph[v][i];
		if (to == p)  {
			continue;
		}
		
		if (used[to]) {
			out[v] = min(out[v], in[to]);
		} else {
			dfs(to, v, time, res, used, in, out, graph);
			out[v] = min(out[v], out[to]);
			if (out[to] >= in[v] && p != -1) {
				res.push_back(v);
			}	
			++nodes;
		}
	}
	
	if (p == -1 && nodes > 1) {
		res.push_back(v);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<vector<ll>> graph(n, vector<ll>());
	for (int i = 0; i < m; ++i) {
		ll to, from;
		cin >> to >> from;
		graph[to].push_back(from);
		graph[from].push_back(to);
	}

	vector<bool> used(n);
	vector<ll> res;
	vector<ll> in(n, 1e9);
	vector<ll> out(n, 1e9);
	ll time = 0;
	dfs(0, -1, time, res, used, in, out, graph);
	for (auto now : res) {
		cout << now << " ";
	}
	return 0;
}
