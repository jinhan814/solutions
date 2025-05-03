#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 a, b, res = 0; cin >> a >> b; a--, b--;
	if (a > b) swap(a, b);
	for (i64 x = 1; x <= a; x++) {
		i64 y = sqrt(a * a - x * x) + 0.5;
		if (x * x + y * y != a * a) continue;
		if (b % (a / gcd(x, y)) == 0) res++;
	}
	if (a != b) res *= 2;
	cout << res << '\n';
}