#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 1; i <= n; i++) v[i] += v[i - 1];

	vector cache(v[n] + 1, 0);
	auto sol = [&](int x) {
		int& ret = cache[x];
		if (ret) return ret;
		for (int i = 1; i <= n;) {
			if (v[i] - v[i - 1] > x) return ret = -1;
			int lo = i, hi = n + 1;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				if (v[mid] - v[i - 1] <= x) lo = mid;
				else hi = mid;
			}
			ret++, i = hi;
		}
		return ret;
	};

	int q; cin >> q;
	while (q--) {
		int x; cin >> x;
		int res = sol(x);
		if (res == -1) cout << "Impossible" << '\n';
		else cout << res << '\n';
	}
}