#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, int m, int q, auto v, auto qs) {
	map c{ pair(1, 0), pair(m + 1, 1) };
	for (auto [a, b] : v) c[a]++, c[b + 1]--;
	vector e(c.begin(), c.end());
	for (int i = 1; i < e.size(); i++) e[i].second += e[i - 1].second;
	vector buc(0, 0);
	for (int l = 0, r = 0; l < e.size(); l = r) {
		while (r < e.size() && e[l].second == e[r].second) r++;
		if (e[l].second) continue;
		buc.push_back(e[r].first - e[l].first);
	}
	sort(buc.begin(), buc.end());
	vector p(buc.size() + 1, 0LL);
	for (int i = buc.size() - 1; i >= 0; i--) {
		p[i] = p[i + 1] + buc[i];
	}
	vector res(q, 0LL);
	for (int i = 0; i < q; i++) {
		auto j = lower_bound(buc.begin(), buc.end(), qs[i]) - buc.begin();
		res[i] += p[j] + i64(buc.size() - j) * (1 - qs[i]);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, array{ 0, 0 });
	for (auto& [a, b] : v) cin >> a >> b;
	int q; cin >> q;
	vector qs(q, 0);
	for (int i = 0; i < q; i++) cin >> qs[i];
	auto res = sol(n, m, q, v, qs);
	for (int i = 0; i < q; i++) cout << res[i] << '\n';
}