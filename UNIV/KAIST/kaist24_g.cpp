#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, k, x; cin >> n >> k >> x;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	auto check = [&](i64 t) -> bool {
		vector v(0, 0LL);
		for (int i = 0; i < n; i++) {
			if (a[i] <= t) continue;
			v.push_back((a[i] - t) * b[i]);
		}
		sort(v.begin(), v.end(), greater{});
		i64 acc = 0;
		while (v.size() + 1 > x) acc += v.back(), v.pop_back();
		return acc < k;
	};
	int lo = -1, hi = 1 << 20;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (!check(mid)) lo = mid;
		else hi = mid;
	}
	cout << hi << '\n';
}