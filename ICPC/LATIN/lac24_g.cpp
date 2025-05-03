#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	double acc = 0;
	vector w(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> w[i], acc += w[i];

	vector buc(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) for (int j = i; j <= n; j += i) buc[j].push_back(i);

	vector p(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		p[i].resize((n + i - 1) / i + 1);
		for (int d1 : buc[i]) for (int d2 : buc[i]) {
			int g = gcd(d1, d2);
			if (d1 / g * d2 != i) continue;
			p[d1][i / d1] += w[d2];
		}
	}

	vector dp(n + 1, 0.);
	for (int i = n; i >= 1; i--) {
		double a = 1 - p[i][1] / acc;
		double b = p[i][1] / acc;
		for (int j = 2; i * j <= n; j++) b += p[i][j] / acc * (dp[i * j] + 1);
		dp[i] = b / a;
	}
	cout << fixed << setprecision(20);
	cout << dp[1] << '\n';
}