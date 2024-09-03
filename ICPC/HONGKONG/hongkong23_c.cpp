#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

auto transpose = [](const auto& v) {
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
	if (n == 2 && m == 3) {
		vector res(n, string(m, '0'));
		res[0] = "001";
		res[1] = "011";
		return res;
	}

	vector res(n, string(m, '0'));
	int sz = 1, p = 0;
	while (1 << sz < n) sz++;
	for (int x = 0; x < sz; x++) {
		for (int i = 0; i < n; i++) {
			if (i >> x & 1) res[i][p]++;
			else res[i][p + 1]++;
		}
		p += 2;
	}

	auto check = [&](const string& s) -> bool {
		for (int j = 0; j < 2 * sz; j++) {
			string t(n, '0');
			for (int i = 0; i < n; i++) t[i] = res[i][j];
			if (s == t) return 0;
		}
		return 1;
	};

	for (int x = 0; (n >= 30 || x < 1 << n - 1) && p + 1 < m; x++) {
		if (2 * __builtin_popcount(x) == n) continue;
		string s(n, '0');
		for (int i = 0; i < min(n, 30); i++) if (x >> i & 1) s[i]++;
		if (!check(s)) continue;
		for (int i = 0; i < n; i++) res[i][p] = s[i];
		for (int i = 0; i < n; i++) res[i][p + 1] = s[i] ^ 1;
		p += 2;
	}

	vector brute(n, 0);
	for (int i = n / 2; i < n; i++) brute[i] = 1;
	while (p < m) {
		string s(n, '0');
		for (int i = 0; i < n; i++) if (brute[i]) s[i]++;
		next_permutation(brute.begin(), brute.end());
		if (!check(s)) continue;
		for (int i = 0; i < n; i++) res[i][p] = s[i];
		p++;
	}
	return res;
};

auto sol = [](int n, int m) {
	if (n * m & 1) return vector(0, string{});
	bool f = n > m;
	if (f) swap(n, m);
	if (n < 30 && 1 << n < m) return vector(0, string{});
	auto res = construct(n, m);
	if (f) res = transpose(res);
	return res;
};

int main() {
	fastio;
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