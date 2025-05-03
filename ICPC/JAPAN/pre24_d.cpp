#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (1) {
		int n; cin >> n;
		if (!n) break;
		i64 a, b, c; cin >> a >> b >> c;
		vector v(101, vector(101, 0));
		vector dp(101, vector(101, vector(4, 0LL)));
		for (int i = 0; i < n; i++) {
			int x, y; cin >> x >> y;
			v[x][y] = 1;
		}
		int d = 0;
		while (1) {
			int x = a + "2101"[d] - '1';
			int y = b + "1210"[d] - '1';
			if (x < 0 || x > 100 || y < 0 || y > 100) break;
			if (v[x][y]) { d = d + 1 & 3; continue; }
			a = x, b = y;
			if (!--c || dp[a][b][d] && !(c %= dp[a][b][d] - c)) break;
			dp[a][b][d] = c;
		}
		a += ("2101"[d] - '1') * c;
		b += ("1210"[d] - '1') * c;
		cout << a << ' ' << b << '\n';
	}
}