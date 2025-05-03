#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, d; cin >> n >> d;
	i64 a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		i64 x; cin >> x;
		a = max(a, -x);
		b = max(b, x);
	}
	i64 r1 = 2 * a + 2 * b + d + min({ 2 * a, 2 * b, d });
	i64 r2 = 2 * a + 2 * b + max(d, 2 * a + 2 * b);
	cout << min(r1, r2) << '\n';
}