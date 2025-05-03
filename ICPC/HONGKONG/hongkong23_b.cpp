#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n + 1, vector(m + 1, 0));
	vector b(n + 1, vector(m + 1, 0));
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		cin >> a[i][j];
		a[i][j] = add(a[i][j], a[i][j - 1]);
	}
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
		cin >> b[i][j];
		b[i][j] = add(b[i][j], b[i - 1][j]);
	}
	int res = 2;
	for (int i = 1; i < n; i++) for (int j = 1; j < m; j++) {
		int p = mul(a[i][j - 1], b[i - 1][j]);
		int q = sub(a[i + 1][m], a[i + 1][j - 1]);
		int r = sub(b[n][j + 1], b[i - 1][j + 1]);
		res = add(res, mul(p, mul(q, r)));
	}
	cout << res << '\n';
}