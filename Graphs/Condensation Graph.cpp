#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void topsort(int v, vector<bool>& used, vector<int>& order, vector<vector<int>>& graph) {
	used[v] = true;
	for (auto now : graph[v]) {
		if (!used[now])
			topsort(now, used, order, graph);
	}
	order.push_back(v);
}

void dfs(int v, int cnt, vector<int>& components, vector<vector<int>>& graph) {
	components[v] = cnt;
	for (auto now : graph[v]) {
		if (components[now] == 0)
			dfs(now, cnt, components, graph);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> graph(n, vector<int>());
	vector<vector<int>> rgraph(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		int from, to;
		cin >> from >> to;
		--from; --to;
		graph[from].push_back(to);
		rgraph[to].push_back(from);
	}

	vector<bool> used(n);
	vector<int> order;
	for (int i = 0; i < n; ++i) {
		if (!used[i])
			topsort(i, used, order, graph);
	}
	reverse(order.begin(), order.end());
	
	int cnt = 1;
	vector<int> components(n);
	for (auto now : order) {
		if (components[now] == 0) {
			dfs(now, cnt, components, rgraph);
			++cnt;
		}
	}

	cout << cnt - 1 << "\n";
	for (auto now : components) {
		cout << now << " ";
	}
	return 0;
}
