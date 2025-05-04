#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	vector buc(0, array{ 0, 0, 0 });
	for (int i = 1; i < n; i++) a[i][0] += a[i - 1][0];
	for (int i = 1; i < m; i++) b[i][0] += b[i - 1][0];
	for (int i = 0, j = 0, x = 0; ;) {
		while (i < a.size() && a[i][0] <= x) i++;
		while (j < b.size() && b[j][0] <= x) j++;
		if (i == a.size() || j == b.size()) break;
		buc.push_back({ i + 1, a[i][1], b[j][1] });
		x = min(a[i][0], b[j][0]);
	}
	vector res(0, 0);
	for (int l = 0, r = 0; l < buc.size(); l = r) {
		while (r < buc.size() && buc[l][2] == buc[r][2]) r++;
		if (l && buc[l - 1][2] > buc[l][2]) continue;
		if (r < buc.size() && buc[r][2] > buc[l][2]) continue;
		for (int i = l; i < r; i++) {
			if (buc[i][1] != buc[i][2]) continue;
			res.push_back(i);
			break;
		}
	}
	vector c(buc.size(), 0), v(buc.size(), 0);
	for (int i : res) c[i] = 1, v[i] = buc[i][1];
	for (int i : res) {
		int l = i - 1, xl = buc[i][1];
		int r = i + 1, xr = buc[i][1];
		auto f = [&](int& x, int i) { v[i] = max(v[i], x = min(x, buc[i][1])); };
		while (l >= 0 && !c[l]) f(xl, l--);
		while (r < buc.size() && !c[r]) f(xr, r++);
	}
	for (int i = 0; i < buc.size(); i++) {
		if (v[i] == buc[i][2]) continue;
		return vector(0, 0);
	}
	for (int& i : res) i = buc[i][0];
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, array{ 0, 0 });
	for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1];
	int m; cin >> m;
	vector b(m, array{ 0, 0 });
	for (int i = 0; i < m; i++) cin >> b[i][0] >> b[i][1];
	auto res = sol(n, m, a, b);
	if (res.empty()) return cout << -1 << '\n', 0;
	cout << res.size() << '\n';
	for (int x : res) cout << x << ' ';
	cout << '\n';
}