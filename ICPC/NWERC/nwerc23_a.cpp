#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) -> int {
	if (n == 1 || m == 1) return 1;
	auto check = [&](int k) -> bool {
		int s = 0, a = 0, b = 0;
		for (int i = 0; i < k; i++) {
			s += v[i] / 3;
			if (v[i] % 3 == 1) a++;
			if (v[i] % 3 == 2) b++;
			if (s > m - 2) return 0;
		}
		s += (a + 1 - min(a, b)) / 2 + b;
		return s <= m - 2;
	};
	int lo = 0, hi = n - 1;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (check(mid)) lo = mid;
		else hi = mid;
	}
	return lo + 2;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());
	cout << sol(n, m, v) << '\n';
}