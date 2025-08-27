#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int mn = 1 << 30, mx = 0;
	for (int i = 1; i <= n; i++) {
		mn = min(mn, v[i]);
		mx = max(mx, v[i]);
	}
	if (mn == mx) return vector(0, array{ 0, 0, 0 });
	vector p1(n + 1, 0), p2(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		v[i] = v[i] == mn ? 1 : v[i] == mx ? 2 : 0;
		p1[i] = p1[i - 1] + (v[i] == 1);
		p2[i] = p2[i - 1] + (v[i] == 2);
	}
	if (p1[n] + p2[n] == n && abs(p1[n] - p2[n]) <= 1) return vector(0, array{ 0, 0, 0 });
	int l = 1, r = n;
	while (l < n && v[l]) l++;
	while (r > 1 && v[r]) r--;
	vector c1(l + 1, 0), c2(l + 1, 0);
	for (int i = r, j = 0; i <= n; i++) {
		if (p1[i] == 0) continue;
		while (j + 1 <= l && p1[i] - p1[j]) j++, c1[j - p1[j - 1]] = j;
		int lo = i - p1[i] + p1[n] + 1 - (n + 1) / 2;
		int hi = i - p1[i] + p1[n] + 1 - n / 2;
		if (0 <= lo && lo <= l && c1[lo]) return vector{ array{ 1, c1[lo], i } };
		if (0 <= hi && hi <= l && c1[hi]) return vector{ array{ 1, c1[hi], i } };
	}
	for (int i = r, j = 0; i <= n; i++) {
		if (p2[i] == 0) continue;
		while (j + 1 <= l && p2[i] - p2[j]) j++, c2[j - p2[j - 1]] = j;
		int lo = i - p2[i] + p2[n] + 1 - (n + 1) / 2;
		int hi = i - p2[i] + p2[n] + 1 - n / 2;
		if (0 <= lo && lo <= l && c2[lo]) return vector{ array{ 2, c2[lo], i } };
		if (0 <= hi && hi <= l && c2[hi]) return vector{ array{ 2, c2[hi], i } };
	}
	while (p1[r] - p1[l - 1] + p2[r] - p2[l - 1] == 0) l > 1 ? l-- : r++;
	for (int i = 1; i < n; i++) {
		if (p1[i] == 0) continue;
		if (p2[n] - p2[i] == 0) continue;
		if (i < n - i) return vector{ array{ 2, i + 1, n }, array{ 1, 1, n / 2 } };
		return vector{ array{ 1, 1, i }, array{ 2, n + 1 - n / 2, n } };
	}
	for (int i = 1; i < n; i++) {
		if (p2[i] == 0) continue;
		if (p1[n] - p1[i] == 0) continue;
		if (i < n - i) return vector{ array{ 1, i + 1, n }, array{ 2, 1, n / 2 } };
		return vector{ array{ 2, 1, i }, array{ 1, n + 1 - n / 2, n } };
	}
	return vector(0, array{ 0, 0, 0 });
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> v[i];
		auto res = sol(n, v);
		cout << "Case #" << tc_num << '\n';
		cout << res.size() << '\n';
		for (auto [op, i, j] : res) cout << op << ' ' << i << ' ' << j << '\n';
	}
}