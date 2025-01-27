#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void count_sort(vector<int>& p, vector<int>& c) {
	
	int n = p.size();
	vector<int> cnt(n);
	
	for (auto now : c) {
		++cnt[now];
	}
	
	vector<int> p_new(n);
	vector<int> pos(n);
	pos[0] = 0;
	
	for (int i = 1; i < n; ++i) {
		pos[i] = pos[i - 1] + cnt[i - 1];
	}
	for (auto now : p) {
		int i = c[now];
		p_new[pos[i]] = now;
		++pos[i];
	}
	p = p_new;
}

void build(string str, vector<int>& p, vector<int>& c) {
	int n = str.size();
	{
		vector<pair<char, int>> a(n);
		for (int i = 0; i < n; ++i) {
			a[i] = { str[i], i };
		}
		
		sort(a.begin(), a.end());
		for (int i = 0; i < n; ++i) {
			p[i] = a[i].second;
		}
		c[p[0]] = 0;
		for (int i = 1; i < n; ++i) {
			if (a[i].first == a[i - 1].first) {
				c[p[i]] = c[p[i - 1]];	
			} else {
				c[p[i]] = c[p[i - 1]] + 1;
			}
		}
	}
	int k = 0;
	while ((1 << k) < n) {
		for (int i = 0; i < n; ++i) {
			p[i] = (p[i] - (1 << k) + n) % n;
		}
		count_sort(p, c);
		vector<int> c_new(n);
		c_new[p[0]] = 0;
		for (int i = 1; i < n; ++i) {
			pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n] };
			pair<int, int> now = { c[p[i]], c[(p[i] + (1 << k)) % n] };
			
			if (now == prev) {
				c_new[p[i]] = c_new[p[i - 1]];
			} else {
				c_new[p[i]] = c_new[p[i - 1]] + 1;
			}
		}
		c = c_new;
		++k;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string str;
	cin >> str;
	str += '$';

	vector<int> p(str.size());
	vector<int> c(str.size());

	build(str, p, c);
	for (int i = 0; i < str.size(); ++i) {
		cout << p[i] << " ";
	}
	return 0;
}
