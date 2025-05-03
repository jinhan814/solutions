#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	auto check = [&](int x) -> bool {
		for (int i = 0; i < n; i++) if (v[i] % x && (v[i] - 1) / 2 < x) return 0;
		return 1;
	};
	int res = -1, mn = ranges::min(v);
	for (int x : { mn, mn >> 1, mn - 1 >> 1}) {
		if (!check(x)) continue;
		res = x;
		break;
	}
	cout << res << '\n';
}