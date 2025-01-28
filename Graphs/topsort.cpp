#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void dfs(int v, vector<bool>& used, vector<int>& topsort, vector<vector<int>>& graph) {
	used[v] = true;
	for (auto now : graph[v]) {
		if (used[now])
			continue;
		dfs(now, used, topsort, graph);
	}
	topsort.push_back(v);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, m;
	cin >> n >> m;

	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		int from, to;
		cin >> from >> to;
		--from; --to;
		graph[from].push_back(to);
	}
		
	vector<int> topsort;
	vector<bool> used(n);
	for (int i = 0; i < n; ++i) {
		if (!used[i])
			dfs(i, used, topsort, graph);
	}

	reverse(topsort.begin(), topsort.end());
	for (auto now : topsort) {
		cout << now + 1 << " ";
	}
	return 0;
}
