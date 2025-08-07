#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto get_fail = [](const auto& s) {
	const int n = s.size();
	vector f(n, 0);
	for (int i = 1, j = 0; i < n; i++) {
		while (j && s[i] != s[j]) j = f[j - 1];
		if (s[i] == s[j]) f[i] = ++j;
	}
	return f;
};

auto sol = [](int n, auto v) {
	i64 acc = 0;
	for (int i = 0; i < n; i++) acc += v[i];
	if (acc >= n || acc == 0) return 1;
	for (int i = 2 * n - 1; i >= 0; i--) {
		if (v[i % n] == 0) continue;
		v[(i + n - 1) % n] += v[i % n] - 1;
		v[i % n] = 1;
	}
	auto nv = v;
	nv.insert(nv.end(), v.begin(), v.end());
	auto f = get_fail(nv);
	for (int i = n; i < 2 * n; i++) {
		if (f[i] < n) continue;
		return i - n + 1;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}