#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	if (n & 1) {
		map cx{ pair(0, 0) };
		map cy{ pair(0, 0) };
		for (auto [a, b] : v) cx[a]++, cy[b]++;
		int x = -1, y = -1;
		for (auto [a, b] : cx) if (b & 1) x = a;
		for (auto [a, b] : cy) if (b & 1) y = a;
		auto it = find(v.begin(), v.end(), array{ x, y });
		v.erase(it);
		n--;
	}
	i64 ret = 0;
	for (int iter = 0; iter < 2; iter++) {
		sort(v.begin(), v.end());
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && v[i][0] == v[j][0]) j++;
			for (int k = i; k < j; k += 2) {
				ret += v[k + 1][1] - v[k][1];
			}
		}
		for (auto& [a, b] : v) swap(a, b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		for (auto& [a, b] : v) cin >> a >> b;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}