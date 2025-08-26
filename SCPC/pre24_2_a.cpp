#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, i64 a, i64 b, auto v) {
	vector p(n + 1, 0);
	for (int i = 0; i < n; i++) p[i + 1] = p[i] + v[i];
	i64 ret = b * p[n];
	i64 mx = -(1LL << 60);
	for (int i = 0; i <= n; i++) {
		i64 val = a * i - (a + b) * p[i];
		ret = min(ret, val - mx + b * p[n]);
		mx = max(mx, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, a, b; cin >> n >> a >> b;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, a, b, v) << '\n';
	}
}