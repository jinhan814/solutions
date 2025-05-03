#include <bits/stdc++.h>
using namespace std;

auto get_fail = [](const string& s) {
	vector f(s.size(), 0);
	for (int i = 1, j = 0; i < s.size(); i++) {
		while (j && s[i] != s[j]) j = f[j - 1];
		if (s[i] == s[j]) f[i] = ++j;
	}
	return f;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		string s; cin >> s;
		vector f = get_fail(s);
		for (int i = 0, j = 0; i < n; i++) {
			while (j && s[i] == s[j]) j = f[j - 1];
			if (s[i] != s[j]) j++;
			cout << j << ' ';
			if (j == n) j = f[j - 1];
		}
		cout << '\n';
	}
}