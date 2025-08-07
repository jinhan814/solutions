#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, auto v, auto a, auto b) {
	vector cht(0, pair(0LL, 0LL));
	for (int i = 0; i < m; i++) {
		while (cht.size() >= 2) {
			auto [a1, b1] = cht.back();
			auto [a2, b2] = cht.end()[-2];
			i64 x1 = (a1 - a[i]) * (b1 - b2);
			i64 x2 = (a2 - a1) * (b[i] - b1);
			if (x1 >= x2) cht.pop_back();
			else break;
		}
		cht.push_back(pair(a[i], b[i]));
	}
	auto f = [&](i64 x) {
		int lo = 0, hi = cht.size() - 1;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			auto [a1, b1] = cht[mid - 1];
			auto [a2, b2] = cht[mid];
			i64 r1 = a1 * x + b1;
			i64 r2 = a2 * x + b2;
			if (r1 >= r2) lo = mid;
			else hi = mid;
		}
		i64 ret = 1LL << 60;
		for (int i = lo; i <= hi; i++) {
			auto [a, b] = cht[i];
			ret = min(ret, a * x + b);
		}
		return ret;
	};
	i64 ret = 0;
	for (int i = 0; i < n; i++) {
		ret += (v[i][1] - v[i][0]) * a[0];
		if (i >= 1) ret += f(v[i][0] - v[i - 1][1]);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, array{ 0LL, 0LL });
		for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
		int m; cin >> m;
		vector a(m, 0LL), b(m, 0LL);
		for (int i = 0; i < m; i++) cin >> a[i];
		for (int i = 0; i < m; i++) cin >> b[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, m, v, a, b) << '\n';
	}
}