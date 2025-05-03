#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];

	auto get_coord = [&] {
		vector res(0, pair(0LL, 0LL));
		for (int i = 0; i < n; i++) {
			if (1LL * a[i] * m < abs(b[i])) continue;
			auto x = 1LL * a[i] * m;
			res.push_back({ x - b[i], x + b[i] });
		}
		return res;
	};

	auto sol = [](auto v) -> int {
		const int n = v.size();
		if (!n) return 0;
		sort(v.begin(), v.end());
		vector lis(0, 0LL);
		for (auto [_, x] : v) {
			if (lis.empty() || lis.back() <= x) lis.push_back(x);
			else *upper_bound(lis.begin(), lis.end(), x) = x;
		}
		return lis.size();
	};

	cout << sol(get_coord()) << '\n';
}