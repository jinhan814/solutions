#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto a, auto b) {
	vector buc(n, 0);
	iota(buc.begin(), buc.end(), 0);
	sort(buc.begin(), buc.end(), [&](int i, int j) {
		return a[i] > a[j];
	});
	vector res(m, vector(0, 0));
	vector acc(m, 0LL);
	for (int i : buc) {
		int opt = 0;
		for (int j = 1; j < m; j++) {
			i64 x = 1LL * b[opt] * (a[i] + acc[j]);
			i64 y = 1LL * b[j] * (a[i] + acc[opt]);
			if (x < y) opt = j;
		}
		res[opt].push_back(i);
		acc[opt] += a[i];
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0);
	vector b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	auto res = sol(n, m, a, b);
	for (auto& v : res) {
		cout << v.size();
		for (int x : v) cout << ' ' << x + 1;
		cout << '\n';
	}
}