#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];

	vector c(n, -1);
	for (int i = 1; i < n; i++) {
		if (v[i - 1] == v[i]) continue;
		c[i] = __lg(v[i - 1] ^ v[i]);
	}

	vector cnt(n, vector(2, 0));
	auto res = 0LL;
	for (int l = 0, r = 0; l < n; l++) {
		if (l && c[l] != -1) {
			int p = c[l];
			int t = v[l - 1] >> p & 1;
			cnt[p][t]--;
		}
		while (r + 1 < n) {
			int p = c[r + 1];
			if (p == -1) { r++; continue; }
			int t = v[r] >> p & 1;
			if (cnt[p][!t]) break;
			r++;
			cnt[p][t]++;
		}
		res += r - l + 1;
	}
	cout << res << '\n';
}