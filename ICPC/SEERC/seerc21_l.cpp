#include <bits/stdc++.h>
using namespace std;

auto sol_1 = [](int n, const auto& p) {
	vector res(0, tuple(0, 0, 'A'));
	if (p[0][3 * n] >= n) return res;
	int j = 1;
	for (int i = 1; i <= 3 * n; i++) {
		while (j <= 3 * n && p[0][i - 1] + (j - i + 1) + (p[0][3 * n] - p[0][j]) < n) j++;
		if (j > 3 * n) break;
		if (p[1][i - 1] + p[1][3 * n] - p[1][j] != n) continue;
		if (p[2][i - 1] + p[2][3 * n] - p[2][j] != n) continue;
		res.push_back({ i, j, 'A' });
		break;
	}
	return res;
};

auto sol_2 = [](int n, const auto& p) {
	vector res(0, tuple(0, 0, 'A'));
	if (p[2][3 * n] < n) return res;
	int i = n;
	while (p[2][i] < n) i++;
	int x = p[0][i];
	int y = p[1][i];
	if (x > n || y > n) return res;
	res.push_back({ i + 1, i + n - x, 'A' });
	res.push_back({ i + n - x + 1, 3 * n, 'B' });
	return res;
};

auto sol = [](int n, string s) {
	vector p(3, vector(3 * n + 1, 0));
	for (int i = 0; i < 3 * n; i++) {
		for (int j = 0; j < 3; j++) {
			p[j][i + 1] = s[i] == j + 65;
			p[j][i + 1] += p[j][i];
		}
	}
	if (p[0][3 * n] == n && p[1][3 * n] == n) {
		return vector(0, tuple(0, 0, 'A'));
	}
	string t = "ABC";
	for (int i = 0; i < 6; i++) {
		swap(t[i & 1], t[2]);
		swap(p[i & 1], p[2]);
		auto res = sol_1(n, p);
		if (res.empty()) continue;
		for (auto& [l, r, x] : res) x = t[x - 65];
		return res;
	}
	for (int i = 0; i < 6; i++) {
		swap(t[i & 1], t[2]);
		swap(p[i & 1], p[2]);
		auto res = sol_2(n, p);
		if (res.empty()) continue;
		for (auto& [l, r, x] : res) x = t[x - 65];
		return res;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	auto res = sol(n, s);
	cout << res.size() << '\n';
	for (auto [l, r, x] : res) {
		cout << l << ' ' << r << ' ' << x << '\n';
	}
}