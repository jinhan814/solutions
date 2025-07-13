#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
constexpr int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
constexpr int mul(int a, int b) { return 1LL * a * b % mod; }
constexpr int pow(int x, int n) {
	int ret = 1;
	for (; n; n >>= 1) {
		if (n & 1) ret = mul(ret, x);
		x = mul(x, x);
	}
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int a, b; cin >> a >> b;
	if (a > b) swap(a, b);
	if (a - 2 > n - b) tie(a, b) = pair(n + 2 - b, n + 2 - a);
	int fac = 1, inv = 1;
	for (int i = 0; i < a - 2; i++) {
		fac = mul(fac, n + a - b - 2 - i);
		inv = mul(inv, i + 1);
	}
	int res = mul(fac, pow(inv, mod - 2));
	if (a + 1 != b) res = mul(res, pow(2, b - a - 1));
	else res = add(res, pow(2, n - 3));
	cout << res << '\n';
}