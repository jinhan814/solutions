#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int k, auto v) {
	i64 cnt = 0, acc = 0;
	int l = 0, r = n - 1;
	while (1) {
		while (l < n && v[l] + cnt >= k) l++;
		while (r >= 0 && v[r] + cnt >= k) r--;
		if (l == n) break;
		i64 x = k - (max(v[l], v[r]) + cnt);
		cnt += x;
		acc += (r - l + 1) * x;
	}
	return pair(cnt, acc);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, k; cin >> n >> k;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		auto [cnt, acc] = sol(n, k, v);
		cout << "Case #" << tc_num << '\n';
		cout << cnt << ' ' << acc << '\n';
	}
}