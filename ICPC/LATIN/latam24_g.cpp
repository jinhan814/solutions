#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0LL);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x; cin >> x;
			if (x) v[i] |= 1LL << j;
		}
	}

	auto check = [&] {
		for (int i = 0; i < n; i++) if (v[i]) return 1;
		return 0;
	};

	auto move = [&] {
		int x = 0, y = 0;
		for (int x = 0, y = 0; x < n; x++) {
			if (!(v[x] >> y)) continue;
			int p = 63 - __builtin_clzll(v[x]);
			v[x] &= (1LL << y) - 1;
			y = p;
		}
	};

	int res = 0;
	while (check()) res++, move();
	cout << res << '\n';
}