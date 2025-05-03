#include <bits/stdc++.h>
using namespace std;

auto check = [](int n, auto v) {
	vector c(n + 1, 0);
	for (int i = 1; i + 1 < n; i++) {
		if (!v[i] || c[v[i]]++) return 0;
		if (v[i - 1] < v[i]) continue;
		if (v[i] > v[i + 1]) continue;
		return 0;
	}
	return 1;
};

auto construct = [](int n, int p, auto v) {
	if (p < 0 || p >= n) return vector(0, 0);
	if (!v[p]) v[p] = n;
	if (v[p] != n) return vector(0, 0);
	vector c(n + 1, 0);
	vector dp1 = v, dp2 = v;
	for (int i = 0; i < n; i++) c[v[i]]++;
	for (int i = 1; i < n; i++) dp1[i] = max(dp1[i], dp1[i - 1]);
	for (int i = n - 2; i >= 0; i--) dp2[i] = max(dp2[i], dp2[i + 1]);
	int l = p, r = p, l_mn = n, r_mn = n;
	auto move_l = [&] { l_mn = min(l_mn, v[l--]); };
	auto move_r = [&] { r_mn = min(r_mn, v[r++]); };
	for (int x = n; x >= 1; x--) {
		if (c[x]) continue;
		while (l >= 0 && v[l]) move_l();
		while (r < n && v[r]) move_r();
		if (l >= 0 && l_mn >= x &&
			(r >= n || r_mn < x || dp1[l] > dp2[r])) v[l] = x;
		else if (r < n && r_mn >= x) v[r] = x;
		else return vector(0, 0);
	}
	if (!check(n, v)) return vector(0, 0);
	return v;
};

auto sol = [](int n, auto v) {
	int p = max_element(v.begin(), v.end()) - v.begin();
	for (int x : { 0, n - 1, p, p - 1, p + 1 }) {
		auto res = construct(n, x, v);
		if (res.size()) return res;
	}
	return vector(0, 0);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto res = sol(n, v);
	if (res.empty()) {
		cout << '*' << '\n';
	}
	else {
		for (int x : res) cout << x << ' ';
		cout << '\n';
	}
}