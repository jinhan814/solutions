#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, auto a, auto b) {
	vector idx(n, 0);
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(), [&](int i, int j) {
		if (b[i] != b[j]) return b[i] < b[j];
		return i < j;
	});
	i64 res = 0;
	for (int i = 0; i < n; i++) res += abs(a[idx[i]] - a[i]);
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector a(n, 0), b(n, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, a, b) << '\n';
	}
}