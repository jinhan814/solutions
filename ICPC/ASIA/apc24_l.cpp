#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		v[i] = v[i] << 1 | 1;
	}

	int rank = 0;
	for (int bit = 0; bit <= 30 && rank < n; bit++) {
		for (int i = rank + 1; i < n; i++) if (v[i] >> bit & 1) swap(v[rank], v[i]);
		if (~v[rank] >> bit & 1) continue;
		for (int i = rank + 1; i < n; i++) if (v[i] >> bit & 1) v[i] ^= v[rank];
		rank++;
	}

	int res = 1, k = rank * (rank - 1) / 2 + (n - rank) * (rank - 1);
	while (k--) res = (res << 1) % mod;
	cout << res << '\n';
}