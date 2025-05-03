#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(m, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < m; i++) cin >> b[i];
	sort(b.begin(), b.end());

	vector d(n, 1 << 30);
	for (int i = 0; i < n; i++) {
		auto it = lower_bound(b.begin(), b.end(), i * 100);
		if (it != b.end()) d[i] = min(d[i], *it - 100 * i);
		if (it != b.begin()) d[i] = min(d[i], 100 * i - *prev(it));
	}

	vector buc(0, pair(0, 0));
	for (int i = 0; i < n; i++) {
		buc.push_back({ 100 * i - d[i], a[i] });
		buc.push_back({ 100 * i + d[i], -a[i] });
	}
	sort(buc.begin(), buc.end());

	auto opt = 0LL, acc = 0LL;
	for (auto [x, d] : buc) {
		acc += d;
		opt = max(opt, acc);
	}
	cout << opt << '\n';
}