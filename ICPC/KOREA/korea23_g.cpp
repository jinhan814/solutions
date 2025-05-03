#include <bits/stdc++.h>
using namespace std;

using i128 = __int128;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k, q; cin >> n >> k >> m >> q;
	vector v(n + 1, i128(0));
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < m; j++) {
			int x; cin >> x;
			v[x] |= i128(1) << i;
		}
	}
	vector c(n, 0);
	iota(c.begin(), c.end(), 1);
	sort(c.begin(), c.end(), [&](int i, int j) { return v[i] < v[j]; });
	auto query = [&](i128 x) {
		int lo = -1, hi = n;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (v[c[mid]] < x) lo = mid;
			else hi = mid;
		}
		if (hi == n || v[c[hi]] != x) return 0;
		if (hi + 1 < n && v[c[hi + 1]] == x) return 0;
		return c[hi];
	};
	for (int i = 0; i < q; i++) {
		string s; cin >> s;
		i128 x = 0;
		for (int j = 0; j < k; j++) x |= i128(s[j] == 'Y') << j;
		cout << query(x) << '\n';
	}
}