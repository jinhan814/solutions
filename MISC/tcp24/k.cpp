#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m, k; cin >> n >> m >> k;
		vector v(n, string{});
		vector a(m, string{});
		vector b(k, string{});
		for (int i = 0; i < n; i++) cin >> v[i];
		for (int i = 0; i < m; i++) cin >> a[i];
		for (int i = 0; i < k; i++) cin >> b[i];
		sort(b.begin(), b.end());
		int u = 0;
		for (auto x : a) u += ranges::binary_search(b, x);
		int res = min(1 + min(n - k, k), m + k - 2 * u);
		cout << res << '\n';
	}
}