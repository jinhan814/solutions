#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, const string& s) {
	string res(n, '-');
	int p = 0;
	while (p < n && s[p] != 'O') p++;
	if (p == n) return res;
	for (int i = 0; i < n; i++) if (s[i] == 'O') res[i] = '+';
	for (int l = 0, r = 0; l < n; l = r) {
		while (r < n && s[(p + l) % n] == s[(p + r) % n]) r++;
		if (s[(p + l) % n] == 'O') continue;
		if (r - l + 1 & 1) return string("");
		for (int i = l; i - l < r - 1 - i; i++) res[(p + i) % n] = '+';
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	string res = sol(n, s);
	if (res.empty()) cout << "NO" << '\n';
	else cout << "YES" << '\n' << res << '\n';
}