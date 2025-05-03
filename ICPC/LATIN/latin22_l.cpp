#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int m; cin >> m;

	auto nxt = [&](int bias) -> int {
		vector f(1, 0);
		for (int i = 1, j = 0; bias + i < s.size(); i++) {
			while (j && s[bias + i] != s[bias + j]) j = f[j - 1];
			f.push_back(s[bias + i] == s[bias + j] ? ++j : 0);
			if (i + 1 - f.back() > m) { f.pop_back(); break; }
		}
		return f.size();
	};

	int res = 0, i = 0;
	while (i < s.size()) res++, i += nxt(i);
	cout << res << '\n';
}