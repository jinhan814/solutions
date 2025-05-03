#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, ang; cin >> ang >> n;
	vector dp(300'001, 0);
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		dp[a] = max(dp[a], b);
	}
	double res = 0, r = -1;
	double val = 1 / tan(ang / 180. * acos(-1));
	for (int i = 0; i <= 300'000; i++) {
		if (!dp[i]) continue;
		double x = i + dp[i] * val;
		if (x <= r) continue;
		res += x - max(r, i * 1.);
		r = x;
	}
	cout << fixed << setprecision(10);
	cout << res << '\n';
}