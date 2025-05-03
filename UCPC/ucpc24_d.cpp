#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 a, i64 b) {
	i64 q = b / a, r = b % a;
	return r * (q + 1) * (q + 1) + (a - r) * q * q;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 1; i < n; i++) cin >> v[i];
	vector p(n + 1, 0LL);
	for (int i = 0; i < m; i++) {
		int a, b, x; cin >> a >> b >> x;
		p[a] += x;
		p[b] -= x;
	}
	for (int i = 1; i < n; i++) {
		p[i] += p[i - 1];
		cout << sol(v[i], p[i]) << '\n';
	}
}