#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

bool dfs(int v, vector<int>& color, vector<vector<int>>& graph) {
	bool haveCycle = false;
	color[v] = 1;
	for (auto now : graph[v]) {
		if (color[now] == 1) {
			haveCycle = true;
		} else if (color[now] == 0) {
			haveCycle = haveCycle ||  dfs(now, color, graph);
		}
	}
	color[v] = 2;
	return haveCycle;
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
	
	vector<int> color(n);
	bool have_cycle = false;
	for (int i = 0; i < n; ++i) {
		if (color[i] == 0) {
			have_cycle = have_cycle || dfs(i, color, graph);
		}
	}
	cout << "cycle: " << have_cycle << "\n";
	return 0;
}
