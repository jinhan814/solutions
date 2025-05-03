#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, n; cin >> a >> b >> n;
	vector x(n + 2, 0), y(n + 2, 0);
	for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
	x[n + 1] = a, y[n + 1] = b;
	auto cost = [&](int i, int j) {
		auto ret = hypot(x[i] - x[j], y[i] - y[j]);
		if (i && i <= n) ret -= 1;
		if (j && j <= n) ret -= 1;
		if (ret < 0) ret = 0;
		return ret;
	};
	vector d(n + 2, 2e9); d[0] = 0;
	vector buc(n + 2, 0);
	iota(buc.begin(), buc.end(), 0);
	while (1) {
		int p = -1;
		for (int x : buc) if (p == -1 || d[p] > d[x]) p = x;
		if (p == n + 1) break;
		buc.erase(ranges::find(buc, p));
		for (int x : buc) d[x] = min(d[x], d[p] + cost(p, x));
	}
	cout << fixed << setprecision(10);
	cout << d[n + 1] << '\n';
}