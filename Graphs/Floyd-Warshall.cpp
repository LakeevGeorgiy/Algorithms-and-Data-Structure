#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void floyd(ll n) {
	
	vector<vector<ll>> graph(n, vector<ll>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> graph[i][j];
		}
	}
	
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				graph[i][j] = min({graph[i][j], graph[i][k] + graph[k][j]});
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << graph[i][j] << " ";
		}
		cout << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n;
	cin >> n;
	floyd(n);
	return 0;
}
