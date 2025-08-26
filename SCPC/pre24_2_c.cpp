#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int q, auto v, auto p, auto qs) {
	vector res(q, 0.);
	for (int iter = 0; iter < 2; iter++) {
		vector buc(n, 0);
		iota(buc.begin(), buc.end(), 0);
		sort(buc.begin(), buc.end(), [&](int i, int j) {
			return v[i][iter] < v[j][iter];
		});
		vector p1(n + 1, 0.);
		vector p2(n + 1, 0.);
		for (int i = 0; i < n; i++) {
			p1[i + 1] = p1[i] + p[buc[i]];
			p2[i + 1] = p2[i] + v[buc[i]][iter] * p[buc[i]];
		}
		for (int i = 0; i < q; i++) {
			int lo = -1, hi = n;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				if (v[buc[mid]][iter] < qs[i][iter]) lo = mid;
				else hi = mid;
			}
			res[i] += qs[i][iter] * (2 * p1[hi] - p1[n]);
			res[i] -= 2 * p2[hi] - p2[n];
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(20);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, array{ 0, 0 });
		vector p(n, 0.);
		for (auto& [a, b] : v) cin >> a >> b;
		for (int i = 0; i < n; i++) cin >> p[i];
		int q; cin >> q;
		vector qs(q, array{ 0, 0 });
		for (auto& [a, b] : qs) cin >> a >> b;
		auto res = sol(n, q, v, p, qs);
		cout << "Case #" << tc_num << '\n';
		for (int i = 0; i < q; i++) cout << res[i] << '\n';
	}
}