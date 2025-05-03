#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	if (m % (k / gcd(n, k))) return cout << "impossible", 0;
	int a = n / gcd(n, k);
	int b = m / (k / gcd(n, k));
	vector v(n, string(m, 0));
	for (int i = 0; i < n; i += a) for (int j = 0; j < m; j += b) {
		for (int x = i; x < i + a; x++) for (int y = j; y < j + b; y++)
			v[x][y] = 65 + (i / a) * (m / b) + (j / b);
	}
	for (auto s : v) cout << s << '\n';
}