#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n, i64 m) {
	if (!n) return -m * m;
	auto f = [&](i64 a) {
		i64 res = a - 1 + (n - a + 1) * (n - a + 1);
		i64 b = min(a + 1, m), q = m / b, r = m % b;
		res -= r * (q + 1) * (q + 1);
		res -= (b - r) * q * q;
		return res;
	};
	int lo = 1, hi = n;
	while (lo + 2 < hi) {
		int mid = lo + hi >> 1;
		if (f(mid) < f(mid + 1)) lo = mid;
		else hi = mid;
	}
	while (lo < hi && f(lo) < f(lo + 1)) lo++;
	return f(lo);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (1) {
		int n, m; cin >> n >> m;
		if (!n && !m) break;
		cout << sol(n, m) << '\n';
	}
}