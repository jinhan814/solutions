#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector v(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> v[i];
	vector p1(n + 1, 0LL), p2(n + 1, 0LL), p3(n + 1, 0LL);
	for (int i = 1; i <= n; i++) {
		p1[i] = p1[i - 1];
		p2[i] = p2[i - 1];
		p3[i] = p3[i - 1];
		if (v[i] == 1) p1[i] += v[i];
		if (v[i] == (v[i] & -v[i])) p2[i] += v[i];
		if (v[i] & 1) p3[i] += v[i];
	}
	while (q--) {
		int l, r; cin >> l >> r;
		i64 a = p1[r] - p1[l - 1];
		i64 b = p2[r] - p2[l - 1];
		i64 c = p3[r] - p3[l - 1];
		i64 x = b + (a + 1 >> 1);
		i64 y = c + (a >> 1);
		cout << (x ^ y ? x < y ? 'B' : 'A' : 'E') << '\n';
	}
}