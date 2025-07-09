#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto v) {
	vector l(n + 1, 0), r(n + 1, 0);
	i64 acc = 0, cnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = n - 1, p = 0; j >= 0; j--) {
			if (v[i][j] == '#') continue;
			r[j] = j + 1 < n && v[i][j + 1] == '.' ? r[j + 1] : r[j] + p;
			p++;
			l[j] = i + 1 < n && v[i + 1][j] == '.' ? l[j] + p : l[j + 1] + 1;
			acc += l[j] - r[j] - 1;
			cnt++;
		}
	}
	return cnt * (cnt - 1) / 2 - acc;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, string{});
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}