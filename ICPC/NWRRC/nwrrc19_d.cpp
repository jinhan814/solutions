#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998'244'353;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return 1LL * a * b % mod; }
int pow(int x, int n) { return n ? n & 1 ? mul(x, pow(x, n - 1)) : pow(mul(x, x), n / 2) : 1; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	int res = 0;
	vector c(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		int a = mul(i + 1 >> 1, pow(k, i + 1 >> 1));
		int b = mul(i >> 1, pow(k, i + 2 >> 1));
		c[i] = add(c[i], add(a, b));
		res = add(res, mul(n / i, c[i]));
		for (int j = 2; i * j <= n; j++) c[i * j] = sub(c[i * j], mul(j, c[i]));
	}
	cout << res << '\n';
}