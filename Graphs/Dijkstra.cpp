#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct Vertex {
	ll weight;
	ll vertex;

	Vertex() = default;
	Vertex(ll w, ll v) : weight(w), vertex(v) {}
};

bool operator>(const Vertex& lhs, const Vertex& rhs) {
	return lhs.weight > rhs.weight;
}

void Dijkstra(ll n, ll s, ll f) {

	--s; --f;
	vector<vector<Vertex>> graph(n, vector<Vertex>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ll weight;
			cin >> weight;
			if (weight == -1) 
				continue;
			graph[i].push_back(Vertex(weight, j));
		}
	}

	priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>> min_queue;
	vector<ll> dist(n, 1e9);
	vector<bool> used(n);
	
	Vertex start_vertex(0, s);
	min_queue.push(start_vertex);
	dist[s] = 0;

	while (!min_queue.empty()) {

		ll u = min_queue.top().vertex;
		min_queue.pop();
		
		if (used[u]) 
			continue;
		used[u] = true;
		for (auto& neigh : graph[u]) {
			ll index = neigh.vertex;
			ll w = neigh.weight;

			if (dist[index] > dist[u] + w) {
				dist[index] = dist[u] + w;
				min_queue.push(Vertex(dist[index], index));
			}
		}
	}	
	
	if (dist[f] == 1e9) {
		cout << "-1\n";
	} else {	
		cout << dist[f] << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n, s, f;
	cin >> n >> s >> f;
	Dijkstra(n, s, f);
	return 0;
}
