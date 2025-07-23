#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 119 << 23 | 1;
constexpr int mul(int a, int b) { return 1LL * a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n + 1, 0), b(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	vector rb(n + 1, 0);
	for (int i = 1; i <= n; i++) rb[b[i]] = i;
	auto rec = [&](const auto& self, int al, int ar, int bl, int br) -> int {
		if (a[al] != b[br]) return 0;
		if (al == ar) return 1;
		int p = rb[a[al + 1]];
		if (p < bl || br < p) return 0;
		if (p == br - 1) return mul(2, self(self, al + 1, ar, bl, br - 1));
		int x = self(self, al + 1, al + p - bl + 1, bl, p);
		int y = self(self, al + p - bl + 2, ar, p + 1, br - 1);
		return mul(x, y);
	};
	cout << rec(rec, 1, n, 1, n) << '\n';
}