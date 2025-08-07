#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int d, auto v) {
	auto calc = [](int n, int d, auto v) {
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (v[i] < 0) continue;
			if (v[i] > d) continue;
			int l = min(2 * v[i] - d, 0);
			int r = v[i];
			auto lo = lower_bound(v.begin(), v.end(), l);
			auto hi = upper_bound(v.begin(), v.end(), r);
			ret = max(ret, int(hi - lo));
		}
		return ret;
	};
	sort(v.begin(), v.end());
	int res_1 = calc(n, d, v);
	reverse(v.begin(), v.end());
	for (int& x : v) x = -x;
	int res_2 = calc(n, d, v);
	return max(res_1, res_2);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, m; cin >> n >> m;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, m, v) << '\n';
	}
}