#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	int a, b, c, d; cin >> a >> b >> c >> d;
	int x, t; cin >> x >> t;
	vector v(n + 1, 1 << 30);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());

	vector p(5, vector(n + 1, 0LL));
	for (int i = 0; i < n; i++) {
		p[0][i + 1] = p[0][i] + min(v[i] - 1, t);
		p[1][i + 1] = p[1][i] + max(c - v[i], 0);
		p[2][i + 1] = p[2][i] + min(max(v[i] - c, 0), t);
		p[3][i + 1] = p[3][i] + max(a - v[i], 0);
		p[4][i + 1] = p[4][i] + min(max(v[i] - a, 0), t);
	}

	i64 res = 1LL << 60;
	for (i64 m = 0; m <= n; m++) {
		i64 l = min(m * k - m, n - m), r = n - m;
		i64 acc = p[1][r] - p[1][l] + p[3][n] - p[3][r];
		i64 rem = p[0][l] + p[2][r] - p[2][l] + p[4][n] - p[4][r];
		if (acc > rem || c - v[l] > t || a - v[r] > t) continue;
		res = min(res, m * b + (r - l) * d + acc * x);
	}
	if (res >> 60) res = -1;
	cout << res << '\n';
}