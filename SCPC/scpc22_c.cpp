#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 x) {
	if (x == 0) return pair(2, vector(3, 1));
	vector buc(0, pair(0, 0));
	while (x) {
		int a = x % 4 == 1 || x % 4 == 2 ? 4 : 2;
		int b = x & 1 ? 1 : 2;
		buc.push_back(pair(a, b));
		x = (x - b) / a;
	}
	int k = buc.size() + 1;
	vector p(1, 0);
	for (int i = 1; i <= k - 1; i++) p.push_back(i);
	for (int i = k - 1; i >= 1; i--) {
		int cnt = buc[k - 1 - i].second - 1;
		while (cnt--) p.push_back(i);
	}
	for (int i = 2; i <= k - 1; i++) {
		int cnt = buc[k - 1 - i].first;
		while (cnt--) p.push_back(i);
	}
	p.push_back(k);
	vector v(p.size() - 1, 0);
	for (int i = 0; i < v.size(); i++) {
		v[i] = p[i + 1] - p[i];
	}
	return pair(k, v);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		i64 x; cin >> x;
		auto [k, v] = sol(x);
		cout << "Case #" << tc_num << '\n';
		cout << v.size() << ' ' << k << '\n';
		for (int x : v) cout << x << ' ';
		cout << '\n';
	}
}