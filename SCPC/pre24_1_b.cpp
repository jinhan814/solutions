#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	i64 ret = 0;
	for (int i = 0; i < n / 4; i++) {
		int val = v[n - 1 - i] - v[i];
		ret += 2 * val;
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}