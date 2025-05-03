#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector fac(n + 1, 1);
	for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	vector inv(n + 1, pow(fac[n], mod - 2));
	for (int i = n; i >= 1; i--) inv[i - 1] = mul(inv[i], i);
	int res = fac[n];
	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		res = mul(res, pow(2, x - 1));
		res = mul(res, inv[x]);
	}
	cout << res << '\n';
}