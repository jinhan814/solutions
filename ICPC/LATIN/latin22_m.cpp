#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

auto conv = [](const string& s) {
	i128 res = 0;
	for (char c : s) res = res << 1 | c & 1;
	return res;
};

auto check = [](const string& s, const auto& t) -> bool {
	const int n = t.size();
	const int m = s.size();
	vector a(m, conv(s));
	vector b(n, i128(0));
	for (int i = 1; i < m; i++) a[i] = a[i - 1] >> 1 | (a[i - 1] & 1) << m - 1;
	for (int i = 0; i < n; i++) b[i] = conv(t[i]);

	auto f = [&](int i, int j) -> bool { return !(b[i] & a[j]); };
	vector c(n, i128(0));
	vector q(0, pair(0, 0));
	for (int i = 0; i < m; i++) {
		if (!f(0, i)) continue;
		c[0] |= i128(1) << i;
		q.push_back({ 0, i });
	}
	while (q.size()) {
		auto [x, y] = q.back(); q.pop_back();
		if (x == n - 1) return 1;
		for (int d = 0; d < 4; d++) {
			int nx = x + "1012"[d] - '1';
			int ny = y + "2101"[d] - '1';
			if (ny < 0) ny = m - 1;
			if (ny >= m) ny = 0;
			if (nx < 0 || nx >= n || !f(nx, ny) || c[nx] >> ny & 1) continue;
			c[nx] |= i128(1) << ny;
			q.push_back({ nx, ny });
		}
	}
	return 0;
};

auto sol = [](string s, const auto& t) -> bool {
	if (check(s, t)) return 1;
	reverse(s.begin(), s.end());
	return check(s, t);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	string s; cin >> s;
	vector t(n, string{});
	for (int i = 0; i < n; i++) cin >> t[i];
	cout << "NY"[sol(s, t)] << '\n';
}