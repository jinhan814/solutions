#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];

	auto f = [&](int i, int lim) {
		if (a[i] < lim) return 0;
		if (!b[i]) return m;
		return (a[i] - lim) / b[i] + 1;
	};

	auto get_cnt = [&](int l, int r, int lim) {
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (l < i && i < r) continue;
			ret += f(i, lim);
		}
		return ret;
	};

	auto get_sum = [&](int l, int r, int lim) {
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (l < i && i < r) continue;
			int t = f(i, lim);
			ret += (2 * a[i] - (t - 1) * b[i]) * t >> 1;
		}
		return ret;
	};

	auto calc = [&](int l, int r, int k) {
		int lo = 0, hi = 5001;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (get_cnt(l, r, mid) >= k) lo = mid;
			else hi = mid;
		}
		int a = get_sum(l, r, hi);
		int b = lo * (k - get_cnt(l, r, hi));
		return a + b;
	};

	int res = 0;
	for (int a = 0; a < n; a++) for (int b = 0; a + b < n; b++) {
		int l = a;
		int r = n - b;
		int k = m - (a + b + min(a, b));
		if (k > 0) res = max(res, calc(l, r, k));
	}
	cout << res << '\n';
}