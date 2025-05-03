#include <bits/stdc++.h>
using namespace std;

auto transpose = [](auto v) {
	const int n = v.size();
	const int m = v[0].size();
	vector res(m, string(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			res[j][i] = v[i][j];
	}
	return res;
};

auto construct = [](int n, int m) {
	if (n == 3 && m == 2) {
		vector res(n, string(m, '0'));
		res = { "00", "01", "11" };
		return res;
	}
	vector res(n, string(m, '0'));
	int p = 0, sz = m - 1 ? __lg(m - 1) + 1 : 1;
	for (int x = 0; x < sz; x++) {
		for (int i = 0; i < m; i++) {
			if (i >> x & 1) res[p][i]++;
			else res[p + 1][i]++;
		}
		p += 2;
	}
	auto check = [&](const string& s) -> bool {
		for (int i = 0; i < 2 * sz; i++) if (res[i] == s) return 0;
		return 1;
	};
	for (int x = 0; (m >= 30 || x < 1 << m - 1) && p + 1 < n; x++) {
		if (2 * __builtin_popcount(x) == m) continue;
		string s(m, '0');
		for (int i = 0; i < m; i++) if (x >> i & 1) s[i]++;
		if (!check(s)) continue;
		res[p++] = s;
		for (char& c : s) c ^= 1;
		res[p++] = s;
	}
	vector b(m, 0);
	for (int i = m / 2; i < m; i++) b[i] = 1;
	while (p < n) {
		string s(m, '0');
		for (int i = 0; i < m; i++) if (b[i]) s[i]++;
		next_permutation(b.begin(), b.end());
		if (!check(s)) continue;
		res[p++] = s;
	}
	return res;
};

auto sol = [](int n, int m) {
	if (n * m & 1) return vector(0, string{});
	bool f = n < m;
	if (f) swap(n, m);
	if (m < 30 && 1 << m < n) return vector(0, string{});
	auto res = construct(n, m);
	if (f) res = transpose(res);
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		auto res = sol(n, m);
		if (res.empty()) {
			cout << "NO" << '\n';
		}
		else {
			cout << "YES" << '\n';
			for (int i = 0; i < n; i++) cout << res[i] << '\n';
		}
	}
}