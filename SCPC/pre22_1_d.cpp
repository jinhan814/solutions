#include <bits/stdc++.h>
using namespace std;

auto get_fail = [](const string& s) {
	const int n = s.size();
	vector f(n, 0);
	for (int i = 1, j = 0; i < n; i++) {
		while (j && s[i] != s[j]) j = f[j - 1];
		if (s[i] == s[j]) f[i] = ++j;
	}
	return f;
};

auto kmp = [](const string& s, const string& t) {
	vector ret(0, 0);
	vector f = get_fail(t);
	for (int i = 0, j = 0; i < s.size(); i++) {
		while (j && s[i] != t[j]) j = f[j - 1];
		if (s[i] == t[j] && ++j == t.size()) {
			ret.push_back(i - t.size() + 1);
			j = f[j - 1];
		}
	}
	return ret;
};

auto sol = [](int n, int m, string s, string t) -> bool {
	vector p1(n + 1, 0), p2(n + 1, 0);
	for (int i = 0; i < n; i++) {
		p1[i + 1] = p1[i] + (s[i] == t[0]);
		p2[i + 1] = p2[i] + (s[i] == t[m - 1]);
	}
	int l = 0, r = m - 1;
	while (l < m - 1 && t[l] == t[l + 1]) l++;
	while (r && t[r] == t[r - 1]) r--;
	if (l == m - 1) return p1[n] >= m;
	if (l + 1 == r) {
		auto it = lower_bound(p1.begin(), p1.end(), l + 1);
		if (it == p1.end()) return 0;
		if (p2[n] - p2[it - p1.begin() - 1] < m - r) return 0;
		return 1;
	}
	int sz = r - l - 1;
	for (int i : kmp(s, t.substr(l + 1, sz))) {
		if (p1[i] < l + 1) continue;
		if (p2[n] - p2[i + sz] < m - r) continue;
		return 1;
	}
	return 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, m; cin >> n >> m;
		string s, t; cin >> s >> t;
		bool res = sol(n, m, s, t);
		cout << "Case #" << tc_num << '\n';
		cout << (res ? "YES" : "NO") << '\n';
	}
}