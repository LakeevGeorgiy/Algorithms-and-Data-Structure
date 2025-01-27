#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string str;
	cin >> str;

	vector<ll> z(str.size());
	ll l = 0;
	ll r = 0;
	
	for (int i = 1; i < str.size(); ++i) {
		if (r >= i) {
			z[i] = min(z[i -l], r - i + 1);
		}

		while (z[i] + i < str.size() && str[z[i]] == str[z[i] + i]) {
			++z[i];
		}

		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	for (auto now : z) 
		cout << now << " ";
	return 0;
}
