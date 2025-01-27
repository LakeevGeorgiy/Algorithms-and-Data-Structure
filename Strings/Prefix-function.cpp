#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

void prefix_function(string& str, vector<ll>& prefix) {
	for (int i = 1; i < str.size(); ++i) {
	
		int temp = prefix[i - 1];
		while (str[i] != str[temp] && temp > 0) {
			temp = prefix[temp - 1];
		}

		if (str[i] == str[temp]) {
			prefix[i] = temp + 1;
		}
	}
	
	for (auto now : prefix) 
		cout << now << " ";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	string str;
	cin >> str;
	vector<ll> prefix(str.size());
	prefix_function(str, prefix);
	return 0;
}
