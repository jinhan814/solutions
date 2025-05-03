#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, m; cin >> n >> m;
	i64 res = 0, prv = 1LL << 60;
	for (int i = 0; i < n; i++) {
		i64 x; cin >> x;
		if (abs(x - prv) < m) x = 1LL << 60;
		if (x >> 60) res++; prv = x;
	}
	cout << res << '\n';
}