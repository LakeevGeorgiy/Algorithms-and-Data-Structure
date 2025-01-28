#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<ll>> graph(n, vector<ll>());
	
	for (int i = 0; i < m; ++i) {	
		int from, to;
		cin >> from >> to;
		--from; --to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	int start_vertex = 0;
	queue<int> q;
	q.push(start_vertex);
	vector<int> dist(n, 1e9);
	dist[start_vertex] = 0; 

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < graph[v].size(); ++i) {
			int u = graph[v][i];
			if (dist[u] > dist[v] + 1) {
				dist[u] = dist[v] + 1;
				q.push(u);
			}
		}
	}
	for (auto now : dist) {
		cout << now << " ";
	}
	return 0;
}
